// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Item/CsManager_Item.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

ACsManager_Item::ACsManager_Item(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UniqueIdIndex = CS_ITEM_UNIQUE_ID_START_INDEX;
}

/*static*/ ACsManager_Item* ACsManager_Item::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Item;
}

uint64 ACsManager_Item::GetUniqueId()
{
	const uint64 Size = AvailableUnqiueIds.Num();

	if (Size > CS_EMPTY)
	{
		const uint64 Id = AvailableUnqiueIds[Size - 1];
		AvailableUnqiueIds.RemoveAt(Size - 1);
		return Id;
	}
	UniqueIdIndex++;
	return UniqueIdIndex;
}

FCsItem* ACsManager_Item::Allocate()
{
	for (uint16 I = 0; I < CS_ITEM_POOL_SIZE; ++I)
	{
		const uint16 Index = (PoolIndex + I) % CS_ITEM_POOL_SIZE;
		FCsItem* Item	   = &(Pool[Index]);

		if (Item->Index == CS_ITEM_POOL_INVALID_INDEX)
			Item->Init(I);

		if (!Item->IsAllocated)
		{
			Item->IsAllocated = true;
			Item->UniqueId	  = GetUniqueId();
			ActiveItems.Add(Item->UniqueId, Item);
			return Item;
		}
	}
	checkf(0, TEXT("ACsManager_Item::Allocate: Pool is exhausted"));
	return nullptr;
}

FCsItem* ACsManager_Item::Allocate(const TCsItemType &ItemType)
{
	return nullptr;
}

FCsItem* ACsManager_Item::GetItem(const uint64 &Id)
{
	return *(ActiveItems.Find(Id));
}

void ACsManager_Item::DeAllocate(FCsItem* Item)
{
	AvailableUnqiueIds.Add(Item->UniqueId);
	Item->Reset();
}