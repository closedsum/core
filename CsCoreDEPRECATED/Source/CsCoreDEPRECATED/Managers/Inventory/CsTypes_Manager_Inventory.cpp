// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Inventory/CsTypes_Manager_Inventory.h"

// Types
#include "Types/CsTypes_Item.h"

// InventoryTransaction
#pragma region

namespace NCsInventoryTransaction
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Add = EMCsInventoryTransaction::Get().Add(Type::Add, TEXT("Add"));
		CSCOREDEPRECATED_API const Type Remove = EMCsInventoryTransaction::Get().Add(Type::Remove, TEXT("Remove"));
		CSCOREDEPRECATED_API const Type Consume = EMCsInventoryTransaction::Get().Add(Type::Consume, TEXT("Consume"));
		CSCOREDEPRECATED_API const Type Drop = EMCsInventoryTransaction::Get().Add(Type::Drop, TEXT("Drop"));
		CSCOREDEPRECATED_API const Type ECsInventoryTransaction_MAX = EMCsInventoryTransaction::Get().Add(Type::ECsInventoryTransaction_MAX, TEXT("ECsInventoryTransaction_MAX"), TEXT("MAX"));
	}

	CSCOREDEPRECATED_API const uint8 MAX = (uint8)Type::ECsInventoryTransaction_MAX;

	namespace Str
	{
		CSCOREDEPRECATED_API const TCsString Add = TCsString(TEXT("Add"), TEXT("add"), TEXT("Adding"));
		CSCOREDEPRECATED_API const TCsString Remove = TCsString(TEXT("Remove"), TEXT("remove"), TEXT("Removing"));
		CSCOREDEPRECATED_API const TCsString Consume = TCsString(TEXT("Consume"), TEXT("consume"), TEXT("Consuming"));
		CSCOREDEPRECATED_API const TCsString Drop = TCsString(TEXT("Drop"), TEXT("drop"), TEXT("Dropping"));
	}
}

#pragma endregion InventoryTransaction

// InventoryGetRequest
#pragma region

namespace NCsInventoryGetRequest
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type FillAny = EMCsInventoryGetRequest::Get().Add(Type::FillAny, TEXT("FillAny"), TEXT("Fill Any"));
		CSCOREDEPRECATED_API const Type FillOrKill = EMCsInventoryGetRequest::Get().Add(Type::FillOrKill, TEXT("FillOrKill"), TEXT("Fill or Kill"));
		CSCOREDEPRECATED_API const Type ECsInventoryGetRequest_MAX = EMCsInventoryGetRequest::Get().Add(Type::ECsInventoryGetRequest_MAX, TEXT("ECsInventoryGetRequest_MAX"), TEXT("MAX"));
	}

	CSCOREDEPRECATED_API const uint8 MAX = (uint8)Type::ECsInventoryGetRequest_MAX;
}

#pragma endregion InventoryGetRequest

// FCsItemBagSlot
#pragma region

bool FCsItemBagSlot::Add(FCsItem* Item)
{
	const int32 Count = Items.Num();

	if (Count > CS_EMPTY)
	{
		if (Count >= Items[CS_FIRST]->InventoryProperties.Capacity)
			return false;
	}

	Item->InventoryProperties.Position = Position;

	Items.Add(Item);
	return true;
}

void FCsItemBagSlot::Remove(FCsItem* Item)
{
	// All
	{
		const int32 Count = Items.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (Item->Id == Items[I]->Id)
			{
				Items.RemoveAt(I);
				break;
			}
		}
	}
}

#pragma endregion FCsItemBagSlot

// FCsItemBag
#pragma region

void FCsItemBag::Init(const FCsUint8MatrixDimension &InSize)
{
	Size = InSize;

	const int32 Count = Size.RowSpan * Size.ColumnSpan;

	for (int32 I = 0; I < Count; ++I)
	{
		Slots.AddDefaulted();
		Slots[I].Position.Row    = Size.GetRow(I);
		Slots[I].Position.Column = Size.GetColumn(I);
	}
}

TArray<FCsItem*>* FCsItemBag::Get(const uint8 &Row, const uint8 &Column)
{
	const uint16 Index = Row * Size.ColumnSpan + Column;

	return &(Slots[Index].Items);
}

int32 FCsItemBag::GetSlotCount(const uint8 &Row, const uint8 &Column)
{
	TArray<FCsItem*>* Items = Get(Row, Column);

	return Items->Num();
}

bool FCsItemBag::Add(FCsItem* Item)
{
	uint8& Row	  = Item->InventoryProperties.Position.Row;
	uint8& Column = Item->InventoryProperties.Position.Column;

	// If the Row and Column are NOT set, Find the appropriate Slot
	if (Row == CS_INVALID_INVENTORY_ITEM_ROW ||
		Column == CS_INVALID_INVENTORY_ITEM_COLUMN)
	{
		int32 AvailableSlot		= INDEX_NONE;
		bool FilledSlot			= false;
		const uint8 SlotCount = Slots.Num();

		for (uint8 I = 0; I < SlotCount; ++I)
		{
			if (Slots[I].Items.Num() == CS_EMPTY)
			{
				AvailableSlot = I;
				break;
			}
			
			FCsItem* FirstItem = Slots[I].Items[CS_FIRST];

			if (Item->ShortCode == FirstItem->ShortCode)
			{
				return Slots[I].Add(Item);
			}
		}

		if (!FilledSlot)
		{
			if (AvailableSlot == INDEX_NONE)
				return false;
			return Slots[AvailableSlot].Add(Item);
		}
	}
	else
	{
		const uint16 Index = Row * Size.ColumnSpan + Column;

		return Slots[Index].Add(Item);
	}
	return false;
}

void FCsItemBag::Remove(FCsItem* Item)
{
	const uint8& Row    = Item->InventoryProperties.Position.Row;
	const uint8& Column = Item->InventoryProperties.Position.Column;
	const uint16 Index  = Row * Size.ColumnSpan + Column;

	Slots[Index].Remove(Item);
}

#pragma endregion FCsItemBag