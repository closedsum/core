// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Item/CsManager_Item.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "FileManager.h"

// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Runnable/CsManager_Runnable.h"
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Item.h"
#include "Data/CsData_Interactive.h"
// Player
#include "Pawn/CsPawn.h"
#include "Player/CsPlayerState.h"

#include "Async/AsyncWork.h"

// Cache
#pragma region

namespace ECsManagerItemCachedString
{
	namespace Str
	{
		const FString Allocate = TEXT("ACsManager_Item::Allocate");
		const FString DeAllocate = TEXT("ACsManager_Item::DeAllocate");
	}
}

#pragma endregion Cache

ACsManager_Item::ACsManager_Item(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (uint16 I = 0; I < CS_ITEM_POOL_SIZE; ++I)
	{
		Pool[I].Init(I);
	}

	UniqueIdIndex = CS_ITEM_UNIQUE_ID_START_INDEX;

	SaveDirectory = TEXT("Items/");
	
	PerformingAsyncSaveHandle.Set(&PerformingAsyncSave);
}

/*static*/ ACsManager_Item* ACsManager_Item::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Item;
}

void ACsManager_Item::OnTick(const float &DeltaSeconds)
{
	OnTick_Handle_AsyncSave();
	OnTick_Handle_DeAllocateQueue();
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

void ACsManager_Item::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, const FCsItem* const Item)
{
	if (CsCVarLogManagerItemTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString Id					  = FString::Printf(TEXT("%llu"), Item->UniqueId);
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const ACsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : ECsCachedString::Str::Empty;
		const float CurrentTime				  = GetWorld()->GetTimeSeconds();

		if (Data_Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with UniqueId: %s, Data: %s, and with Data_Actor: %s at %f."), *FunctionName, *TransactionAsString, *ItemName,*Id, *DataName, *DataActorName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with UniqueId: % and Data: %s at %f."), *FunctionName, *TransactionAsString, *ItemName, *Id, *DataName, CurrentTime);
		}
	}
}

// Allocate
#pragma region

FCsItem* ACsManager_Item::Allocate_Internal()
{
	for (uint16 I = 0; I < CS_ITEM_POOL_SIZE; ++I)
	{
		PoolIndex	  = (PoolIndex + I) % CS_ITEM_POOL_SIZE;
		FCsItem* Item = &(Pool[PoolIndex]);

		if (!Item->IsAllocated)
		{
			Item->IsAllocated = true;
			return Item;
		}
	}
	checkf(0, TEXT("ACsManager_Item::Allocate_Internal: Pool is exhausted."));
	return nullptr;
}

FCsItem* ACsManager_Item::Allocate()
{
	FCsItem* Item  = Allocate_Internal();
	Item->UniqueId = GetUniqueId();

	ActiveItems.Add(Item->UniqueId, Item);
	return Item;
}

FCsItem* ACsManager_Item::Allocate(const FName &ShortCode)
{
	FCsItem* Item = Allocate();

	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	ACsData_Item* Data			= Cast<ACsData_Item>(DataMapping->GetLoadedData(ItemAssetType, ShortCode));
	const TCsItemType& ItemType = Data->BaseItemType;

	Item->Type			= ItemType;
	Item->Type_Script	= (uint8)Item->Type;
	Item->TypeAsString	= (*ItemTypeToString)(Item->Type);
	Item->ShortCode		= Data->ShortCode;
	Item->DisplayName	= Data->GetDisplayName();

	SetItemFileName(Item);

	Item->Created = FDateTime::Now();

	Item->InventoryProperties.Reset();
	Item->InventoryProperties.Dimension = *(Data->GetDimension());

	if (Data->IsIngredient())
		Item->InventoryProperties.SetIngredient();

	Item->InventoryProperties.Capacity = Data->GetCapacity();

	Data->SetMembers(Item->CurrentHistory);

	Item->Data = Data;
	// Get Data for Actor when this Item is Dropped
	if (Data->OnDropSpawnActor())
		Item->Data_Actor = Cast<ACsData_Interactive>(DataMapping->GetLoadedData(InteractiveAssetType, Data->GetSpawnedActorDataShortCode()));

	return Item;
}

