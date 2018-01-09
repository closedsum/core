// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Inventory/CsManager_Inventory.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

// Managers
#include "Managers/Item/CsManager_Item.h"

ACsManager_Inventory::ACsManager_Inventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

/*static*/ ACsManager_Inventory* ACsManager_Inventory::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Inventory;
}

AActor* ACsManager_Inventory::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

FCsItem* ACsManager_Inventory::GetItem(const uint64 &Id)
{
	return *(Items.Find(Id));
}

FCsItem* ACsManager_Inventory::GetFirstItem(const TCsItemType &ItemType)
{
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ItemType);

	if (!ItemsPtr)
		return nullptr;
	
	if (ItemsPtr->Num() == CS_EMPTY)
		return nullptr;
	
	return (*ItemsPtr)[CS_FIRST];
}

int32 ACsManager_Inventory::GetItemCount(const TCsItemType &ItemType)
{
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ItemType);

	if (!ItemsPtr)
		return 0;
	return ItemsPtr->Num();
}

void ACsManager_Inventory::RemoveItem(const uint64 &Id, const bool &ShouldDestroy)
{
	FCsItem* Item = *(Items.Find(Id));

	if (!Item)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::RemoveItem: Failed to remove item with UniqueId: %d"), Id);
		return;
	}

	Items.Remove(Id);

	const TCsItemType ItemType = Item->Type;
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ItemType);

	const int32 Count = ItemsPtr->Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		if ((*ItemsPtr)[I]->UniqueId == Id)
		{
			ItemsPtr->RemoveAt(I);
			break;
		}
	}

	if (ShouldDestroy)
	{
		ACsManager_Item* Manager_Item = ACsManager_Item::Get(GetWorld());
		Manager_Item->DeAllocate(Item);
	}
}


void ACsManager_Inventory::RemoveItem(FCsItem* Item, const bool &ShouldDestroy)
{
	RemoveItem(Item->UniqueId, ShouldDestroy);
}

void ACsManager_Inventory::ConsumeItem(const uint64 &Id)
{
	RemoveItem(Id, true);
}

void ACsManager_Inventory::ConsumeItem(FCsItem* Item)
{
	ConsumeItem(Item->UniqueId);
}