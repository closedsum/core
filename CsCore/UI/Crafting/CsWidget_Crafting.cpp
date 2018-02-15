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

UCsWidget_Crafting::UCsWidget_Crafting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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

	const int32 Count = FMath::Min((int32)MyGrid->Dimension.GetSize(), Ingredients->Num());

	for (int32 I = 0; I < Count; ++I)
	{
		const FCsRecipeIngredient& Ingredient = (*Ingredients)[I];
		const FName& ItemShortCode = Ingredient.ShortCode;
		ACsData_Item* Item = Cast<ACsData_Item>(DataMapping->GetLoadedData(ItemAssetType, ItemShortCode));

		UCsWidget_Crafting_Slot* CurrentSlot = MyGrid->Slots[I];

		CurrentSlot->DisplayName = Item->GetDisplayName();
		CurrentSlot->Count = CurrentCount.Value.Get() * Ingredient.Count;

		CurrentSlot->UpdateDisplayNameWithCurrentCount();
		CurrentSlot->SetImage(Item->GetMaterial());
	}
}

void UCsWidget_Crafting::OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType)
{
	const FName ShortCode = FName(*SelectedItem);

	SetRecipe(ShortCode);
}

	// Increment
#pragma region

void UCsWidget_Crafting::OnIncrementButtonPressed()
{

}

void UCsWidget_Crafting::OnIncrementButtonReleased()
{
	if (IncrementCount_Internal_Routine && IncrementCount_Internal_Routine->IsValid())
		IncrementCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

void UCsWidget_Crafting::IncrementCount()
{

}

CS_COROUTINE(UCsWidget_Crafting, IncrementCount_Internal)
{
	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}

#pragma endregion Increment

	// Count
#pragma region

void UCsWidget_Crafting::OnCountValueChanged(float InValue)
{
	CurrentCount.SetValue(FMath::FloorToInt(InValue));

	const FName ShortCode = FName(*(Options_ComboBox->GetSelectedOption()));

	SetRecipe(ShortCode);
}

void UCsWidget_Crafting::OnCountValueCommitted(float InValue, ETextCommit::Type CommitMethod)
{
	CurrentCount.SetValue(FMath::FloorToInt(InValue));

	const FName ShortCode = FName(*(Options_ComboBox->GetSelectedOption()));

	SetRecipe(ShortCode);
}

#pragma endregion Count

// Decrement
#pragma region

void UCsWidget_Crafting::OnDecrementButtonPressed()
{

}

void UCsWidget_Crafting::OnDecrementButtonReleased()
{
	if (DecrementCount_Internal_Routine && DecrementCount_Internal_Routine->IsValid())
		DecrementCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

void UCsWidget_Crafting::DecrementCount()
{

}

CS_COROUTINE(UCsWidget_Crafting, DecrementCount_Internal)
{
	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}

#pragma endregion Decrement

	// Start
#pragma region

void UCsWidget_Crafting::OnStartButtonPressed()
{
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