void ACsManager_Item::SetItemOwnerInfo(FCsItem* Item, UObject* ItemOwner){}

FCsItem* ACsManager_Item::Allocate(const FName &ShortCode, UObject* ItemOwner)
{
	FCsItem* Item = Allocate(ShortCode);

	SetItemOwnerInfo(Item, ItemOwner);
	AddActiveItemByOwnerId(Item);
	return Item;
}

void ACsManager_Item::AddActiveItemByOwnerId(FCsItem* Item)
{
	const uint64 OwnerId = Item->CurrentHistory.OwnerId;

	if (TArray<FCsItem*>* Items = ActiveItemsByOwnerId.Find(OwnerId))
	{
		Items->Add(Item);
	}
	else
	{
		TArray<FCsItem*> ItemArray;
		ItemArray.Add(Item);
		ActiveItemsByOwnerId.Add(OwnerId, ItemArray);
	}
}

void ACsManager_Item::ChangeActiveItemOwnerInfo(FCsItem* Item, UObject* ItemOwner)
{
	// Remove OLD OwnerId
	const uint64 OwnerId = Item->CurrentHistory.OwnerId;

	if (TArray<FCsItem*>* Items = ActiveItemsByOwnerId.Find(OwnerId))
	{
		const int32 Count = Items->Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if ((*Items)[I] == Item)
			{
				Items->RemoveAt(I);
				break;
			}
		}
	}
	// Update with NEW OwnerId
	SetItemOwnerInfo(Item, ItemOwner);
	AddActiveItemByOwnerId(Item);
}

void ACsManager_Item::SetActiveItemData(FCsItem* Item)
{
	ACsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	ACsData_Item* Data			= Cast<ACsData_Item>(DataMapping->GetLoadedData(ItemAssetType, Item->ShortCode));
	Item->Data					= Data;

	if (Data->IsIngredient())
		Item->InventoryProperties.SetIngredient();

	Item->InventoryProperties.Dimension = *(Data->GetDimension());
	Item->InventoryProperties.Capacity	= Data->GetCapacity();

	Item->Data_Actor = Cast<ACsData_Interactive>(DataMapping->GetLoadedData(InteractiveAssetType, Data->GetSpawnedActorDataShortCode()));
}

#pragma endregion Allocate

// Get
#pragma region

FCsItem* ACsManager_Item::GetItem(const uint64 &Id)
{
	if (FCsItem** ItemPtr = ActiveItems.Find(Id))
		return *ItemPtr;

	if (CsCVarLogManagerItemActionGetFail->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::GetItem: Failed to find an Item with Id: %d"), Id);
	}
	return nullptr;
}

void ACsManager_Item::GetItemsByOwnerType(const TCsItemOwner &OwnerType, TArray<FCsItem*> &OutItems)
{
	TArray<uint64> OutKeys;
	ActiveItems.GetKeys(OutKeys);

	const int32 Count = OutKeys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsItem* Item = *(ActiveItems.Find(OutKeys[I]));

		if (Item->CurrentHistory.OwnerType == OwnerType)
		{
			OutItems.Add(Item);
		}
	}
}

void ACsManager_Item::GetItemsByOwnerId(const uint64 &OwnerId, TArray<FCsItem*> &OutItems)
{
	TArray<FCsItem*>* Items = ActiveItemsByOwnerId.Find(OwnerId);

	if (!Items)
	{
		if (CsCVarLogManagerItemActionGetFail->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::GetItemsByOwnerId: Failed to find any ActiveItems with OwnerId: %d"), OwnerId);
		}
		OutItems.Reset();
		return;
	}

	const int32 Count = Items->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutItems.Add((*Items)[I]);
	}
}

void ACsManager_Item::GetItems(const TArray<uint64> &Ids, TArray<FCsItem*> &OutItems)
{
	const int32 Count = Ids.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (FCsItem** ItemPtr = (ActiveItems.Find(Ids[I])))
		{
			OutItems.Add(*ItemPtr);
		}
		else
		{
			if (CsCVarLogManagerItemActionGetFail->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::GetItems: Failed to find an Item with Id: %d"), Ids[I]);
			}
		}
	}
}

