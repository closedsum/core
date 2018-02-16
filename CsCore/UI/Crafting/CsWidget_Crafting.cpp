// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "UI/Crafting/CsWidget_Crafting_Grid.h"
#include "UI/Crafting/CsWidget_Crafting_Slot.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/Crafting/CsManager_Crafting.h"
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Recipe.h"
#include "Data/CsData_Item.h"

// Cache
#pragma region

namespace ECsWidgetCraftingCachedName
{
	namespace Name
	{
		// Functions
		const FName IncrementCount_Internal = FName("UCsWidget_Crafting::IncrementCount_Internal");
		const FName DecrementCount_Internal = FName("UCsWidget_Crafting::DecrementCount_Internal");
	};
}

namespace ECsWidgetCraftingCachedString
{
	namespace Str
	{
		// Functions
		const FString IncrementCount_Internal = TEXT("UCsWidget_Crafting::IncrementCount_Internal");
		const FString DecrementCount_Internal = TEXT("UCsWidget_Crafting::DecrementCount_Internal");
	};
}

#pragma endregion Cache

UCsWidget_Crafting::UCsWidget_Crafting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoIncrementTime = 0.05f;
	AutoDecrementTime = 0.05f;
}

void UCsWidget_Crafting::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	// Options ComboBox
	Options_ComboBox->OnSelectionChanged.AddDynamic(this, &UCsWidget_Crafting::OnRecipeSelectionChanged);
	// Count Spin
	Count_Spin->OnValueChanged.AddDynamic(this, &UCsWidget_Crafting::OnCountValueChanged);
	Count_Spin->OnValueCommitted.AddDynamic(this, &UCsWidget_Crafting::OnCountValueCommitted);
}

void UCsWidget_Crafting::Init()
{
	const FGeometry& Geometry = MyVerticalBox->GetCachedGeometry();
	// TopLeft
	FVector2D PixelPosition;
	FVector2D ViewportPosition;

	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), Geometry.GetAbsolutePosition(), PixelPosition, ViewportPosition);
	Position = PixelPosition;
	// Size = BotRight - TopLeft
	Size = Geometry.LocalToAbsolute(Geometry.GetLocalSize()) - Position;
}

// Routines
#pragma region

bool UCsWidget_Crafting::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::AddRoutine_Internal(Routine, InType))
		return true;

	const TCsWidgetCraftingRoutine RoutineType = (TCsWidgetCraftingRoutine)InType;

	// IncrementCount_Internal
	if (RoutineType == ECsWidgetCraftingRoutine::IncrementCount_Internal)
	{
		IncrementCount_Internal_Routine = Routine;
		return true;
	}
	// DecrementCount_Internal
	if (RoutineType == ECsWidgetCraftingRoutine::DecrementCount_Internal)
	{
		DecrementCount_Internal_Routine = Routine;
		return true;
	}
	return false;
}

bool UCsWidget_Crafting::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::RemoveRoutine_Internal(Routine, InType))
		return true;

	const TCsWidgetCraftingRoutine RoutineType = (TCsWidgetCraftingRoutine)InType;

	// IncrementCount_Internal
	if (RoutineType == ECsWidgetCraftingRoutine::IncrementCount_Internal)
	{
		check(IncrementCount_Internal_Routine == Routine);
		IncrementCount_Internal_Routine = nullptr;
		return true;
	}
	// DecrementCount_Internal
	if (RoutineType == ECsWidgetCraftingRoutine::DecrementCount_Internal)
	{
		check(DecrementCount_Internal_Routine == Routine);
		DecrementCount_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

// Options
#pragma region

void UCsWidget_Crafting::PopulateRecipes()
{
	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());

	TArray<ACsData*> Datas;
	DataMapping->GetLoadedDatas(RecipeAssetType, Datas);

	Options_ComboBox->ClearOptions();

	const int32 Count = Datas.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsData_Recipe* Data = Cast<ACsData_Recipe>(Datas[I]);

		Options_ComboBox->AddOption(Data->GetDisplayName());
	}

	if (Count > CS_EMPTY)
	{
		ACsData_Recipe* Data = Cast<ACsData_Recipe>(Datas[CS_FIRST]);

		Options_ComboBox->SetSelectedOption(Data->GetDisplayName());
	}
}

