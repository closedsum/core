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

	CS_DECLARE_ITEM_TYPE

	TMap<uint64, FCsItem*> Items;
	TMap<FName, TArray<FCsItem*>> ItemMap;

	bool IsEmpty();

	virtual FCsItem* GetItem(const uint64 &Id);
	virtual FCsItem* GetFirstItem(const FName &ShortCode);

	TMap<FName, uint16> ItemCountMap;

	virtual int32 GetItemCount(const FName &ShortCode);

	void IncrementItemCount(const FName &ShortCode);
	void DecrementItemCount(const FName &ShortCode);

	virtual void AddItem(FCsItem* Item);
	virtual void AddItems(const TArray<FCsItem*> &ItemsToAdd);

// Remove
#pragma region
private:

	void RemoveItem(const uint64 &Id, const bool &ShouldDestroy);
	void RemoveItem(FCsItem* Item, const bool &ShouldDestroy);

#pragma endregion Remove

// Consume
#pragma region
public:

	virtual void ConsumeItem(const uint64 &Id);
	virtual void ConsumeItem(FCsItem* Item);

	virtual FCsItem* ConsumeFirstItem(const FName &ShortCode);

#pragma endregion Consume

// Drop
#pragma region
public:

	virtual void DropItem(const uint64 &Id);
	virtual void DropItem(FCsItem* Item);

	virtual FCsItem* DropFirstItem(const FName &ShortCode);

#pragma endregion Drop
};