#pragma endregion Get

// DeAllocate
#pragma region

void ACsManager_Item::DeAllocate(const uint64 &Id)
{
	FCsItem* Item = *(ActiveItems.Find(Id));

	if (!Item)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::DeAllocate: Attempting to deallocate an Item with UniqueId: %d, but it is already deallocated."), Id);
		return;
	}

	ActiveItems.Remove(Id);

	// If Async Saving Item, Queue DeAllocate
	if (Item->AsycTaskMutex.IsLocked())
	{
		DeAllocateQueue.Add(Item);
		return;
	}

	// If Save EXISTS, Delete it.
	if (Item->IsSaved)
	{
		const FString Path = GetSavePath();
		const FString Filename = Path + Item->FileName + ECsCachedString::Str::Json;

		if (IFileManager::Get().FileExists(*Filename))
		{
			IFileManager::Get().Delete(*Filename, true, true, true);
		}
	}
	AvailableUnqiueIds.Add(Item->UniqueId);
	Item->Reset();
	Item->Data.Reset();
	Item->Data = nullptr;
	Item->Data_Actor.Reset();
	Item->Data_Actor = nullptr;
}

void ACsManager_Item::DeAllocate(FCsItem* Item)
{
	DeAllocate(Item->UniqueId);
}

void ACsManager_Item::OnTick_Handle_DeAllocateQueue()
{
	if (DeAllocateQueue.Num() == CS_EMPTY)
		return;

	const int32 Count = DeAllocateQueue.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsItem* Item = DeAllocateQueue[I];

		if (Item->AsycTaskMutex.IsLocked())
			continue;

		// If Save EXISTS, Delete it.
		if (Item->IsSaved)
		{
			const FString Path = GetSavePath();
			const FString Filename = Path + Item->FileName + ECsCachedString::Str::Json;

			if (IFileManager::Get().FileExists(*Filename))
			{
				IFileManager::Get().Delete(*Filename, true, true, true);
			}
		}
		AvailableUnqiueIds.Add(Item->UniqueId);
		Item->Reset();
		Item->Data.Reset();
		Item->Data = nullptr;
		Item->Data_Actor.Reset();
		Item->Data_Actor = nullptr;

		DeAllocateQueue.RemoveAt(I);
	}
}

#pragma endregion DeAllocate

// Transfer
#pragma region

bool ACsManager_Item::Transfer_Internal(FCsItem* Item, UObject* Instigator, ACsManager_Inventory* Manager_Inventory)
{
	if (Manager_Inventory)
	{
		const uint8 BAG = 0;
		// TODO: Need a way to determine correct Bag
		if (Manager_Inventory->IsFull(BAG, Item->ShortCode))
		{
			const FString OwnerName = Instigator->GetName();
			const FString& Type = Item->TypeAsString;

			UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::Transfer_Internal: %s's Inventory is FULL. DeAllocating %s with Id: %d"), *OwnerName, *Type, Item->UniqueId);
			DeAllocate(Item);
			return false;
		}

		Item->InventoryProperties.SetVisible();
		// TODO: Need a way to determine correct Bag
		Item->InventoryProperties.Bag = BAG;
	}

	// TODO: Potentially evaluate having ChangeActiveItemOwnerInfo within AddItem
	ChangeActiveItemOwnerInfo(Item, Instigator);

	if (Manager_Inventory)
		Manager_Inventory->AddItem(Item);

	// Transfer Contents
	TArray<FCsItem*> Items;
	GetItems(Item->Contents, Items);

	const int32 ContentCount = Items.Num();

	for (int32 I = 0; I < ContentCount; ++I)
	{
		FCsItem* ContentItem = Items[I];

		ChangeActiveItemOwnerInfo(ContentItem, Instigator);

		if (Manager_Inventory)
			Manager_Inventory->AddItem(ContentItem);
	}
	return true;
}

