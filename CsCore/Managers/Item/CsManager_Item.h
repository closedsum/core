// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_Item.h"
#include "Types/CsTypes_Load.h"
#include "CsManager_Item.generated.h"

// PopulateExistingItems
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsManagerItem_OnPopulateExistingItems);
DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsManagerItem_OnPopulateExistingItems);
// InitInventory
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsManagerItem_OnInitInventory);
DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsManagerItem_OnInitInventory);

#define CS_ITEM_POOL_SIZE 65535
#define CS_ITEM_UNIQUE_ID_START_INDEX 65535

UCLASS()
class CSCORE_API ACsManager_Item : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	static ACsManager_Item* Get(UWorld* InWorld);

	CS_DECLARE_ITEM_TYPE
	CS_DECLARE_ITEM_OWNER

	UPROPERTY()
	uint64 UniqueIdIndex;

	TArray<uint64> AvailableUnqiueIds;

	virtual uint64 GetUniqueId();

	FCsItem Pool[CS_ITEM_POOL_SIZE];

	uint16 PoolIndex;

	void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, const FCsItem* const Item);

	TCsAssetType ItemAssetType;
	TCsAssetType InteractiveAssetType;

private:

	FCsItem* Allocate_Internal();

public:

	virtual FCsItem* Allocate();
	virtual FCsItem* Allocate(const FName &ShortCode);

	virtual void SetItemOwnerInfo(FCsItem* Item, UObject* ItemOwner);

	virtual FCsItem* Allocate(const FName &ShortCode, UObject* ItemOwner);

	TMap<uint64, FCsItem*> ActiveItems;
	TMap<uint64, TArray<FCsItem*>> ActiveItemsByOwnerId;

	void AddActiveItemByOwnerId(FCsItem* Item);

	void ChangeActiveItemOwnerInfo(FCsItem* Item, UObject* ItemOwner);

	virtual void SetActiveItemData(FCsItem* Item);

// Get
#pragma region
public:

	virtual FCsItem* GetItem(const uint64 &Id);

	void GetItemsByOwnerType(const TCsItemOwner &OwnerTyper, TArray<FCsItem*> &OutItems);
	void GetItemsByOwnerId(const uint64 &OwnerId, TArray<FCsItem*> &OutItems);

	void GetItems(const TArray<uint64> &Ids, TArray<FCsItem*> &OutItems);

#pragma endregion Get

// DeAllocate
#pragma region
public:

	virtual void DeAllocate(const uint64 &Id);
	virtual void DeAllocate(FCsItem* Item);

#pragma endregion DeAllocate

// Transfer
#pragma region
public:

	virtual bool Transfer(FCsItem* Item, UObject* Instigator);
	virtual bool Transfer(TArray<FCsItem*> &Items, UObject* Instigator, const TCsPoolTransactionOrder &Order);
	bool Transfer_Internal(FCsItem* Item, UObject* Instigator, class ACsManager_Inventory* Manager_Inventory);

#pragma endregion Transfer

// Save / Load
#pragma region
public:

	void SetItemFileName(FCsItem* Item);

	UPROPERTY()
	FString RootSaveDirectory;

	void SetRootSaveDirectory(const FString &Directory);

	UPROPERTY()
	FString SaveDirectory;
	UPROPERTY()
	FString CombinedSaveDirectory;

	FString GetSavePath();

	virtual void Save(FCsItem* Item);
	virtual void SaveHistory(TSharedRef<TJsonWriter<TCHAR>> &JsonWriter, FCsItemHistory* ItemHistory);

	virtual void PopulateExistingItems();
	virtual void AsyncPopulateExistingItems();

	FBindableEvent_CsManagerItem_OnPopulateExistingItems OnPopulateExistingItems_Event;

	UPROPERTY(BlueprintAssignable, Category = "Load")
	FBindableDynEvent_CsManagerItem_OnPopulateExistingItems OnPopulateExistingItems_ScriptEvent;

	virtual void LoadHistory(TSharedPtr<class FJsonObject> &JsonObject, FCsItem* Item, FCsItemHistory* ItemHistory);

	virtual void InitInventory(class ACsManager_Inventory* Manager_Inventory);
	virtual void AsyncInitInventory(class ACsManager_Inventory* Manager_Inventory);

	FBindableEvent_CsManagerItem_OnInitInventory OnInitInventory_Event;

	UPROPERTY(BlueprintAssignable, Category = "Load")
	FBindableDynEvent_CsManagerItem_OnInitInventory OnInitInventory_ScriptEvent;

#pragma endregion Save / Load
};