void UCsWidget_Crafting::SetRecipe(const FName &ShortCode)
{
	// Get Data for selected Recipe
	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	ACsData_Recipe* Recipe		= Cast<ACsData_Recipe>(DataMapping->GetLoadedData(RecipeAssetType, ShortCode));
	// Update Grid with the Ingredients (Items)
	MyGrid->Clear();

	if (CurrentCount.Value.Get() == CS_EMPTY)
		return;

	TArray<FCsRecipeIngredient>* Ingredients = Recipe->GetIngredients();

	const int32 IngredientCount = Ingredients->Num();
	const int32 GridSize		= MyGrid->Dimension.GetSize();

	if (IngredientCount > GridSize)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsWidget_Crafting::SetRecipe: Recipe: %s has MORE Ingredients than what the Crafting Grid supports (%d > %d)."), *(ShortCode.ToString()), IngredientCount, GridSize);
	}

	const int32 Count = FMath::Min(GridSize, IngredientCount);

	for (int32 I = 0; I < Count; ++I)
	{
		const FCsRecipeIngredient& Ingredient = (*Ingredients)[I];
		const FName& ItemShortCode			  = Ingredient.ShortCode;
		ACsData_Item* Item					  = Cast<ACsData_Item>(DataMapping->GetLoadedData(ItemAssetType, ItemShortCode));

		UCsWidget_Crafting_Slot* CurrentSlot = MyGrid->Slots[I];

		CurrentSlot->DisplayName = Item->GetDisplayName();
		CurrentSlot->Count		 = CurrentCount.Value.Get() * Ingredient.Count;

		CurrentSlot->UpdateDisplayNameWithCurrentCount();
		CurrentSlot->SetImage(Item->GetMaterial());
	}
}

void UCsWidget_Crafting::UpdateRecipeWithSelectedOption()
{
	const FName ShortCode = FName(*(Options_ComboBox->GetSelectedOption()));

	SetRecipe(ShortCode);
}

void UCsWidget_Crafting::OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType)
{
	const FName ShortCode = FName(*SelectedItem);

	SetRecipe(ShortCode);
}

bool UCsWidget_Crafting::CanCompleteRecipe(const uint32& Count)
{
	if (Count == CS_EMPTY)
		return false;

	const FName ShortCode		= FName(*(Options_ComboBox->GetSelectedOption()));
	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	ACsData_Recipe* Recipe		= Cast<ACsData_Recipe>(DataMapping->GetLoadedData(RecipeAssetType, ShortCode));

	ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();

	TArray<FCsRecipeIngredient>* Ingredients = Recipe->GetIngredients();
	const int32 IngredientCount				 = Ingredients->Num();

	const uint32 CreationCount = CurrentCount.Value.Get();

	for (int32 I = 0; I < IngredientCount; ++I)
	{
		const FCsRecipeIngredient& Ingredient = (*Ingredients)[I];

		const uint32 ItemCount  = Manager_Inventory->GetItemCount(Ingredient.ShortCode);
		const uint32 TotalCount = Ingredient.Count * CreationCount;
		// If there are NOT enough Items in the Inventory for the requested amount, then 
		// Recipe can NOT be completed
		if (TotalCount > ItemCount)
			return false;
	}
	return true;
}

	// Increment
#pragma region

void UCsWidget_Crafting::OnIncrementButtonPressed()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		 = Schedule;
	Payload->Function		 = &UCsWidget_Crafting::IncrementCount_Internal;
	Payload->Object			 = this;
	Payload->Stop			 = &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			 = &UCsUserWidget::AddRoutine;
	Payload->Remove			 = &UCsUserWidget::RemoveRoutine;
	Payload->Type			 = (uint8)ECsWidgetCraftingRoutine::IncrementCount_Internal;
	Payload->DoInit			 = true;
	Payload->PerformFirstRun = false;
	Payload->Name			 = ECsWidgetCraftingCachedName::Name::IncrementCount_Internal;
	Payload->NameAsString	 = ECsWidgetCraftingCachedString::Str::IncrementCount_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

void UCsWidget_Crafting::OnIncrementButtonReleased()
{
	if (IncrementCount_Internal_Routine && IncrementCount_Internal_Routine->IsValid())
		IncrementCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

void UCsWidget_Crafting::IncrementCount()
{
	uint32 OldValue = CurrentCount.Value.Get();

	if (OldValue == UINT32_MAX)
		return;

	++OldValue;

	if (!CanCompleteRecipe(OldValue))
		return;

	CurrentCount.IncrementValue();
	UpdateRecipeWithSelectedOption();
}

CS_COROUTINE(UCsWidget_Crafting, IncrementCount_Internal)
{
	UCsWidget_Crafting* c	 = Cast<UCsWidget_Crafting>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = c->GetWorld();

	const float CurrentTime = w->GetTimeSeconds();
	const float& StartTime  = r->startTime;

	const float AutoIncrementTime = c->AutoIncrementTime > 0.0f ? c->AutoIncrementTime : 0.01f;

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			c->IncrementCount();
		}
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= AutoIncrementTime);
	} while (true);

	CS_COROUTINE_END(r);
}

