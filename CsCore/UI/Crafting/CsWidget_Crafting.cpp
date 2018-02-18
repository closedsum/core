// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "UI/Crafting/CsWidget_Crafting_Grid.h"
#include "UI/Crafting/CsWidget_Crafting_Slot.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/Input/CsManager_Input.h"
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
	// Increment
	Increment.Button.Set(Increment_Button);
	Increment.Button.Init(TEXT("Button"), TEXT("Increment_Button"), GetName() + TEXT(".Increment_Button"));
	Increment.Text.Set(Increment_Text);
	Increment.Text.Init(TEXT("Text"), TEXT("Increment_Text"), GetName() + TEXT(".Increment_Text"));
	Increment_Button->OnPressed.AddDynamic(this, &UCsWidget_Crafting::OnIncrementButtonPressed);
	Increment_Button->OnReleased.AddDynamic(this, &UCsWidget_Crafting::OnIncrementButtonReleased);
	// Count Spin
	CurrentCount.Set(Count_Spin);
	CurrentCount.Init(TEXT("SpinBox"), TEXT("Count_Spin"), GetName() + TEXT(".Count_Spin"));
	Count_Spin->OnValueChanged.AddDynamic(this, &UCsWidget_Crafting::OnCountValueChanged);
	Count_Spin->OnValueCommitted.AddDynamic(this, &UCsWidget_Crafting::OnCountValueCommitted);
	// Decrement
	Decrement.Button.Set(Decrement_Button);
	Decrement.Button.Init(TEXT("Button"), TEXT("Decrement_Button"), GetName() + TEXT(".Decrement_Button"));
	Decrement.Text.Set(Decrement_Text);
	Decrement.Text.Init(TEXT("Text"), TEXT("Decrement_Text"), GetName() + TEXT(".Decrement_Text"));
	Decrement_Button->OnPressed.AddDynamic(this, &UCsWidget_Crafting::OnDecrementButtonPressed);
	Decrement_Button->OnReleased.AddDynamic(this, &UCsWidget_Crafting::OnDecrementButtonReleased);
	// Start
	Start.Button.Set(Start_Button);
	Start.Button.Init(TEXT("Button"), TEXT("Start_Button"), GetName() + TEXT(".Start_Button"));
	Start.Text.Set(Start_Text);
	Start.Text.Init(TEXT("Text"), TEXT("Start_Text"), GetName() + TEXT(".Start_Text"));
	Start_Button->OnPressed.AddDynamic(this, &UCsWidget_Crafting::OnStartButtonPressed);
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

void UCsWidget_Crafting::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Increment.OnNativeTick(InDeltaTime);
	CurrentCount.OnNativeTick(InDeltaTime);
	Decrement.OnNativeTick(InDeltaTime);
	Start.OnNativeTick(InDeltaTime);
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

// Game Event
#pragma region

bool UCsWidget_Crafting::ProcessGameEvent(const TCsGameEvent &GameEvent)
{
	// Start
	if (GameEvent == StartGameEvent)
	{
		CraftItem();
		return true;
	}
	// Increment Start
	if (GameEvent == IncrementStartGameEvent)
	{
		IncrementCount();
		return true;
	}
	// Increment End
	if (GameEvent == IncrementEndGameEvent)
	{
		StopIncrementCount();
		return true;
	}
	// Decrement Start
	if (GameEvent == DecrementStartGameEvent)
	{
		DecrementCount();
		return true;
	}
	// Decrement End
	if (GameEvent == DecrementEndGameEvent)
	{
		StopDecrementCount();
		return true;
	}
	return false;
}

#pragma endregion Game Event

// Options
#pragma region

void UCsWidget_Crafting::PopulateRecipes()
{
	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());

	TArray<ACsData*> Datas;
	DataMapping->GetLoadedDatas(RecipeAssetType, Datas);

	Options_ComboBox->ClearOptions();
	SelectedOptionShortCodes.Reset();

	const int32 Count = Datas.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsData_Recipe* Data = Cast<ACsData_Recipe>(Datas[I]);

		Options_ComboBox->AddOption(Data->GetDisplayName());
		SelectedOptionShortCodes.Add(Data->ShortCode);
	}

	CurrentSelectedOptionIndex = CS_FIRST;

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
	const FName& ShortCode = SelectedOptionShortCodes[CurrentSelectedOptionIndex];

	SetRecipe(ShortCode);
}

void UCsWidget_Crafting::OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType)
{
	// Find ShortCode
	const int32 Count = SelectedOptionShortCodes.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FString Option = Options_ComboBox->GetOptionAtIndex(I);

		if (SelectedItem == Option)
		{
			CurrentSelectedOptionIndex = I;
			break;
		}
	}
	const FName& ShortCode = SelectedOptionShortCodes[CurrentSelectedOptionIndex];

	SetRecipe(ShortCode);
}

