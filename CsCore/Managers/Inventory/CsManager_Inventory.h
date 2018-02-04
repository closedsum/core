// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Item.h"
#include "CsManager_Inventory.generated.h"

// Add
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnAddItem, FCsItem, Item);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerInventory_OnAddItem, FCsItem*);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnRemoveItem, FCsItem, Item);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManagerInventory_OnRemoveItem, FCsItem*);

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsInventoryTransaction
{
	enum Type
	{
		Add							UMETA(DisplayName = "Add"),
		Remove						UMETA(DisplayName = "Remove"),
		Consume						UMETA(DisplayName = "Consume"),
		Drop						UMETA(DisplayName = "Drop"),
		ECsInventoryTransaction_MAX	UMETA(Hidden),
	};
}

namespace ECsInventoryTransaction
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Add = TCsString(TEXT("Add"), TEXT("add"), TEXT("Adding"));
		const TCsString Remove = TCsString(TEXT("Remove"), TEXT("remove"), TEXT("Removing"));
		const TCsString Consume = TCsString(TEXT("Consume"), TEXT("consume"), TEXT("Consuming"));
		const TCsString Drop = TCsString(TEXT("Drop"), TEXT("drop"), TEXT("Dropping"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Add) { return Str::Add.Value; }
		if (EType == Type::Remove) { return Str::Remove.Value; }
		if (EType == Type::Consume) { return Str::Consume.Value; }
		if (EType == Type::Drop) { return Str::Drop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToActionString(const Type &EType)
	{
		if (EType == Type::Add) { return Str::Add.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Remove) { return Str::Remove.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Consume) { return Str::Consume.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Drop) { return Str::Drop.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Add) { return Type::Add; }
		if (String == Str::Remove) { return Type::Remove; }
		if (String == Str::Consume) { return Type::Consume; }
		if (String == Str::Drop) { return Type::Drop; }
		return Type::ECsInventoryTransaction_MAX;
	}
}

#define ECS_INVENTORY_TRANSACTION_MAX (uint8)ECsInventoryTransaction::ECsInventoryTransaction_MAX
typedef TEnumAsByte<ECsInventoryTransaction::Type> TCsInventoryTransaction;

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
	TArray<FCsItem*> Items_OnlyVisible;

	FCsItemBagSlot(){}
	~FCsItemBagSlot(){}

	void Add(FCsItem* Item)
	{
		Items.Add(Item);

		if (Item->InventoryProperties.Visible)
			Items_OnlyVisible.Add(Item);
	}

	void Remove(FCsItem* Item)
	{
		// All
		{
			const int32 Count = Items.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				if (Item->UniqueId == Items[I]->UniqueId)
				{
					Items.RemoveAt(I);
					break;
				}
			}
		}
		// Only Visible
		if (Item->InventoryProperties.Visible)
		{
			const int32 Count = Items_OnlyVisible.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				if (Item->UniqueId == Items_OnlyVisible[I]->UniqueId)
				{
					Items_OnlyVisible.RemoveAt(I);
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

	TArray<FCsItem*>* Get(const uint8 &Row, const uint8 &Column, const bool &OnlyVisible)
	{
		const uint16 Index = Row * Size.ColumnSpan + Column;

		if (OnlyVisible)
			return &(Slots[Index].Items_OnlyVisible);
		return &(Slots[Index].Items);
	}

	void Add(FCsItem* Item)
	{
		const uint8& Row	= Item->InventoryProperties.Position.Row;
		const uint8& Column = Item->InventoryProperties.Position.Column;
		const uint16 Index  = Row * Size.ColumnSpan + Column;

		Slots[Index].Add(Item);
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

	CS_DECLARE_ITEM_TYPE

	TMap<uint64, FCsItem*> Items;
	TMap<FName, TArray<FCsItem*>> ItemMap;

	uint8 BagCount;

	TArray<FCsItemBag> Bags;

	bool IsEmpty();

	virtual FCsItem* GetItem(const uint64 &Id);
	virtual FCsItem* GetFirstItem(const FName &ShortCode);

	TMap<FName, uint16> ItemCountMap;

	virtual int32 GetItemCount(const FName &ShortCode);

	void IncrementItemCount(const FName &ShortCode);
	void DecrementItemCount(const FName &ShortCode);

	void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsInventoryTransaction::Type> &Transaction, const FCsItem* const Item);

// Add
#pragma region
public:

	virtual void AddItem(FCsItem* Item);
	virtual void AddItems(const TArray<FCsItem*> &ItemsToAdd);

	FBindableEvent_CsManagerInventory_OnAddItem OnAddItem_Event;

	UPROPERTY(BlueprintAssignable, Category = "Add")
	FBindableDynEvent_CsManagerInventory_OnAddItem OnAddItem_ScriptEvent;

#pragma endregion Add

// Remove
#pragma region
private:

	void RemoveItem(const uint64 &Id, const FString &FunctionName, const TEnumAsByte<ECsInventoryTransaction::Type> &Transaction, const bool &ShouldDestroy);
	void RemoveItem(FCsItem* Item, const FString &FunctionName, const TEnumAsByte<ECsInventoryTransaction::Type> &Transaction, const bool &ShouldDestroy);

public:

	FBindableEvent_CsManagerInventory_OnRemoveItem OnRemoveItem_Event;

	UPROPERTY(BlueprintAssignable, Category = "Remove")
	FBindableDynEvent_CsManagerInventory_OnRemoveItem OnRemoveItem_ScriptEvent;

#pragma endregion Remove

// Consume
#pragma region
public:

	virtual void ConsumeItem(const uint64 &Id);
	virtual void ConsumeItem(FCsItem* Item);
	virtual void ConsumeFirstItem(const FName &ShortCode);

#pragma endregion Consume

// Drop
#pragma region
public:

	virtual void DropItem(const uint64 &Id);
	virtual void DropItem(FCsItem* Item);

	virtual FCsItem* DropFirstItem(const FName &ShortCode);

#pragma endregion Drop
};