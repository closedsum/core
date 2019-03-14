// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Item.h"
#include "CsManager_Inventory.generated.h"

// Add
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnAddItem, FCsItem, Item);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnRemoveItem, FCsItem, Item);
// Hide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnHideItem, FCsItem, Item);

// Enums
#pragma region

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

struct CSCORE_API EMCsInventoryTransaction : public TCsEnumMap<ECsInventoryTransaction>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsInventoryTransaction)
};

namespace NCsInventoryTransaction
{
	typedef ECsInventoryTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Add;
		extern CSCORE_API const Type Remove;
		extern CSCORE_API const Type Consume;
		extern CSCORE_API const Type Drop;
		extern CSCORE_API const Type ECsInventoryTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSCORE_API const TCsString Add;
		extern CSCORE_API const TCsString Remove;
		extern CSCORE_API const TCsString Consume;
		extern CSCORE_API const TCsString Drop;
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

struct CSCORE_API EMCsInventoryGetRequest : public TCsEnumMap<ECsInventoryGetRequest>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsInventoryGetRequest)
};

namespace NCsInventoryGetRequest
{
	typedef ECsInventoryGetRequest Type;

	namespace Ref
	{
		extern CSCORE_API const Type FillAny;
		extern CSCORE_API const Type FillOrKill;
		extern CSCORE_API const Type ECsInventoryGetRequest_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_INVENTORY_GET_REQUEST_MAX NCsInventoryGetRequest::MAX

#pragma endregion InventoryGetRequest

#pragma endregion Enums

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsItemBagSlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FCsUint8MatrixCoordinate Position;

	TArray<FCsItem*> Items;

	FCsItemBagSlot(){}
	~FCsItemBagSlot(){}

	bool Add(FCsItem* Item)
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

	void Remove(FCsItem* Item)
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
};

USTRUCT(BlueprintType)
struct FCsItemBag
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

	void Remove(FCsItem* Item)
	{
		const uint8& Row    = Item->InventoryProperties.Position.Row;
		const uint8& Column = Item->InventoryProperties.Position.Column;
		const uint16 Index  = Row * Size.ColumnSpan + Column;

		Slots[Index].Remove(Item);
	}
};

#pragma endregion Structs

UCLASS()
class CSCORE_API ACsManager_Inventory : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

	static ACsManager_Inventory* Get(UWorld* InWorld);

	TWeakObjectPtr<AActor> MyOwner;

	AActor* GetMyOwner();

	TMap<TCsItemId, FCsItem*> Items;
	TMap<FName, TArray<FCsItem*>> ItemMap;

	uint8 BagCount;

	TArray<FCsItemBag> Bags;

	int32 GetSlotCount(const uint8& Bag, const uint8& Row, const uint8& Column);

	bool IsEmpty();
	bool IsFull(const uint8& Bag, const FName& ShortCode);

	virtual FCsItem* GetItem(const TCsItemId& Id);
	virtual FCsItem* GetFirstItem(const FName& ShortCode);

	void GetItems(const FName& ShortCode, const int32& Count, const ECsInventoryGetRequest& Request, TArray<FCsItem*>& OutItems);
	void GetItems(const FName& ShortCode, const int32& Count, const ECsInventoryGetRequest& Request, const int32& State, TArray<FCsItem*>& OutItems);
	void GetItems(const TArray<TCsItemId>& Ids, TArray<FCsItem*>& OutItems);

	TMap<FName, uint16> ItemCountMap;

	int32 GetItemCount(const FName& ShortCode);
	int32 GetItemCount(const FName& ShortCode, const int32& State);

	void IncrementItemCount(const FName& ShortCode);
	void DecrementItemCount(const FName& ShortCode);

	void LogTransaction(const FString& FunctionName, const ECsInventoryTransaction& Transaction, const FCsItem* const Item);

	virtual uint8 GetFirstAvailableBagIndex(const FECsItemType& ItemType);

// Add
#pragma region
public:

	virtual void AddItem(FCsItem* Item);
	virtual void AddItems(const TArray<FCsItem*>& ItemsToAdd);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddItem, FCsItem*);

	FOnAddItem OnAddItem_Event;

	UPROPERTY(BlueprintAssignable, Category = "Add")
	FBindableDynEvent_CsManagerInventory_OnAddItem OnAddItem_ScriptEvent;

#pragma endregion Add

// Remove
#pragma region
private:

	void RemoveItem(const TCsItemId& Id, const FString& FunctionName, const ECsInventoryTransaction& Transaction, const bool& ShouldDestroy);
	void RemoveItem(FCsItem* Item, const FString& FunctionName, const ECsInventoryTransaction& Transaction, const bool& ShouldDestroy);

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoveItem, FCsItem*);

	FOnRemoveItem OnRemoveItem_Event;

	UPROPERTY(BlueprintAssignable, Category = "Remove")
	FBindableDynEvent_CsManagerInventory_OnRemoveItem OnRemoveItem_ScriptEvent;

#pragma endregion Remove

// Consume
#pragma region
private:

	void ConsumeItem_Internal(const TCsItemId& Id);

public:

	virtual void ConsumeItem(FCsItem* Item, TArray<FCsItem*>& OutResultingItems);
	virtual void ConsumeItem(FCsItem* Item);
	virtual void ConsumeFirstItem(const FName& ShortCode, TArray<FCsItem*>& OutResultingItems);
	virtual void ConsumeFirstItem(const FName& ShortCode);

#pragma endregion Consume

// Drop
#pragma region
private:

	virtual void DropItem_Internal(const TCsItemId& Id);

public:

	virtual void DropItem(FCsItem* Item);

	virtual FCsItem* DropFirstItem(const FName& ShortCode);

#pragma endregion Drop

// Hide
#pragma region
public:

	void HideItem(FCsItem* Item);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHideItem, FCsItem*);

	FOnHideItem OnHideItem_Event;

	UPROPERTY(BlueprintAssignable, Category = "Hide")
	FBindableDynEvent_CsManagerInventory_OnHideItem OnHideItem_ScriptEvent;

#pragma endregion Hide
};