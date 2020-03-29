// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Inventory/CsManager_Inventory.h"
#include "CsCore.h"
#include "CsCVars.h"

// Managers
#include "Managers/Item/CsManager_Item.h"
// Data
#include "Data/CsData_Item.h"
#include "Data/CsData_Interactive.h"
// Game
#include "Game/CsGameState_DEPRECATED.h"

// Cache
#pragma region

namespace NCsManagerInventoryStringCache
{
	namespace Str
	{
		const FString AddItem = TEXT("ACsManager_Inventory::AddItem");
		const FString RemoveItem = TEXT("ACsManager_Inventory::RemoveItem");
		const FString ConsumeItem_Internal = TEXT("ACsManager_Inventory::ConsumeItem_Internal");
		const FString DropItem = TEXT("ACsManager_Inventory::DropItem");
	}
}

#pragma endregion Cache

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
	return InWorld->GetGameState<ACsGameState_DEPRECATED>()->Manager_Inventory;
}

AActor* ACsManager_Inventory::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

int32 ACsManager_Inventory::GetSlotCount(const uint8& Bag, const uint8& Row, const uint8& Column)
{
	return Bags[Bag].GetSlotCount(Row, Column);
}

bool ACsManager_Inventory::IsEmpty()
{
	TArray<TCsItemId> OutKeys;
	Items.GetKeys(OutKeys);
	return OutKeys.Num() == CS_EMPTY;
}

bool ACsManager_Inventory::IsFull(const uint8& Bag, const FName& ShortCode)
{
	const uint8 SlotCount = Bags[Bag].Slots.Num();

	for (uint8 I = 0; I < SlotCount; ++I)
	{
		FCsItemBagSlot& Slot = Bags[Bag].Slots[I];

		const uint8 ItemCount = Slot.Items.Num();

		if (ItemCount == CS_EMPTY)
			return false;

		FCsItem* Item = Slot.Items[CS_FIRST];

		if (ShortCode == Item->ShortCode &&
			ItemCount < Item->InventoryProperties.Capacity)
		{
			return false;
		}
	}
	return true;
}

FCsItem* ACsManager_Inventory::GetItem(const TCsItemId& Id)
{
	if (FCsItem** ItemPtr = Items.Find(Id))
		return *ItemPtr;

	UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItem: Failed to find an Item with Id: %s"), *(Id.ToString()));
	return nullptr;
}

FCsItem* ACsManager_Inventory::GetFirstItem(const FName& ShortCode)
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

void ACsManager_Inventory::GetItems(const FName& ShortCode, const int32& Count, const ECsInventoryGetRequest& Request, TArray<FCsItem*>& OutItems)
{
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

	if (!ItemsPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItems: There are NO Items with ShortCode: %s."), *(ShortCode.ToString()));
		return;
	}

	const int32 ItemCount = ItemsPtr->Num();

	if (Request == ECsInventoryGetRequest::FillOrKill &&
		Count > ItemCount)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItems: There are only %d ( < %d requested ) Items with ShortCode: %s "), ItemCount, Count, *(ShortCode.ToString()));
		return;
	}

	for (int32 I = 0; I < ItemCount; ++I)
	{
		OutItems.Add((*ItemsPtr)[I]);

		if (OutItems.Num() == Count)
			break;
	}

	// FillOrKill
	if (Request == ECsInventoryGetRequest::FillOrKill)
	{
		if (OutItems.Num() != Count)
			OutItems.Reset();
	}
}

void ACsManager_Inventory::GetItems(const FName& ShortCode, const int32& Count, const ECsInventoryGetRequest& Request, const int32& State, TArray<FCsItem*>&OutItems)
{ 
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

	if (!ItemsPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItems: There are NO Items with ShortCode: %s."), *(ShortCode.ToString()));
		return;
	}

	const int32 ItemCount = ItemsPtr->Num();

	if (Request == ECsInventoryGetRequest::FillOrKill &&
		Count > ItemCount)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItems: There are only %d ( < %d requested ) Items with ShortCode: %s "), ItemCount, Count, *(ShortCode.ToString()));
		return;
	}

	for (int32 I = 0; I < ItemCount; ++I)
	{
		FCsItem* Item = (*ItemsPtr)[I];

		if (Item->InventoryProperties.IsState(State))
			OutItems.Add((*ItemsPtr)[I]);

		if (OutItems.Num() == Count)
			break;
	}

	// FillOrKill
	if (Request == ECsInventoryGetRequest::FillOrKill)
	{
		if (OutItems.Num() != Count)
			OutItems.Reset();
	}
}