bool ACsManager_Item::Transfer(FCsItem* Item, UObject* Instigator)
{
	// Get Manager_Inventory from Instigator
	ACsManager_Inventory* Manager_Inventory = nullptr;

	// Character
	if (ACsPawn* Pawn = Cast<ACsPawn>(Instigator))
	{
		// Player
		if (ACsPlayerStateBase* PlayerState = Cast<ACsPlayerStateBase>(Pawn->PlayerState))
		{
			Manager_Inventory = PlayerState->Manager_Inventory;
		}
	}
	// Manager_Inventory
	else
	{
		Manager_Inventory = Cast<ACsManager_Inventory>(Instigator);
	}

	if (Transfer_Internal(Item, Instigator, Manager_Inventory))
		return true;

	UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::Transfer: Failed to Trasfer Item: %s with Id: %d"), *(Item->TypeAsString), Item->UniqueId);
	return false;
}

bool ACsManager_Item::Transfer(TArray<FCsItem*> &Items, UObject* Instigator, const TCsPoolTransactionOrder &Order)
{
	// Get Manager_Inventory from Instigator
	ACsManager_Inventory* Manager_Inventory = nullptr;

	// Character
	if (ACsPawn* Pawn = Cast<ACsPawn>(Instigator))
	{
		// Player
		if (ACsPlayerStateBase* PlayerState = Cast<ACsPlayerStateBase>(Pawn->PlayerState))
		{
			Manager_Inventory = PlayerState->Manager_Inventory;
		}
	}
	// Manager_Inventory
	else
	{
		Manager_Inventory = Cast<ACsManager_Inventory>(Instigator);
	}

	if (Manager_Inventory)
	{
		const int32 Count = Items.Num();

		// Fill Any
		if (Order == ECsPoolTransactionOrder::FillAny)
		{
			bool Success = false;

			for (int32 I = 0; I < Count; ++I)
			{
				FCsItem* Item = Items[I];

				Success |= Transfer_Internal(Item, Instigator, Manager_Inventory);
			}
			return Success;
		}
		// Fill Or Kill
		if (Order == ECsPoolTransactionOrder::FillOrKill)
		{
			bool Success = true;

			for (int32 I = 0; I < Count; ++I)
			{
				FCsItem* Item = Items[I];

				if (Manager_Inventory->IsFull(0, Item->ShortCode))
					Success &= false;
			}

			if (Success)
			{
				for (int32 I = 0; I < Count; ++I)
				{
					FCsItem* Item = Items[I];

					Transfer_Internal(Item, Instigator, Manager_Inventory);
				}
			}
			return Success;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::Transfer: Failed to Trasfer Items."));
	return false;
}

#pragma endregion Transfer

// Save / Load
#pragma region

void ACsManager_Item::SetItemFileName(FCsItem* Item)
{
	const FString Id = UCsCommon::UInt64ToString(Item->UniqueId);
	Item->FileName   = Id + TEXT("_") + (*ItemTypeToString)(Item->Type);
}

void ACsManager_Item::SetRootSaveDirectory(const FString &Directory)
{
	RootSaveDirectory	   = Directory + TEXT("/");
	CombinedSaveDirectory  = RootSaveDirectory + SaveDirectory;
}

FString ACsManager_Item::GetSavePath()
{
	const FString GameSaveDir = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir());
	const FString ItemsDir	  = CombinedSaveDirectory;
	const FString Directory   = GameSaveDir + ItemsDir;
	return Directory;
}

void ACsManager_Item::Save(FCsItem* Item)
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	// Header
	{
		JsonWriter->WriteObjectStart(ECsFileItemHeaderCachedString::Str::Header);

			// UniqueId
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::UniqueId, FString::Printf(TEXT("%llu"), Item->UniqueId));
			// ShortCode
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::ShortCode, Item->ShortCode.ToString());
			// DisplayName
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::DisplayName, Item->DisplayName);
			// Type
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Type, (*ItemTypeToString)(Item->Type));
			// Created
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Created, Item->Created.ToString());
			// Timespan
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Timespan, Item->LifeTime.ToString());

			// Contents
			JsonWriter->WriteObjectStart(ECsFileItemHeaderCachedString::Str::Contents);

				const int32 Count = Item->Contents.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					JsonWriter->WriteValue(FString::FromInt(I), FString::Printf(TEXT("%llu"), Item->Contents[I]));
				}
			JsonWriter->WriteObjectEnd();

		JsonWriter->WriteObjectEnd();
	}
	// Current History
	{
		JsonWriter->WriteObjectStart(ECsFileItemHistoryHeaderCachedString::Str::CurrentHistory);

		SaveHistory(JsonWriter, &(Item->CurrentHistory));

		JsonWriter->WriteObjectEnd();
	}
	// Previous Histories
	{
		JsonWriter->WriteArrayStart(ECsFileItemHistoryHeaderCachedString::Str::PreviousHistories);

		const int32 Count = Item->PreviousHistories.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			JsonWriter->WriteObjectStart();

			SaveHistory(JsonWriter, &(Item->PreviousHistories[I]));

			JsonWriter->WriteObjectEnd();
		}

		JsonWriter->WriteArrayEnd();
	}
	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Path		= GetSavePath();
	const FString Filename  = Path + Item->FileName + ECsCachedString::Str::Json;

	FFileHelper::SaveStringToFile(OutputString, *Filename);

	Item->IsSaved = true;
}

