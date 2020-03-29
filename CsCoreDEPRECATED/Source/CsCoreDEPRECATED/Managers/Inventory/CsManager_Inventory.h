// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Types
#include "Types/CsTypes_Item.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"
#include "Managers/Inventory/CsTypes_Manager_Inventory.h"

#include "CsManager_Inventory.generated.h"

// Add
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnAddItem, FCsItem, Item);
// Remove
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnRemoveItem, FCsItem, Item);
// Hide
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInventory_OnHideItem, FCsItem, Item);

UCLASS()
class CSCOREDEPRECATED_API ACsManager_Inventory : public AActor
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