bool UCsWidget_Crafting::CanCompleteRecipe(const uint32& Count)
{
	if (Count == CS_EMPTY)
		return false;

	const FName& ShortCode		= SelectedOptionShortCodes[CurrentSelectedOptionIndex];
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
	ACsManager_Input* Manager_Input = ACsManager_Input::Get(GetWorld());

	Manager_Input->QueueInput(IncrementInputAction, ECsInputEvent::FirstPressed);
}

void UCsWidget_Crafting::OnIncrementButtonReleased()
{
	ACsManager_Input* Manager_Input = ACsManager_Input::Get(GetWorld());

	Manager_Input->QueueInput(IncrementInputAction, ECsInputEvent::FirstReleased);
}

bool UCsWidget_Crafting::CanIncrement()
{
	uint32 OldValue = CurrentCount.Value.Get();

	if (OldValue == UINT32_MAX || OldValue >= CurrentCount.MaxValue)
		return false;

	++OldValue;

	if (!CanCompleteRecipe(OldValue))
		return false;
	return true;
}

void UCsWidget_Crafting::IncrementCount()
{
	if (!CanIncrement())
		return;

	StopIncrementCount();

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

	R->floats[0] = GetWorld()->GetTimeSeconds();

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsWidget_Crafting, IncrementCount_Internal)
{
	UCsWidget_Crafting* c	 = Cast<UCsWidget_Crafting>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = c->GetWorld();

	const float CurrentTime = w->GetTimeSeconds();
	const float& StartTime  = r->floats[0];

	const float AutoIncrementTime = c->AutoIncrementTime > 0.0f ? c->AutoIncrementTime : 0.01f;

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			c->PerformIncrementCount();
		}
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= AutoIncrementTime);

		r->floats[0] = CurrentTime;
	} while (true);

	CS_COROUTINE_END(r);
}

void UCsWidget_Crafting::PerformIncrementCount()
{
	if (!CanIncrement())
		return;

	CurrentCount.IncrementValue();
	UpdateRecipeWithSelectedOption();
}

void UCsWidget_Crafting::StopIncrementCount()
{
	if (IncrementCount_Internal_Routine && IncrementCount_Internal_Routine->IsValid())
		IncrementCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
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
	ACsManager_Input* Manager_Input = ACsManager_Input::Get(GetWorld());

	Manager_Input->QueueInput(DecrementInputAction, ECsInputEvent::FirstPressed);
}

void UCsWidget_Crafting::OnDecrementButtonReleased()
{
	ACsManager_Input* Manager_Input = ACsManager_Input::Get(GetWorld());

	Manager_Input->QueueInput(DecrementInputAction, ECsInputEvent::FirstReleased);
}

bool UCsWidget_Crafting::CanDecrement()
{
	uint32 OldValue = CurrentCount.Value.Get();

	if (OldValue == 0 || OldValue <= CurrentCount.MinValue)
		return false;

	--OldValue;

	if (!CanCompleteRecipe(OldValue))
		return false;
	return true;
}

void UCsWidget_Crafting::DecrementCount()
{
	if (!CanDecrement())
		return;

	StopDecrementCount();

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

	R->floats[0] = GetWorld()->GetTimeSeconds();

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsWidget_Crafting, DecrementCount_Internal)
{
	UCsWidget_Crafting* c	 = Cast<UCsWidget_Crafting>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = c->GetWorld();

	const float CurrentTime = w->GetTimeSeconds();
	const float& StartTime  = r->floats[0];

	const float AutoDecrementTime = c->AutoDecrementTime > 0.0f ? c->AutoDecrementTime : 0.01f;

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			c->PerformDecrementCount();
		}
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= AutoDecrementTime);

		r->floats[0] = CurrentTime;
	} while (true);

	CS_COROUTINE_END(r);
}

void UCsWidget_Crafting::PerformDecrementCount()
{
	if (!CanDecrement())
		return;

	CurrentCount.DecrementValue();
	UpdateRecipeWithSelectedOption();
}

void UCsWidget_Crafting::StopDecrementCount()
{
	if (DecrementCount_Internal_Routine && DecrementCount_Internal_Routine->IsValid())
		DecrementCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

#pragma endregion Decrement

	// Start
#pragma region

void UCsWidget_Crafting::OnStartButtonPressed()
{
	ACsManager_Input* Manager_Input = ACsManager_Input::Get(GetWorld());

	Manager_Input->QueueInput(StartInputAction, ECsInputEvent::FirstPressed);
}

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
	const FName& ShortCode		 = SelectedOptionShortCodes[CurrentSelectedOptionIndex];
	ACsData_Recipe* Recipe		 = Cast<ACsData_Recipe>(DataMapping->GetLoadedData(RecipeAssetType, ShortCode));
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

	// Reset the CurrentCount
	CurrentCount.Value = 0;

	UpdateRecipeWithSelectedOption();
}

#pragma endregion Start

#pragma endregion Options