void ACsManager_Item::SaveHistory(TSharedRef<TJsonWriter<TCHAR>> &JsonWriter, FCsItemHistory* ItemHistory)
{
	// OwnerId
	JsonWriter->WriteValue(ECsFileItemHistoryHeaderCachedString::Str::OwnerId, FString::Printf(TEXT("%llu"), ItemHistory->OwnerId));
	// OwnerType
	JsonWriter->WriteValue(ECsFileItemHistoryHeaderCachedString::Str::OwnerType, (*ItemOwnerToString)(ItemHistory->OwnerType));
	// OwnerName
	JsonWriter->WriteValue(ECsFileItemHistoryHeaderCachedString::Str::OwnerName, ItemHistory->OwnerName);

	// Members
	JsonWriter->WriteObjectStart(ECsFileItemHistoryHeaderCachedString::Str::Members);

		TArray<FName> OutKeys;
		ItemHistory->Members.GetKeys(OutKeys);

		const int32 Count = OutKeys.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FCsItemMemberValue* Value = ItemHistory->Members.Find(OutKeys[I]);

			const TCsItemMemberValueType ValueType = Value->Type;
			const FString KeyName				   = OutKeys[I].ToString();
			// bool
			if (Value->Type == ECsItemMemberValueType::Bool)
				JsonWriter->WriteValue(KeyName, Value->GetBool());
			// uint8
			else
			if (Value->Type == ECsItemMemberValueType::Uint8)
				JsonWriter->WriteValue(KeyName, Value->GetUint8());
			// int32
			else
			if (Value->Type == ECsItemMemberValueType::Int32)
				JsonWriter->WriteValue(KeyName, Value->GetInt32());
			// floats
			else
			if (Value->Type == ECsItemMemberValueType::Float)
				JsonWriter->WriteValue(KeyName, Value->GetFloat());
		}
	JsonWriter->WriteObjectEnd();
}

void ACsManager_Item::SaveActiveItems()
{
	TArray<uint64> Keys;
	ActiveItems.GetKeys(Keys);

	const int32 Count = Keys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const uint64& Key = Keys[I];
		FCsItem** ItemPtr = ActiveItems.Find(Key);

		Save(*ItemPtr);
	}
}

// Async
#pragma region

FCsItem* ACsManager_Item::AllocateAsyncSave()
{
	for (uint8 I = 0; I < CS_ITEM_ASYNC_SAVE_POOL_SIZE; ++I)
	{
		const uint8 Index = (AsyncSavePoolIndex + I) % CS_ITEM_ASYNC_SAVE_POOL_SIZE;
		FCsItem* Item = &(AsyncSavePool[Index]);

		if (!Item->IsAllocated)
		{
			Item->IsAllocated = true;
			return Item;
		}
	}
	checkf(0, TEXT("ACsManager_Item::AllocatePayload: AsyncSavePool is exhausted"));
	return nullptr;
}

void ACsManager_Item::AddAsyncSave(FCsItem* Item)
{
	AsyncSaveItems.Add(Item);
}

