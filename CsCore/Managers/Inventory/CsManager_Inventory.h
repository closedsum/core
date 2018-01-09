// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Item.h"
#include "CsManager_Inventory.generated.h"


UCLASS()
class CSCORE_API ACsManager_Inventory : public AActor
{
	GENERATED_UCLASS_BODY()

	static ACsManager_Inventory* Get(UWorld* InWorld);

	TWeakObjectPtr<AActor> MyOwner;

	AActor* GetMyOwner();

	TMap<uint64, FCsItem*> Items;
	TMap<TCsItemType, TArray<FCsItem*>> ItemMap;

	virtual FCsItem* GetItem(const uint64 &Id);
	virtual FCsItem* GetFirstItem(const TCsItemType &ItemType);

	virtual int32 GetItemCount(const TCsItemType &ItemType);

	virtual void RemoveItem(const uint64 &Id, const bool &ShouldDestroy);
	virtual void RemoveItem(FCsItem* Item, const bool &ShouldDestroy);

	virtual void ConsumeItem(const uint64 &Id);
	virtual void ConsumeItem(FCsItem* Item);
};