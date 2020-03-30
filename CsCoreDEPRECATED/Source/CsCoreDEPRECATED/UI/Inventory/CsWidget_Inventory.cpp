// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory.h"
#include "CsCore.h"

#include "UI/Inventory/CsWidget_Inventory_Grid.h"
#include "UI/Inventory/CsWidget_Inventory_Slot.h"

// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
// Data
#include "Data/CsData_Item.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"

UCsWidget_Inventory::UCsWidget_Inventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Inventory::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	Slot_Draggable->SetVisibility(ESlateVisibility::Hidden);
}

void UCsWidget_Inventory::Init()
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

ACsManager_Inventory* UCsWidget_Inventory::GetMyManager_Inventory()
{
	return MyManager_Inventory.IsValid() ? MyManager_Inventory.Get() : nullptr;
}

void UCsWidget_Inventory::UpdateGrid()
{
	// Update UI from current Inventory
	ACsManager_Inventory* Manager_Inventory = GetMyManager_Inventory();

	// Clear Slots and then "rebuild" Slot with latest item information
	const int32 SlotCount = MyGrid->Slots.Num();

	for (int32 I = 0; I < SlotCount; ++I)
	{
		MyGrid->Slots[I]->Empty();
	}
	// Go through inventory and determine which Item should go in which Slot
	TArray<FName> Keys;
	Manager_Inventory->ItemMap.GetKeys(Keys);

	const int32 KeyCount = Keys.Num();

	for (int32 I = 0; I < KeyCount; ++I)
	{
		const FName& Key = Keys[I];

		TArray<FCsItem*>* ItemsPtr = Manager_Inventory->ItemMap.Find(Key);

		const int32 ItemCount = ItemsPtr->Num();

		for (int32 J = 0; J < ItemCount; ++J)
		{
			FCsItem* Item = (*ItemsPtr)[J];

			// If NOT Visible, do NOT place in a Bag
			if (!Item->InventoryProperties.IsVisible())
				continue;
			// If NOT the matching Bag, SKIP
			if (Item->InventoryProperties.Bag != Bag)
				continue;

			const uint8& Row		= Item->InventoryProperties.Position.Row;
			const uint8& Column		= Item->InventoryProperties.Position.Column;
			const uint8& ColumnSpan = MyGrid->Dimension.ColumnSpan;
			const uint8 Index		= Row * ColumnSpan + Column;

			UCsWidget_Inventory_Slot* CurrentSlot = MyGrid->Slots[Index];

			// Set Data for Slot starting to be populated
			if (CurrentSlot->Count == CS_EMPTY)
			{
				UCsData_Item* Data = Item->GetData();
				CurrentSlot->MyData = Data;

				CurrentSlot->SetImage(Data->GetMaterial());
			}
			CurrentSlot->Count++;
		}
	}
	// Update Slot
	for (int32 I = 0; I < SlotCount; ++I)
	{
		UCsWidget_Inventory_Slot* CurrentSlot = MyGrid->Slots[I];

		CurrentSlot->UpdateCurrentCount();
	}
}

void UCsWidget_Inventory::OnAddItem(FCsItem* Item)
{
	if (!Item->InventoryProperties.IsVisible())
		return;

	const uint8& Row		= Item->InventoryProperties.Position.Row;
	const uint8& Column		= Item->InventoryProperties.Position.Column;
	const uint8& ColumnSpan = MyGrid->Dimension.ColumnSpan;
	const uint8 Index		= Row * ColumnSpan + Column;

	MyGrid->Slots[Index]->AddItem(Item);
}

void UCsWidget_Inventory::OnRemoveItem(FCsItem* Item)
{
	if (!Item->InventoryProperties.IsVisible())
		return;

	const uint8& Row		= Item->InventoryProperties.Position.Row;
	const uint8& Column		= Item->InventoryProperties.Position.Column;
	const uint8& ColumnSpan = MyGrid->Dimension.ColumnSpan;
	const uint8 Index		= Row * ColumnSpan + Column;

	MyGrid->Slots[Index]->RemoveItem(Item);
}

void UCsWidget_Inventory::OnHideItem(FCsItem* Item)
{
	const uint8& Row		= Item->InventoryProperties.Position.Row;
	const uint8& Column		= Item->InventoryProperties.Position.Column;
	const uint8& ColumnSpan = MyGrid->Dimension.ColumnSpan;
	const uint8 Index		= Row * ColumnSpan + Column;

	MyGrid->Slots[Index]->RemoveItem(Item);
}