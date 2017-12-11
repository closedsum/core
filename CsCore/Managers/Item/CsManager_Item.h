// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
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

	UPROPERTY()
	uint64 UniqueIdIndex;

	TArray<uint64> AvailableUnqiueIds;

	virtual uint64 GetUniqueId();

	FCsItem Pool[CS_ITEM_POOL_SIZE];

	uint16 PoolIndex;

	virtual FCsItem* Allocate();
	virtual FCsItem* Allocate(const TCsItemType &ItemType);

	TMap<uint64, FCsItem*> ActiveItems;

	virtual FCsItem* GetItem(const uint64 &Id);

	virtual void DeAllocate(const uint64 &Id);
	virtual void DeAllocate(FCsItem* Item);

	virtual void PopulateExistingItems();
	virtual void LoadCurrentHistory(TSharedPtr<class FJsonObject> &JsonParsed, FCsItem* Item);
	virtual void LoadPreviousHistories(TSharedPtr<class FJsonObject> &JsonParsed, FCsItem* Item);

	virtual void InitInventory(class ACsManager_Inventory* Manager_Inventory);
};