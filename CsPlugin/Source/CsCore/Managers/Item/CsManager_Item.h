// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Types
#include "Types/Property/Ref/CsProperty_Ref_bool.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_Item.h"
#include "Types/CsTypes_Load.h"
#include "CsManager_Item.generated.h"

// PopulateExistingItems
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsManagerItem_OnPopulateExistingItems);
// InitInventory
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsManagerItem_OnInitInventory);

#define CS_ITEM_POOL_SIZE 65535
#define CS_ITEM_UNIQUE_ID_START_INDEX 65535
#define CS_ITEM_ASYNC_SAVE_POOL_SIZE 256

UCLASS()
class CSCORE_API ACsManager_Item : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	static ACsManager_Item* Get(UWorld* InWorld);

	virtual void Rebuild();

	virtual void OnTick(const float& DeltaSeconds);

// Product
#pragma region
public:

	// TODO: Maybe this should be in the GameInstance?
	
	UPROPERTY()
	FString ProductName;
		
	UPROPERTY()
	FGuid ProductId;

#pragma endregion Product

	virtual FGuid GetUniqueId();

	FCsItem Pool[CS_ITEM_POOL_SIZE];

	uint16 PoolIndex;

	void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, const FCsItem* const Item);

	FECsDataType ItemDataType;
	FECsDataType InteractiveDataType;

// Allocate
#pragma region

private:

	FCsItem* Allocate_Internal();

public:

	virtual FCsItem* Allocate();
	virtual FCsItem* Allocate(const FName& ShortCode);

	virtual void SetItemOwnerInfo(FCsItem* Item, UObject* ItemOwner);

	virtual FCsItem* Allocate(const FName& ShortCode, UObject* ItemOwner);

	TMap<TCsItemId, FCsItem*> ActiveItems;
	TMap<TCsItemOwnerId, TArray<FCsItem*>> ActiveItemsByOwnerId;

	void AddActiveItemByOwnerId(FCsItem* Item);

	void ChangeActiveItemOwnerInfo(FCsItem* Item, UObject* ItemOwner);

	virtual void SetActiveItemData(FCsItem* Item);

#pragma endregion Allocate

// Get
#pragma region
public:

	virtual FCsItem* GetItem(const TCsItemId& Id);

	void GetItemsByOwnerType(const FECsItemOwner& OwnerTyper, TArray<FCsItem*>& OutItems);
	void GetItemsByOwnerId(const TCsItemOwnerId& OwnerId, TArray<FCsItem*>& OutItems);

	void GetItems(const TArray<TCsItemId>& Ids, TArray<FCsItem*>& OutItems);

#pragma endregion Get

// DeAllocate
#pragma region
public:

	virtual void DeAllocate(const TCsItemId& Id);
	virtual void DeAllocate(FCsItem* Item);

	TArray<FCsItem*> DeAllocateQueue;

	void OnTick_Handle_DeAllocateQueue();

#pragma endregion DeAllocate

// Transfer
#pragma region
public:

	bool Transfer_Internal(FCsItem* Item, UObject* Instigator, class ACsManager_Inventory* Manager_Inventory);
	virtual bool Transfer(FCsItem* Item, UObject* Instigator);
	virtual bool Transfer(TArray<FCsItem*>& Items, UObject* Instigator, const ECsPoolTransactionOrder& Order);

#pragma endregion Transfer

// Save / Load
#pragma region
public:

	void SetItemFileName(FCsItem* Item);

	UPROPERTY()
	FString RootSaveDirectory;

	void SetRootSaveDirectory(const FString& Directory);

	UPROPERTY()
	FString SaveDirectory;
	UPROPERTY()
	FString CombinedSaveDirectory;

	FString GetSavePath();

	virtual void Save(FCsItem* Item);
	virtual void SaveProduct(TSharedRef<TJsonWriter<TCHAR>>& JsonWriter, FCsItemProduct* Product);
	virtual void SaveHistory(TSharedRef<TJsonWriter<TCHAR>>& JsonWriter, FCsItemHistory* ItemHistory);

	void SaveActiveItems();
	
	// Async
#pragma region
private:

	FCsItem AsyncSavePool[CS_ITEM_ASYNC_SAVE_POOL_SIZE];

	uint8 AsyncSavePoolIndex;

public:

	FCsItem* AllocateAsyncSave();

	TArray<FCsItem*> AsyncSaveItems;
	TArray<FCsItem*> ActiveAsyncSaveItems;
	TArray<FCsItem*> CopiedAsyncSaveItems;

	void AddAsyncSave(FCsItem* Item);
	void AsyncSave();

	bool PerformingAsyncSave;
	TCsBool_Ref PerformingAsyncSaveHandle;

	void OnTick_Handle_AsyncSave();

#pragma endregion Async

public:

	virtual void PopulateExistingItems();
	virtual void AsyncPopulateExistingItems();

	DECLARE_MULTICAST_DELEGATE(OnPopulateExistingItems);

	OnPopulateExistingItems OnPopulateExistingItems_Event;

	UPROPERTY(BlueprintAssignable, Category = "Load")
	FBindableDynEvent_CsManagerItem_OnPopulateExistingItems OnPopulateExistingItems_ScriptEvent;

	virtual void LoadProduct(TSharedPtr<class FJsonObject>& JsonObject, FCsItem* Item, FCsItemProduct* Product);
	virtual void LoadHistory(TSharedPtr<class FJsonObject>& JsonObject, FCsItem* Item, FCsItemHistory* ItemHistory);

	virtual void InitInventory(class ACsManager_Inventory* Manager_Inventory);
	virtual void AsyncInitInventory(class ACsManager_Inventory* Manager_Inventory);

	DECLARE_MULTICAST_DELEGATE(OnInitInventory);

	OnInitInventory OnInitInventory_Event;

	UPROPERTY(BlueprintAssignable, Category = "Load")
	FBindableDynEvent_CsManagerItem_OnInitInventory OnInitInventory_ScriptEvent;

#pragma endregion Save / Load

// Action
#pragma region
public:

	void RecordItemsInteraction(const TArray<FCsItem*>& Items, const FECsItemInteraction& Interaction);
	virtual void RecordItemInteraction(FCsItem* Item, const FECsItemInteraction& Interaction);

#pragma endregion Action
};