void ACsManager_Item::AsyncSave()
{
	const int32 Count = CopiedAsyncSaveItems.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsItem* Item = CopiedAsyncSaveItems[I];

		Save(Item);
		Item->Reset();
	}
	CopiedAsyncSaveItems.Reset();

	PerformingAsyncSave = false;
}

void ACsManager_Item::OnTick_Handle_AsyncSave()
{
	PerformingAsyncSaveHandle.UpdateIsDirty();

	if (PerformingAsyncSave)
		return;

	// If an Async Save just completed, Clear Mutex
	if (PerformingAsyncSaveHandle.HasChanged())
	{
		const int32 Count = ActiveAsyncSaveItems.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FCsItem* Item = ActiveAsyncSaveItems[I];
			Item->AsycTaskMutex.Unlock();
		}
		ActiveAsyncSaveItems.Reset();
		PerformingAsyncSaveHandle.Clear();
	}

	if (AsyncSaveItems.Num() == CS_EMPTY)
		return;

	const int32 Count = AsyncSaveItems.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsItem* Item = AsyncSaveItems[I];
		// Lock for Async Save
		Item->AsycTaskMutex.Lock();
		// Add to Active List
		ActiveAsyncSaveItems.Add(Item);
		// Copy for Async Save
		FCsItem* AsyncItem	= AllocateAsyncSave();
		*AsyncItem			= *Item;

		CopiedAsyncSaveItems.Add(AsyncItem);
	}

	AsyncSaveItems.Reset();

	PerformingAsyncSave = true;
	PerformingAsyncSaveHandle.Resolve();

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner				= this;
	Payload->ThreadPriority		= EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &ACsManager_Item::AsyncSave);
	Runnable->Start();
}

#pragma endregion Async

