// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "UI/Crafting/CsWidget_Crafting_Grid.h"
#include "UI/Crafting/CsWidget_Crafting_Slot.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"

#include "Coroutine/CsCoroutineScheduler.h"

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
		const FName CraftItem_Internal = FName("UCsWidget_Crafting::CraftItem_Internal");
	};
}

namespace ECsWidgetCraftingCachedString
{
	namespace Str
	{
		// Functions
		const FString CraftItem_Internal = TEXT("UCsWidget_Crafting::CraftItem_Internal");
	};
}

#pragma endregion Cache

UCsWidget_Crafting::UCsWidget_Crafting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Crafting::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	Options_ComboBox->OnSelectionChanged.AddDynamic(this, &UCsWidget_Crafting::OnRecipeSelectionChanged);
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

void UCsWidget_Crafting::OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType)
{
	// Get Data for selected Recipe
	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	const FName RecipeShortCode	= FName(*SelectedItem);
	ACsData_Recipe* Recipe		= Cast<ACsData_Recipe>(DataMapping->GetLoadedData(RecipeAssetType, RecipeShortCode));
	// Update Grid with the Ingredients (Items)
	MyGrid->Clear();

	TArray<FCsRecipeIngredient>* Ingredients = Recipe->GetIngredients();

	const int32 Count = FMath::Min((int32)MyGrid->Dimension.GetSize(), Ingredients->Num());

	for (int32 I = 0; I < Count; ++I)
	{
		UCsWidget_Crafting_Slot* CurrentSlot = MyGrid->Slots[I];
		const FName ItemShortCode			 = (*Ingredients)[I].ShortCode;
		ACsData_Item* Item					 = Cast<ACsData_Item>(DataMapping->GetLoadedData(ItemAssetType, ItemShortCode));

		CurrentSlot->DisplayName = Item->GetDisplayName();
		CurrentSlot->Count		 = CurrentCount.Value.Get() * (*Ingredients)[I].Count;

		CurrentSlot->UpdateDisplayNameWithCurrentCount();
		CurrentSlot->SetImage(Item->GetMaterial());
	}
}

// Routines
#pragma region

bool UCsWidget_Crafting::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::AddRoutine_Internal(Routine, Type))
		return true;

	const TCsWidgetCraftingRoutine RoutineType = (TCsWidgetCraftingRoutine)Type;

	// CraftItem_Internal
	if (RoutineType == ECsWidgetCraftingRoutine::CraftItem_Internal)
	{
		CraftItem_Internal_Routine = Routine;
		return true;
	}
	return false;
}

bool UCsWidget_Crafting::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::RemoveRoutine_Internal(Routine, Type))
		return true;

	const TCsWidgetCraftingRoutine RoutineType = (TCsWidgetCraftingRoutine)Type;

	// CraftItem_Internal
	if (RoutineType == ECsWidgetCraftingRoutine::CraftItem_Internal)
	{
		check(CraftItem_Internal_Routine == Routine);
		CraftItem_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

void UCsWidget_Crafting::CraftItem()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		 = Schedule;
	Payload->Function		 = &UCsWidget_Crafting::CraftItem_Internal;
	Payload->Object			 = this;
	Payload->Stop			 = &UCsCommon::CoroutineStopCondition_CheckObject;
	Payload->Add			 = &UCsUserWidget::AddRoutine;
	Payload->Remove			 = &UCsUserWidget::RemoveRoutine;
	Payload->Type			 = (uint8)ECsWidgetCraftingRoutine::CraftItem_Internal;
	Payload->DoInit			 = true;
	Payload->PerformFirstRun = false;
	Payload->Name			 = ECsWidgetCraftingCachedName::Name::CraftItem_Internal;
	Payload->NameAsString	 = ECsWidgetCraftingCachedString::Str::CraftItem_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsWidget_Crafting, CraftItem_Internal)
{
	UCsWidget_Crafting* wc   = Cast<UCsWidget_Crafting>(r->GetRObject());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = wc->GetWorld();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}