void ACsManager_Inventory::GetItems(const TArray<TCsItemId>& Ids, TArray<FCsItem*>& OutItems)
{
	const int32 Count = Ids.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (FCsItem** ItemPtr = (Items.Find(Ids[I])))
		{
			OutItems.Add(*ItemPtr);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItems: Failed to find an Item with Id: %s"), *(Ids[I].ToString()));
		}
	}
}

int32 ACsManager_Inventory::GetItemCount(const FName& ShortCode)
{
	if (uint16* Count = ItemCountMap.Find(ShortCode))
		return *Count;
	return 0;
}

int32 ACsManager_Inventory::GetItemCount(const FName& ShortCode, const int32& State)
{
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

	if (!ItemsPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::GetItems: There are NO Items with ShortCode: %s."), *(ShortCode.ToString()));
		return 0;
	}

	int32 OutCount	  = 0;
	const int32 Count = ItemsPtr->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsItem* Item = (*ItemsPtr)[I];

		if (Item->InventoryProperties.IsState(State))
			++OutCount;
	}
	return OutCount;
}

void ACsManager_Inventory::IncrementItemCount(const FName& ShortCode)
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

void ACsManager_Inventory::DecrementItemCount(const FName& ShortCode)
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

void ACsManager_Inventory::LogTransaction(const FString& FunctionName, const ECsInventoryTransaction& Transaction, const FCsItem* const Item)
{
	if (CsCVarLogManagerInventoryTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString TransactionAsString = NCsInventoryTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const UCsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : NCsCached::Str::Empty;
		const float CurrentTime				  = GetWorld()->GetTimeSeconds();

		if (Data_Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with Data: %s and with Data_Actor: %s at %f."), *FunctionName, *TransactionAsString, *ItemName, *DataName, *DataActorName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with Data: %s at %f."), *FunctionName, *TransactionAsString, *ItemName, *DataName, CurrentTime);
		}
	}
}

uint8 ACsManager_Inventory::GetFirstAvailableBagIndex(const FECsItemType& ItemType)
{
	return 0;
}

// Add
#pragma region

void ACsManager_Inventory::AddItem(FCsItem* Item)
{
	if (Item->InventoryProperties.IsVisible())
	{
		// Try to Add the Item to the Bag. Only Add the Item if there is a Slot free that can hold the Item
		const bool Success = Bags[Item->InventoryProperties.Bag].Add(Item);

		if (!Success)
		{
			const FString ItemName = Item->ShortCode.ToString();
			const FString Id	   = Item->Id.ToString();

			UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::AddItem: Failed to Add Item: %s with ID: %s. All Slots for Bag: %d are FULL."), *ItemName, *Id, Item->InventoryProperties.Bag);
			return;
		}
	}

	Items.Add(Item->Id, Item);

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
	
	LogTransaction(NCsManagerInventoryStringCache::Str::AddItem, ECsInventoryTransaction::Add, Item);

#if WITH_EDITOR
	OnAddItem_ScriptEvent.Broadcast(*Item);
#endif // #if WITH_EDITOR
	OnAddItem_Event.Broadcast(Item);
}

void ACsManager_Inventory::AddItems(const TArray<FCsItem*>& ItemsToAdd)
{
	const int32 Count = ItemsToAdd.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		AddItem(ItemsToAdd[I]);
	}
}

#pragma endregion Add

// Remove
#pragma region

void ACsManager_Inventory::RemoveItem(const TCsItemId& Id, const FString& FunctionName, const ECsInventoryTransaction& Transaction, const bool& ShouldDestroy)
{
	FCsItem** ItemPtr = Items.Find(Id);

	if (!ItemPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::RemoveItem: Failed to remove item with UniqueId: %s"), *(Id.ToString()));
		return;
	}

	FCsItem* Item = *ItemPtr;

	Items.Remove(Id);

	const FName& ShortCode	   = Item->ShortCode;
	TArray<FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

	const int32 Count = ItemsPtr->Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if ((*ItemsPtr)[I]->Id == Id)
		{
			ItemsPtr->RemoveAt(I);
			break;
		}
	}
	DecrementItemCount(ShortCode);

	if (Item->InventoryProperties.IsVisible())
		Bags[Item->InventoryProperties.Bag].Remove(Item);

	LogTransaction(FunctionName, Transaction, Item);

#if WITH_EDITOR
	OnRemoveItem_ScriptEvent.Broadcast(*Item);
#endif // #if WITH_EDITOR
	OnRemoveItem_Event.Broadcast(Item);

	if (ShouldDestroy)
	{
		ACsManager_Item* Manager_Item = ACsManager_Item::Get(GetWorld());
		Manager_Item->DeAllocate(Item);
	}
}