void ACsManager_Item::PopulateExistingItems()
{
	TArray<FString> FoundFiles;

	const FString Path = GetSavePath();
	// Get all .json files under Path
	IFileManager::Get().FindFiles(FoundFiles, *Path, *ECsCachedString::Str::Json);

	const int32 FileCount = FoundFiles.Num();

	if (FileCount == CS_EMPTY)
	{
#if WITH_EDITOR
		OnPopulateExistingItems_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
		OnPopulateExistingItems_Event.Broadcast();
		return;
	}

	TArray<FCsItem*> Items;

	for (int32 I = 0; I < FileCount; ++I)
	{
		FString ItemJson;
		const FString Filename = Path + FoundFiles[I];

		if (FFileHelper::LoadFileToString(ItemJson, *Filename))
		{
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ItemJson);

			TSharedPtr<FJsonObject> JsonParsed;

			if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
			{
				/*
#if WITH_EDITOR
				VerifyJsonIntegrity();
#endif // #if WITH_EDITOR
				*/

				FCsItem* Item = Allocate_Internal();

				// Header
				{
					TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(ECsFileItemHeaderCachedString::Str::Header)->Get()->AsObject();

					// UniqueId
					Item->UniqueId = FCString::Strtoui64(*(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::UniqueId)), NULL, 10);
					// ShortCode
					Item->ShortCode = FName(*JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::ShortCode));
					// DisplayName
					Item->DisplayName = JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::DisplayName);
					// Type
					Item->TypeAsString = JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Type);
					Item->SetType((*StringToItemType)(Item->TypeAsString));
					// Created
					FDateTime::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Created), Item->Created);
					// Timespan
					FTimespan::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Timespan), Item->LifeTime);

					// Contents
					const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(ECsFileItemHeaderCachedString::Str::Contents);

					TArray<FString> Keys;

					Object->Values.GetKeys(Keys);

					const int32 Count = Keys.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const FString& Key				 = Keys[I];
						TSharedPtr<FJsonValue> JsonValue = *(Object->Values.Find(Key));
						FString Value					 = JsonValue->AsString();

						const uint64 UniqueId = FCString::Strtoui64(*Value, NULL, 10);
						
						Item->Contents.Add(UniqueId);
					}
				}

				SetActiveItemData(Item);

				// Current History
				{
					TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(ECsFileItemHistoryHeaderCachedString::Str::CurrentHistory)->Get()->AsObject();
					
					LoadHistory(JsonObject, Item, &(Item->CurrentHistory));
				}
				// Previous Histories
				{
					const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonParsed->Values.Find(ECsFileItemHistoryHeaderCachedString::Str::PreviousHistories)->Get()->AsArray();

					const int32 Count = JsonArray.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

						LoadHistory(Object, Item, &(Item->PreviousHistories[I]));
					}
				}

				AddActiveItemByOwnerId(Item);
				SetItemFileName(Item);

				Item->IsSaved = true;

				ActiveItems.Add(Item->UniqueId, Item);
				Items.Add(Item);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: %s is NOT Valid."), *Filename);
			}
		}
	}

	// Sort UniqueIds in ascending order
	Items.Sort([](const FCsItem &A, const FCsItem &B) { return A.UniqueId < B.UniqueId; });

	// Check / Validate Item Contents
	const int32 ItemCount = Items.Num();

	for (int32 I = 0; I < ItemCount; ++I)
	{
		FCsItem* Item = Items[I];

		// Add any UniqueId that were NOT accounted for
		if (I < ItemCount - 1)
		{
			const uint64 CurrentId = Item->UniqueId + 1;
			FCsItem* NextItem	   = Items[I + 1];
			const uint64& NextId   = NextItem->UniqueId;

			for (uint64 J = CurrentId; J < NextId; ++J)
			{
				AvailableUnqiueIds.Add(J);
			}
		}

		// Validate Item Contents
		const int32 ContentCount = Item->Contents.Num();

		if (ContentCount > CS_EMPTY)
		{
			bool ContentMismatch = false;

			for (int32 J = 0; J < ItemCount; ++J)
			{
				if (I == J)
					continue;

				// Compare Item->Contents with OtherItem->Contents
				FCsItem* OtherItem			  = Items[J];
				const int32 OtherContentCount = OtherItem->Contents.Num();
			
				if (OtherContentCount > CS_EMPTY)
				{
					for (int32 M = 0; M < ContentCount; ++M)
					{
						for (int32 N = 0; N < OtherContentCount; ++N)
						{
							if (Item->Contents[M] == OtherItem->Contents[N])
							{
								const FString ItemName		= Item->ShortCode.ToString();
								const FString OtherItemName = OtherItem->ShortCode.ToString();

								UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: Item: %s with UniqueId: %d and Item: %s with UniqueId: %d share Content with UniqueId: %d."), *ItemName, Item->UniqueId, *OtherItemName, OtherItem->UniqueId, Item->Contents[M]);

								ContentMismatch = true;
							}
						}
					}
				}
			}

			if (ContentMismatch)
			{
				const FString ItemName = Item->ShortCode.ToString();

				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: DeAllocating Item: %s with UniqueId: %d because it shares some Content with other Items."), *ItemName, Item->UniqueId);

				DeAllocate(Item);
			}
		}
	}

#if WITH_EDITOR
	OnPopulateExistingItems_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
	OnPopulateExistingItems_Event.Broadcast();
}

void ACsManager_Item::AsyncPopulateExistingItems()
{
	class FAsyncPopulateExistingItemsWorker : public FNonAbandonableTask
	{
	public:

		friend class FAutoDeleteAsyncTask<FAsyncPopulateExistingItemsWorker>;

		ACsManager_Item* Manager_Item;

		FAsyncPopulateExistingItemsWorker(ACsManager_Item* InManager_Item)
		{
			Manager_Item = InManager_Item;
		}

		void DoWork()
		{
			Manager_Item->PopulateExistingItems();
		}

		FORCEINLINE TStatId GetStatId() const
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncPopulateExistingItemsWorker, STATGROUP_ThreadPoolAsyncTasks);
		}
	};
	(new FAutoDeleteAsyncTask<FAsyncPopulateExistingItemsWorker>(this))->StartBackgroundTask();
}

