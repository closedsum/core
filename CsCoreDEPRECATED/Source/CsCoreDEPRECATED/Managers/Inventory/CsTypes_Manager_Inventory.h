// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "CsTypes_Manager_Inventory.generated.h"
#pragma once

// InventoryTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsInventoryTransaction : uint8
{
	Add							UMETA(DisplayName = "Add"),
	Remove						UMETA(DisplayName = "Remove"),
	Consume						UMETA(DisplayName = "Consume"),
	Drop						UMETA(DisplayName = "Drop"),
	ECsInventoryTransaction_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsInventoryTransaction : public TCsEnumMap<ECsInventoryTransaction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInventoryTransaction, ECsInventoryTransaction)
};

namespace NCsInventoryTransaction
{
	typedef ECsInventoryTransaction Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Add;
		extern CSCOREDEPRECATED_API const Type Remove;
		extern CSCOREDEPRECATED_API const Type Consume;
		extern CSCOREDEPRECATED_API const Type Drop;
		extern CSCOREDEPRECATED_API const Type ECsInventoryTransaction_MAX;
	}

	extern CSCOREDEPRECATED_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSCOREDEPRECATED_API const TCsString Add;
		extern CSCOREDEPRECATED_API const TCsString Remove;
		extern CSCOREDEPRECATED_API const TCsString Consume;
		extern CSCOREDEPRECATED_API const TCsString Drop;
	}

	FORCEINLINE const FString& ToActionString(const Type& EType)
	{
		if (EType == Type::Add) { return Str::Add.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Remove) { return Str::Remove.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Consume) { return Str::Consume.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Drop) { return Str::Drop.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#define ECS_INVENTORY_TRANSACTION_MAX NCsInventoryTransaction::MAX

#pragma endregion InventoryTransaction

// InventoryGetRequest
#pragma region

UENUM(BlueprintType)
enum class ECsInventoryGetRequest : uint8
{
	FillAny						UMETA(DisplayName = "Fill Any"),
	FillOrKill					UMETA(DisplayName = "Fill Or Kill"),
	ECsInventoryGetRequest_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsInventoryGetRequest : public TCsEnumMap<ECsInventoryGetRequest>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInventoryGetRequest, ECsInventoryGetRequest)
};

namespace NCsInventoryGetRequest
{
	typedef ECsInventoryGetRequest Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type FillAny;
		extern CSCOREDEPRECATED_API const Type FillOrKill;
		extern CSCOREDEPRECATED_API const Type ECsInventoryGetRequest_MAX;
	}

	extern CSCOREDEPRECATED_API const uint8 MAX;
}

#define ECS_INVENTORY_GET_REQUEST_MAX NCsInventoryGetRequest::MAX

#pragma endregion InventoryG`etRequest

// FCsItemBagSlot
#pragma region

struct FCsItem;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemBagSlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FCsUint8MatrixCoordinate Position;

	TArray<FCsItem*> Items;

	FCsItemBagSlot(){}
	~FCsItemBagSlot(){}

	bool Add(FCsItem* Item);

	void Remove(FCsItem* Item);
};

#pragma endregion FCsItemBagSlot

// FCsItemBag
#pragma region

#define CS_INVALID_MANAGER_INVENTORY_ITEM_ROW 255
#define CS_INVALID_MANAGER_INVENTORY_ITEM_COLUMN 255

struct FCsItem;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemBag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FCsUint8MatrixDimension Size;

	UPROPERTY()
	TArray<FCsItemBagSlot> Slots;

	FCsItemBag() {}
	~FCsItemBag() {}

	void Init(const FCsUint8MatrixDimension &InSize)
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

	TArray<FCsItem*>* Get(const uint8 &Row, const uint8 &Column)
	{
		const uint16 Index = Row * Size.ColumnSpan + Column;

		return &(Slots[Index].Items);
	}

	int32 GetSlotCount(const uint8 &Row, const uint8 &Column)
	{
		TArray<FCsItem*>* Items = Get(Row, Column);

		return Items->Num();
	}

	bool Add(FCsItem* Item)
	{
		uint8& Row	  = Item->InventoryProperties.Position.Row;
		uint8& Column = Item->InventoryProperties.Position.Column;

		// If the Row and Column are NOT set, Find the appropriate Slot
		if (Row == CS_INVALID_MANAGER_INVENTORY_ITEM_ROW ||
			Column == CS_INVALID_MANAGER_INVENTORY_ITEM_COLUMN)
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

	void Remove(FCsItem* Item)
	{
		const uint8& Row    = Item->InventoryProperties.Position.Row;
		const uint8& Column = Item->InventoryProperties.Position.Column;
		const uint16 Index  = Row * Size.ColumnSpan + Column;

		Slots[Index].Remove(Item);
	}
};

#pragma endregion FCsItemBag