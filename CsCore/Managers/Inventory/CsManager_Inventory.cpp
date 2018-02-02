// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Inventory/CsManager_Inventory.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

// Managers
#include "Managers/Item/CsManager_Item.h"

ACsManager_Inventory::ACsManager_Inventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// TODO: Get BagCount from Data
	BagCount = 1;
}

void ACsManager_Inventory::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	for (uint8 I = 0; I < BagCount; ++I)
	{
		Bags.AddDefaulted();
	}
}

/*static*/ ACsManager_Inventory* ACsManager_Inventory::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Inventory;
}

AActor* ACsManager_Inventory::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

bool ACsManager_Inventory::IsEmpty()
{
	TArray<uint64> OutKeys;
	Items.GetKeys(OutKeys);
	return OutKeys.Num() == CS_EMPTY;
}

FCsItem* ACsManager_Inventory::GetItem(const uint64 &Id)
{
	return *(Items.Find(Id));
}

FCsItem* ACsManager_Inventory::GetFirstItem(const FName &ShortCode)
{
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

	if (!ItemsPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetFirstItem: There are NO Items with ShortCode: %s."), *(ShortCode.ToString()));
		return nullptr;
	}
	
	if (ItemsPtr->Num() == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetFirstItem: There are NO Items with ShortCode: %s."), *(ShortCode.ToString()));
		return nullptr;
	}
	return (*ItemsPtr)[CS_FIRST];
}

int32 ACsManager_Inventory::GetItemCount(const FName &ShortCode)
{
	if (uint16* Count = ItemCountMap.Find(ShortCode))
		return *Count;
	return 0;
}

void ACsManager_Inventory::IncrementItemCount(const FName &ShortCode)
{
	if (uint16* Count = ItemCountMap.Find(ShortCode))
	{
		(*Count)++;
	}
	else
	{
		ItemCountMap.Add(ShortCode, 1);
	}
}

void ACsManager_Inventory::DecrementItemCount(const FName &ShortCode)
{
	if (uint16* Count = ItemCountMap.Find(ShortCode))
	{
		if (*Count > 0)
			(*Count)--;
	}
	else
	{
		ItemCountMap.Add(ShortCode, 0);
	}
}

void ACsManager_Inventory::AddItem(FCsItem* Item)
{
	Items.Add(Item->UniqueId, Item);

	if (TArray<FCsItem*>* ItemsPtr = ItemMap.Find(Item->ShortCode))
	{
		ItemsPtr->Add(Item);
	}
	else
	{
		TArray<FCsItem*> ItemArray;
		ItemArray.Add(Item);
		ItemMap.Add(Item->ShortCode, ItemArray);
	}
	IncrementItemCount(Item->ShortCode);
	Bags[Item->InventoryProperties.Bag].Add(Item);
}

void ACsManager_Inventory::AddItems(const TArray<FCsItem*> &ItemsToAdd)
{
	const int32 Count = ItemsToAdd.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		AddItem(ItemsToAdd[I]);
	}
}

// Remove
#pragma region

void ACsManager_Inventory::RemoveItem(const uint64 &Id, const bool &ShouldDestroy)
{
	FCsItem* Item = *(Items.Find(Id));

	if (!Item)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::RemoveItem: Failed to remove item with UniqueId: %d"), Id);
		return;
	}

	Items.Remove(Id);

	const FName& ShortCode	   = Item->ShortCode;
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

	const int32 Count = ItemsPtr->Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		if ((*ItemsPtr)[I]->UniqueId == Id)
		{
			ItemsPtr->RemoveAt(I);
			break;
		}
	}
	DecrementItemCount(ShortCode);
	Bags[Item->InventoryProperties.Bag].Remove(Item);

	if (ShouldDestroy)
	{
		// TODO: Need to Delete .json file associated with the item

		ACsManager_Item* Manager_Item = ACsManager_Item::Get(GetWorld());
		Manager_Item->DeAllocate(Item);
	}
}


void ACsManager_Inventory::RemoveItem(FCsItem* Item, const bool &ShouldDestroy)
{
	RemoveItem(Item->UniqueId, ShouldDestroy);
}

#pragma endregion Remove

// Consume
#pragma region

void ACsManager_Inventory::ConsumeItem(const uint64 &Id)
{
	RemoveItem(Id, true);
}

void ACsManager_Inventory::ConsumeItem(FCsItem* Item)
{
	ConsumeItem(Item->UniqueId);
}

void ACsManager_Inventory::ConsumeFirstItem(const FName &ShortCode)
{
	if (FCsItem* Item = GetFirstItem(ShortCode))
	{
		ConsumeItem(Item);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::ConsumeFirstItem: There are NO Items with ShortCode: %s to Consume."), *(ShortCode.ToString()));
	}
}

#pragma endregion Consume

// Drop
#pragma region

void ACsManager_Inventory::DropItem(const uint64 &Id)
{
	RemoveItem(Id, false);
}

void ACsManager_Inventory::DropItem(FCsItem* Item)
{
	DropItem(Item->UniqueId);
}

FCsItem* ACsManager_Inventory::DropFirstItem(const FName &ShortCode)
{
	if (FCsItem* Item = GetFirstItem(ShortCode))
	{
		DropItem(Item);
		return Item;
	}
	return nullptr;
}

#pragma endregion Drop