void ACsManager_Item::LoadHistory(TSharedPtr<class FJsonObject> &JsonObject, FCsItem* Item, FCsItemHistory* ItemHistory)
{
	// OwnerId
	ItemHistory->OwnerId = FCString::Strtoui64(*(JsonObject->GetStringField(ECsFileItemHistoryHeaderCachedString::Str::OwnerId)), NULL, 10);
	// OwnerType
	ItemHistory->SetOwnerType((*StringToItemOwner)(JsonObject->GetStringField(ECsFileItemHistoryHeaderCachedString::Str::OwnerType)));
	// OwnerName
	ItemHistory->OwnerName = JsonObject->GetStringField(ECsFileItemHistoryHeaderCachedString::Str::OwnerName);

	// Members
	{
		const TSharedPtr<FJsonObject>& Object = JsonObject->Values.Find(ECsFileItemHistoryHeaderCachedString::Str::Members)->Get()->AsObject();

		TArray<FCsItemMemberDescription>* Members = Item->GetData()->GetMembers();

		TArray<FString> Keys;
		Object->Values.GetKeys(Keys);
		const uint8 KeyCount    = Keys.Num();
		const uint8 MemberCount	= Members->Num();
		const uint8 Count		= FMath::Max(KeyCount, MemberCount);
	
		for (uint8 I = 0; I < Count; ++I)
		{
			if (I >= MemberCount)
				continue;
			
			FCsItemMemberDescription& Member = (*Members)[I];

			const TCsItemMemberValueType& Type = Member.Type;

			FCsItemMemberValue Value;
			Value.Type = Type;

			const FName& MemberName			 = Member.Name;
			const FString MemberNameAsString = MemberName.ToString();

			const TSharedPtr<FJsonValue>* JsonValue = Object->Values.Find(MemberNameAsString);
			bool IsValidKey							= JsonValue != nullptr && I < KeyCount;

			if (IsValidKey)
			{ 
				// bool
				if (Type == ECsItemMemberValueType::Bool)
				{
					Value.Value_bool =  Object->GetBoolField(MemberNameAsString);
				}
				// uint8
				else
				if (Type == ECsItemMemberValueType::Uint8)
				{
					Value.Value_uint8 = (uint8)Object->GetIntegerField(MemberNameAsString);
				}
				// int32
				else
				if (Type == ECsItemMemberValueType::Int32)
				{
					Value.Value_int32 = Object->GetIntegerField(MemberNameAsString);
				}
				// float
				else
				if (Type == ECsItemMemberValueType::Float)
				{
					Value.Value_float = (float)Object->GetNumberField(MemberNameAsString);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::LoadHistory: INVALID ItemMemberValue Type: %s."), *(ECsItemMemberValueType::ToString(Type)));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::LoadHistory: Change in Member Count from %d -> %d. Using default value for Member: %s."), KeyCount, MemberCount, *MemberNameAsString);
			}
			ItemHistory->Members.Add(MemberName, Value);
		}
	}
}

void ACsManager_Item::InitInventory(ACsManager_Inventory* Manager_Inventory){}

void ACsManager_Item::AsyncInitInventory(ACsManager_Inventory* Manager_Inventory) 
{
	class FAsyncInitInventoryWorker : public FNonAbandonableTask
	{
	public:

		friend class FAutoDeleteAsyncTask<FAsyncInitInventoryWorker>;

		ACsManager_Item* Manager_Item;
		ACsManager_Inventory* Manager_Inventory;

		FAsyncInitInventoryWorker(ACsManager_Item* InManager_Item, ACsManager_Inventory* InManager_Inventory)
		{
			Manager_Item	  = InManager_Item;
			Manager_Inventory = InManager_Inventory;
		}

		void DoWork()
		{
			Manager_Item->InitInventory(Manager_Inventory);
		}

		FORCEINLINE TStatId GetStatId() const
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncInitInventoryWorker, STATGROUP_ThreadPoolAsyncTasks);
		}
	};
	(new FAutoDeleteAsyncTask<FAsyncInitInventoryWorker>(this, Manager_Inventory))->StartBackgroundTask();
}

#pragma endregion Save / Load

// Action
#pragma region

void ACsManager_Item::RecordItemsInteraction(const TArray<FCsItem*> &Items, const TCsItemInteraction &Interaction)
{
	const int32 Count = Items.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		RecordItemInteraction(Items[I], Interaction);
	}
}

void ACsManager_Item::RecordItemInteraction(FCsItem* Item, const TCsItemInteraction& Interaction){}

#pragma endregion Action