void ACsManager_Inventory::RemoveItem(FCsItem* Item, const FString& FunctionName, const ECsInventoryTransaction& Transaction, const bool& ShouldDestroy)
{
	RemoveItem(Item->Id, FunctionName, Transaction, ShouldDestroy);
}

#pragma endregion Remove

// Consume
#pragma region

void ACsManager_Inventory::ConsumeItem_Internal(const TCsItemId& Id)
{
	RemoveItem(Id, NCsManagerInventoryStringCache::Str::ConsumeItem_Internal, ECsInventoryTransaction::Consume, true);
}

void ACsManager_Inventory::ConsumeItem(FCsItem* Item, TArray<FCsItem*>& OutResultingItems)
{
	UCsData_Item* Data = Item->GetData();
	
	// Handle Contents
	const TArray<FCsItemOnConsumeContentRule>* Rules = Data->GetOnConsumeContentRules();

	TArray<FCsItem*> OutItems;
	GetItems(Item->Contents, OutItems);
	
	int32 ContentCount = OutItems.Num();

	for (int32 I = ContentCount - 1; I >= 0; --I)
	{
		FCsItem* ContentItem = OutItems[I];
		// By Default CONSUME
		TCsItemOnConsumeContentAction Action = ECsItemOnConsumeContentAction::Consume;
		
		// Check Rules
		if (Rules)
		{
			int32 RuleCount = Rules->Num();

			for (int32 J = 0; J < RuleCount; ++J)
			{
				const FCsItemOnConsumeContentRule& Rule = (*Rules)[J];

				if (ContentItem->ShortCode == Rule.ShortCode)
				{
					Action = (TCsItemOnConsumeContentAction)Rule.Action;
					break;
				}
			}
		}
		// Check to DROP
		else
		if (Data->OnConsumeDropContents())
		{
			Action = ECsItemOnConsumeContentAction::Drop;
		}
		
		// CONSUME
		if (Action == ECsItemOnConsumeContentAction::Consume)
		{
			ConsumeItem_Internal(ContentItem->Id);
		}
		// DROP
		else
		if (Action == ECsItemOnConsumeContentAction::Drop)
		{
			DropItem(ContentItem);
			OutResultingItems.Add(ContentItem);
		}
		// RETAIN
		else
		if (Action == ECsItemOnConsumeContentAction::Retain)
		{
			OutResultingItems.Add(ContentItem);
		}
	}
	ConsumeItem_Internal(Item->Id);
}

void ACsManager_Inventory::ConsumeItem(FCsItem* Item)
{
	TArray<FCsItem*> OutResultingItems;
	ConsumeItem(Item, OutResultingItems);
}

void ACsManager_Inventory::ConsumeFirstItem(const FName& ShortCode, TArray<FCsItem*>& OutResultingItems)
{
	if (FCsItem* Item = GetFirstItem(ShortCode))
	{
		ConsumeItem(Item, OutResultingItems);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Inventory::ConsumeFirstItem: There are NO Items with ShortCode: %s to Consume."), *(ShortCode.ToString()));
	}
}

void ACsManager_Inventory::ConsumeFirstItem(const FName& ShortCode)
{
	TArray<FCsItem*> OutResultingItems;
	ConsumeFirstItem(ShortCode, OutResultingItems);
}

#pragma endregion Consume

// Drop
#pragma region

void ACsManager_Inventory::DropItem_Internal(const TCsItemId& Id)
{
	RemoveItem(Id, NCsManagerInventoryStringCache::Str::DropItem, ECsInventoryTransaction::Drop, false);
}

void ACsManager_Inventory::DropItem(FCsItem* Item)
{
	DropItem_Internal(Item->Id);
}

FCsItem* ACsManager_Inventory::DropFirstItem(const FName& ShortCode)
{
	if (FCsItem* Item = GetFirstItem(ShortCode))
	{
		DropItem(Item);
		return Item;
	}
	return nullptr;
}

#pragma endregion Drop

// Hide
#pragma region

void ACsManager_Inventory::HideItem(FCsItem* Item)
{
	if (!Item->InventoryProperties.IsVisible())
		return;

	Bags[Item->InventoryProperties.Bag].Remove(Item);
	Item->InventoryProperties.ClearVisible();

#if WITH_EDITOR
	OnHideItem_ScriptEvent.Broadcast(*Item);
#endif // #if WITH_EDITOR
	OnHideItem_Event.Broadcast(Item);
}

#pragma endregion Hide