#pragma endregion Increment

	// Count
#pragma region

void UCsWidget_Crafting::OnCountValueChanged(float InValue)
{
	const uint32 NewValue = FMath::Max(0, FMath::FloorToInt(InValue));

	if (!CanCompleteRecipe(NewValue))
		return;

	CurrentCount.SetValue(NewValue);
	UpdateRecipeWithSelectedOption();
}

void UCsWidget_Crafting::OnCountValueCommitted(float InValue, ETextCommit::Type CommitMethod)
{
	const uint32 NewValue = FMath::Max(0, FMath::FloorToInt(InValue));

	if (!CanCompleteRecipe(NewValue))
		return;

	CurrentCount.SetValue(NewValue);
	UpdateRecipeWithSelectedOption();
}

#pragma endregion Count

// Decrement
#pragma region

void UCsWidget_Crafting::OnDecrementButtonPressed()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		 = Schedule;
	Payload->Function		 = &UCsWidget_Crafting::DecrementCount_Internal;
	Payload->Object			 = this;
	Payload->Stop			 = &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			 = &UCsUserWidget::AddRoutine;
	Payload->Remove			 = &UCsUserWidget::RemoveRoutine;
	Payload->Type			 = (uint8)ECsWidgetCraftingRoutine::DecrementCount_Internal;
	Payload->DoInit			 = true;
	Payload->PerformFirstRun = false;
	Payload->Name			 = ECsWidgetCraftingCachedName::Name::DecrementCount_Internal;
	Payload->NameAsString	 = ECsWidgetCraftingCachedString::Str::DecrementCount_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

void UCsWidget_Crafting::OnDecrementButtonReleased()
{
	if (DecrementCount_Internal_Routine && DecrementCount_Internal_Routine->IsValid())
		DecrementCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

void UCsWidget_Crafting::DecrementCount()
{
	uint32 OldValue = CurrentCount.Value.Get();

	if (OldValue == 0)
		return;

	--OldValue;

	if (!CanCompleteRecipe(OldValue))
		return;

	CurrentCount.DecrementValue();
	UpdateRecipeWithSelectedOption();
}

CS_COROUTINE(UCsWidget_Crafting, DecrementCount_Internal)
{
	UCsWidget_Crafting* c	 = Cast<UCsWidget_Crafting>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = c->GetWorld();

	const float CurrentTime = w->GetTimeSeconds();
	const float& StartTime  = r->startTime;

	const float AutoDecrementTime = c->AutoDecrementTime > 0.0f ? c->AutoDecrementTime : 0.01f;

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			c->DecrementCount();
		}
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= AutoDecrementTime);
	} while (true);

	CS_COROUTINE_END(r);
}

#pragma endregion Decrement

	// Start
#pragma region

void UCsWidget_Crafting::OnStartButtonPressed()
{
	/*
	ACsManager_Crafting* Manager_Crafting = ACsManager_Crafting::Get(GetWorld());

	Manager_Crafting->CancelCraftingItems(this);
	CraftItem();
	*/
}

#pragma endregion Start

ACsManager_Inventory* UCsWidget_Crafting::GetMyManager_Inventory()
{
	return MyManager_Inventory.IsValid() ? MyManager_Inventory.Get() : nullptr;
}

void UCsWidget_Crafting::CraftItem()
{
	if (CurrentCount.Value.Get() == CS_EMPTY)
		return;

	// Get Data for selected Recipe
	ACsDataMapping* DataMapping  = UCsCommon::GetDataMapping(GetWorld());
	const FString SelectedOption = Options_ComboBox->GetSelectedOption();
	const FName RecipeShortCode  = FName(*SelectedOption);
	ACsData_Recipe* Recipe		 = Cast<ACsData_Recipe>(DataMapping->GetLoadedData(RecipeAssetType, RecipeShortCode));
	// Prepare Payload
	ACsManager_Crafting* Manager_Crafting = ACsManager_Crafting::Get(GetWorld());
	FCsCraftingPayload* Payload			  = Manager_Crafting->AllocatePayload();

	ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();

	Payload->Instigator		   = Manager_Inventory->GetMyOwner();
	Payload->Manager_Inventory = Manager_Inventory;
	Payload->Recipe			   = Recipe;
	Payload->Count			   = CurrentCount.Value.Get();
	Payload->AddToInventory    = true;

	Manager_Crafting->CraftItem(Payload);
}

#pragma endregion Options