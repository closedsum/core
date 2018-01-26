// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Item.h"
#include "CsManager_Item.generated.h"

#define CS_ITEM_POOL_SIZE 65535
#define CS_ITEM_UNIQUE_ID_START_INDEX 65535

UCLASS()
class CSCORE_API ACsManager_Item : public AActor
{
	GENERATED_UCLASS_BODY()

	static ACsManager_Item* Get(UWorld* InWorld);

	CS_DECLARE_ITEM_TYPE
	CS_DECLARE_ITEM_OWNER

	UPROPERTY()
	uint64 UniqueIdIndex;

	TArray<uint64> AvailableUnqiueIds;

	virtual uint64 GetUniqueId();

	FCsItem Pool[CS_ITEM_POOL_SIZE];

	uint16 PoolIndex;

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

	virtual void Transfer(FCsItem* Item, UObject* Instigator);

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
	virtual void LoadHistory(TSharedPtr<class FJsonObject> &JsonObject, FCsItem* Item, FCsItemHistory* ItemHistory);

	virtual void InitInventory(class ACsManager_Inventory* Manager_Inventory);

#pragma endregion Save / Load
};