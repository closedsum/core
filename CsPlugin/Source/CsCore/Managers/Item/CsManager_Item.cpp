// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

// Cache
#pragma region

namespace NCsManagerItemCached
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
	ProductName = TEXT("Mega Block One");
	ProductId = FGuid(1, 1, 1, 1);

	for (uint16 I = 0; I < CS_ITEM_POOL_SIZE; ++I)
	{
		Pool[I].Init(I);
	}

	SaveDirectory = TEXT("Items/");
	
	PerformingAsyncSaveHandle.Set(&PerformingAsyncSave);
}

/*static*/ ACsManager_Item* ACsManager_Item::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Item;
}

void ACsManager_Item::Rebuild()
{
	const FString Directory = GetSavePath();

	// Delete files in existing directories
	IFileManager& FileManager = FFileManagerGeneric::Get();

	// Accounts
	if (FileManager.DirectoryExists(*Directory))
	{
		TArray<FString> FoundFiles;
		FileManager.FindFiles(FoundFiles, *Directory, nullptr);

		for (const FString& File : FoundFiles)
		{
			const FString Path = Directory + File;

			FileManager.Delete(*Path, false, true, true);
		}
	}
}

void ACsManager_Item::OnTick(const float& DeltaSeconds)
{
	OnTick_Handle_AsyncSave();
	OnTick_Handle_DeAllocateQueue();
}

FGuid ACsManager_Item::GetUniqueId()
{
	/*
	const uint64 Size = AvailableUnqiueIds.Num();

	if (Size > CS_EMPTY)
	{
		const uint64 Id = AvailableUnqiueIds[Size - 1];
		AvailableUnqiueIds.RemoveAt(Size - 1);
		return Id;
	}
	UniqueIdIndex++;
	return UniqueIdIndex;
	*/
	return FGuid::NewGuid();
}

void ACsManager_Item::LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, const FCsItem* const Item)
{
	if (CsCVarLogManagerItemTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& TransactionAsString = NCsPoolTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString Id					  = Item->Id.ToString();
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const UCsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : NCsCached::Str::Empty;
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
		PoolIndex	  = (PoolIndex + 1) % CS_ITEM_POOL_SIZE;
		FCsItem* Item = &(Pool[PoolIndex]);

		if (!Item->bAllocated)
		{
			Item->bAllocated = true;

			FCsItemProduct Product;
			Product.Name = ProductName;
			Product.Id	 = ProductId;
			Item->Products.Add(ProductId, Product);
			return Item;
		}
	}
	checkf(0, TEXT("ACsManager_Item::Allocate_Internal: Pool is exhausted."));
	return nullptr;
}

FCsItem* ACsManager_Item::Allocate()
{
	FCsItem* Item  = Allocate_Internal();
	Item->Id	   = GetUniqueId();

	ActiveItems.Add(Item->Id, Item);
	return Item;
}

FCsItem* ACsManager_Item::Allocate(const FName& ShortCode)
{
	FCsItem* Item = Allocate();

	UCsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	UCsData_Item* Data			= Cast<UCsData_Item>(DataMapping->GetLoadedData(ItemAssetType, ShortCode));
	const FECsItemType& ItemType = Data->GetItemType();

	Item->Type			= ItemType;
	Item->ShortCode		= Data->ShortCode;
	Item->DisplayName	= Data->GetDisplayName();

	SetItemFileName(Item);

	Item->Created = FDateTime::Now();

	Item->InventoryProperties.Reset();
	Item->InventoryProperties.Dimension = *(Data->GetDimension());

	if (Data->IsIngredient())
		Item->InventoryProperties.SetIngredient();

	Item->InventoryProperties.Capacity = Data->GetCapacity();

	Data->SetMembers(Item->GetCurrentHistory(ProductId));

	Item->Data = Data;
	// Get Data for Actor when this Item is Dropped
	if (Data->OnDropSpawnActor())
		Item->Data_Actor = Cast<UCsData_Interactive>(DataMapping->GetLoadedData(InteractiveAssetType, Data->GetSpawnedActorDataShortCode()));

	return Item;
}

void ACsManager_Item::SetItemOwnerInfo(FCsItem* Item, UObject* ItemOwner){}

FCsItem* ACsManager_Item::Allocate(const FName& ShortCode, UObject* ItemOwner)
{
	FCsItem* Item = Allocate(ShortCode);

	SetItemOwnerInfo(Item, ItemOwner);
	AddActiveItemByOwnerId(Item);
	return Item;
}

void ACsManager_Item::AddActiveItemByOwnerId(FCsItem* Item)
{
	const TCsItemId& OwnerId = Item->GetCurrentHistory(ProductId).OwnerId;

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
	const TCsItemId& OwnerId = Item->GetCurrentHistory(ProductId).OwnerId;

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
	UCsDataMapping* DataMapping = UCsCommon::GetDataMapping(GetWorld());
	UCsData_Item* Data			= Cast<UCsData_Item>(DataMapping->GetLoadedData(ItemAssetType, Item->ShortCode));
	Item->Data					= Data;

	if (Data->IsIngredient())
		Item->InventoryProperties.SetIngredient();

	Item->InventoryProperties.Dimension = *(Data->GetDimension());
	Item->InventoryProperties.Capacity	= Data->GetCapacity();

	Item->Data_Actor = Cast<UCsData_Interactive>(DataMapping->GetLoadedData(InteractiveAssetType, Data->GetSpawnedActorDataShortCode()));
}

#pragma endregion Allocate

// Get
#pragma region

FCsItem* ACsManager_Item::GetItem(const TCsItemId& Id)
{
	if (FCsItem** ItemPtr = ActiveItems.Find(Id))
		return *ItemPtr;

	if (CsCVarLogManagerItemActionGetFail->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::GetItem: Failed to find an Item with Id: %s"), *(Id.ToString()));
	}
	return nullptr;
}

void ACsManager_Item::GetItemsByOwnerType(const FECsItemOwner& OwnerType, TArray<FCsItem*>& OutItems)
{
	TArray<TCsItemId> OutKeys;
	ActiveItems.GetKeys(OutKeys);

	for (const TCsItemId& Key : OutKeys)
	{
		FCsItem* Item = ActiveItems[Key];

		const FCsItemHistory& CurrentHistory = Item->GetCurrentHistory(ProductId);

		if (CurrentHistory.OwnerType == OwnerType)
		{
			OutItems.Add(Item);
		}
	}
}

void ACsManager_Item::GetItemsByOwnerId(const TCsItemOwnerId& OwnerId, TArray<FCsItem*>& OutItems)
{
	TArray<FCsItem*>* ItemsPtr = ActiveItemsByOwnerId.Find(OwnerId);

	if (!ItemsPtr)
	{
		if (CsCVarLogManagerItemActionGetFail->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::GetItemsByOwnerId: Failed to find any ActiveItems with OwnerId: %s"), *(OwnerId.ToString()));
		}
		OutItems.Reset();
		return;
	}

	TArray<FCsItem*>& Items = *ItemsPtr;

	for (FCsItem* Item : Items)
	{
		OutItems.Add(Item);
	}
}

void ACsManager_Item::GetItems(const TArray<TCsItemId>& Ids, TArray<FCsItem*>& OutItems)
{
	for (const TCsItemId& Id : Ids)
	{
		if (FCsItem** ItemPtr = (ActiveItems.Find(Id)))
		{
			OutItems.Add(*ItemPtr);
		}
		else
		{
			if (CsCVarLogManagerItemActionGetFail->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::GetItems: Failed to find an Item with Id: %d"), *(Id.ToString()));
			}
		}
	}
}

#pragma endregion Get

// DeAllocate
#pragma region

void ACsManager_Item::DeAllocate(const FGuid& Id)
{
	FCsItem* Item = *(ActiveItems.Find(Id));

	if (!Item)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::DeAllocate: Attempting to deallocate an Item with Id: %s, but it is already deallocated."), *(Id.ToString()));
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
		const FString Filename = Path + Item->FileName + NCsCached::Ext::json;

		if (IFileManager::Get().FileExists(*Filename))
		{
			IFileManager::Get().Delete(*Filename, true, true, true);
		}
	}

	Item->Reset();
	Item->Data.Reset();
	Item->Data = nullptr;
	Item->Data_Actor.Reset();
	Item->Data_Actor = nullptr;
}

void ACsManager_Item::DeAllocate(FCsItem* Item)
{
	DeAllocate(Item->Id);
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
			const FString Filename = Path + Item->FileName + NCsCached::Ext::json;

			if (IFileManager::Get().FileExists(*Filename))
			{
				IFileManager::Get().Delete(*Filename, true, true, true);
			}
		}

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

bool ACsManager_Item::Transfer_Internal(FCsItem* Item, UObject* InInstigator, ACsManager_Inventory* Manager_Inventory)
{
	if (Manager_Inventory)
	{
		const uint8 BAG = 0;
		// TODO: Need a way to determine correct Bag
		if (Manager_Inventory->IsFull(BAG, Item->ShortCode))
		{
			const FString OwnerName = InInstigator->GetName();
			const FString& Type		= Item->Type.Name;

			UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::Transfer_Internal: %s's Inventory is FULL. DeAllocating %s with Id: %s"), *OwnerName, *Type, *(Item->Id.ToString()));
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

		ChangeActiveItemOwnerInfo(ContentItem, InInstigator);

		if (Manager_Inventory)
			Manager_Inventory->AddItem(ContentItem);
	}
	return true;
}

bool ACsManager_Item::Transfer(FCsItem* Item, UObject* InInstigator)
{
	// Get Manager_Inventory from Instigator
	ACsManager_Inventory* Manager_Inventory = nullptr;

	// Character
	if (ACsPawn* Pawn = Cast<ACsPawn>(InInstigator))
	{
		// Player
		if (ACsPlayerStateBase* PlayerState = Pawn->GetPlayerState<ACsPlayerStateBase>())
		{
			Manager_Inventory = PlayerState->Manager_Inventory;
		}
	}
	// Manager_Inventory
	else
	{
		Manager_Inventory = Cast<ACsManager_Inventory>(InInstigator);
	}

	if (Transfer_Internal(Item, InInstigator, Manager_Inventory))
		return true;

	UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::Transfer: Failed to Trasfer Item: %s with Id: %d"), *(Item->Type.Name), *(Item->Id.ToString()));
	return false;
}

bool ACsManager_Item::Transfer(TArray<FCsItem*>& Items, UObject* InInstigator, const ECsPoolTransactionOrder& Order)
{
	// Get Manager_Inventory from Instigator
	ACsManager_Inventory* Manager_Inventory = nullptr;

	// Character
	if (ACsPawn* Pawn = Cast<ACsPawn>(InInstigator))
	{
		// Player
		if (ACsPlayerStateBase* PlayerState = Pawn->GetPlayerState<ACsPlayerStateBase>())
		{
			Manager_Inventory = PlayerState->Manager_Inventory;
		}
	}
	// Manager_Inventory
	else
	{
		Manager_Inventory = Cast<ACsManager_Inventory>(InInstigator);
	}

	if (Manager_Inventory)
	{
		// Fill Any
		if (Order == ECsPoolTransactionOrder::FillAny)
		{
			bool Success = false;

			for (FCsItem* Item : Items)
			{
				Success |= Transfer_Internal(Item, InInstigator, Manager_Inventory);
			}
			return Success;
		}
		// Fill Or Kill
		if (Order == ECsPoolTransactionOrder::FillOrKill)
		{
			bool Success = true;

			for (FCsItem* Item : Items)
			{
				if (Manager_Inventory->IsFull(0, Item->ShortCode))
					Success &= false;
			}

			if (Success)
			{
				for (FCsItem* Item : Items)
				{
					Transfer_Internal(Item, InInstigator, Manager_Inventory);
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
	const FString Id = Item->Id.ToString();
	Item->FileName   = Id + TEXT("_") + Item->Type.Name;
}

void ACsManager_Item::SetRootSaveDirectory(const FString& Directory)
{
	RootSaveDirectory	   = Directory + TEXT("/");
	CombinedSaveDirectory  = RootSaveDirectory + SaveDirectory;
}

FString ACsManager_Item::GetSavePath()
{
	const FString ProjectSaveDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	const FString ItemsDir		 = CombinedSaveDirectory;
	const FString Directory		= ProjectSaveDir + ItemsDir;
	return Directory;
}

void ACsManager_Item::Save(FCsItem* Item)
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	// Header
	{
		JsonWriter->WriteObjectStart(ECsFileItemHeaderCached::Str::Header);

			// Id
			JsonWriter->WriteValue(ECsFileItemHeaderCached::Str::Id, Item->Id.ToString());
			// ShortCode
			JsonWriter->WriteValue(ECsFileItemHeaderCached::Str::ShortCode, Item->ShortCode.ToString());
			// DisplayName
			JsonWriter->WriteValue(ECsFileItemHeaderCached::Str::DisplayName, Item->DisplayName);
			// Type
			JsonWriter->WriteValue(ECsFileItemHeaderCached::Str::Type, Item->Type.Name);
			// Created
			JsonWriter->WriteValue(ECsFileItemHeaderCached::Str::Created, Item->Created.ToString());
			// Timespan
			JsonWriter->WriteValue(ECsFileItemHeaderCached::Str::Timespan, Item->LifeTime.ToString());

			// Contents
			JsonWriter->WriteObjectStart(ECsFileItemHeaderCached::Str::Contents);

				const int32 Count = Item->Contents.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					JsonWriter->WriteValue(FString::FromInt(I), Item->Contents[I].ToString());
				}
			JsonWriter->WriteObjectEnd();

		JsonWriter->WriteObjectEnd();
	}
	// Products
	{
		JsonWriter->WriteArrayStart(ECsFileItemProductHeaderCached::Str::Products);

		TArray<TCsItemProductId> Keys;
		Item->Products.GetKeys(Keys);

		for (const TCsItemProductId& Key : Keys)
		{
			JsonWriter->WriteObjectStart();

			FCsItemProduct& Product	= Item->Products[Key];

			SaveProduct(JsonWriter, &Product);

			JsonWriter->WriteObjectEnd();
		}

		JsonWriter->WriteArrayEnd();
	}
	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Path		= GetSavePath();
	const FString Filename  = Path + Item->FileName + NCsCached::Ext::json;

	FFileHelper::SaveStringToFile(OutputString, *Filename);

	Item->IsSaved = true;
}

void ACsManager_Item::SaveProduct(TSharedRef<TJsonWriter<TCHAR>>& JsonWriter, FCsItemProduct* Product)
{
	// Name
	JsonWriter->WriteValue(ECsFileItemProductHeaderCached::Str::Name, Product->Name);
	// Id
	JsonWriter->WriteValue(ECsFileItemProductHeaderCached::Str::Id, Product->Id.ToString());

	// Current History
	{
		JsonWriter->WriteObjectStart(ECsFileItemHistoryHeaderCached::Str::CurrentHistory);

		SaveHistory(JsonWriter, &(Product->CurrentHistory));

		JsonWriter->WriteObjectEnd();
	}
	// Previous Histories
	{
		JsonWriter->WriteArrayStart(ECsFileItemHistoryHeaderCached::Str::PreviousHistories);

		for (FCsItemHistory& History : Product->PreviousHistories)
		{
			JsonWriter->WriteObjectStart();

			SaveHistory(JsonWriter, &History);

			JsonWriter->WriteObjectEnd();
		}

		JsonWriter->WriteArrayEnd();
	}
}

void ACsManager_Item::SaveHistory(TSharedRef<TJsonWriter<TCHAR>>& JsonWriter, FCsItemHistory* ItemHistory)
{
	// OwnerId
	JsonWriter->WriteValue(ECsFileItemHistoryHeaderCached::Str::OwnerId, ItemHistory->OwnerId.ToString());
	// OwnerType
	JsonWriter->WriteValue(ECsFileItemHistoryHeaderCached::Str::OwnerType, ItemHistory->OwnerType.Name);
	// OwnerName
	JsonWriter->WriteValue(ECsFileItemHistoryHeaderCached::Str::OwnerName, ItemHistory->OwnerName);

	// Members
	JsonWriter->WriteObjectStart(ECsFileItemHistoryHeaderCached::Str::Members);

		TArray<FName> OutKeys;
		ItemHistory->Members.GetKeys(OutKeys);

		for (const FName& Key : OutKeys)
		{
			FCsItemMemberValue& Value = ItemHistory->Members[Key];

			const TCsItemMemberValueType& ValueType = Value.Type;
			const FString KeyName				    = Key.ToString();
			// bool
			if (Value.Type == ECsItemMemberValueType::Bool)
				JsonWriter->WriteValue(KeyName, Value.GetBool());
			// uint8
			else
			if (Value.Type == ECsItemMemberValueType::Uint8)
				JsonWriter->WriteValue(KeyName, Value.GetUint8());
			// int32
			else
			if (Value.Type == ECsItemMemberValueType::Int32)
				JsonWriter->WriteValue(KeyName, Value.GetInt32());
			// floats
			else
			if (Value.Type == ECsItemMemberValueType::Float)
				JsonWriter->WriteValue(KeyName, Value.GetFloat());
		}
	JsonWriter->WriteObjectEnd();
}

void ACsManager_Item::SaveActiveItems()
{
	TArray<TCsItemId> Keys;
	ActiveItems.GetKeys(Keys);

	for (const TCsItemId& Key : Keys)
	{
		FCsItem* Item = ActiveItems[Key];

		Save(Item);
	}
}

// Async
#pragma region

FCsItem* ACsManager_Item::AllocateAsyncSave()
{
	for (uint8 I = 0; I < CS_ITEM_ASYNC_SAVE_POOL_SIZE; ++I)
	{
		const uint8 Index = (AsyncSavePoolIndex + I) % CS_ITEM_ASYNC_SAVE_POOL_SIZE;
		FCsItem* Item	  = &(AsyncSavePool[Index]);

		if (!Item->bAllocated)
		{
			Item->bAllocated = true;
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
	for (FCsItem* Item : CopiedAsyncSaveItems)
	{
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
		for (FCsItem* Item : ActiveAsyncSaveItems)
		{
			Item->AsycTaskMutex.Unlock();
		}
		ActiveAsyncSaveItems.Reset();
		PerformingAsyncSaveHandle.Clear();
	}

	if (AsyncSaveItems.Num() == CS_EMPTY)
		return;

	for (FCsItem* Item : AsyncSaveItems)
	{
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
	IFileManager::Get().FindFiles(FoundFiles, *Path, *NCsCached::Ext::json);

	if (FoundFiles.Num() == CS_EMPTY)
	{
#if WITH_EDITOR
		OnPopulateExistingItems_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
		OnPopulateExistingItems_Event.Broadcast();
		return;
	}

	TArray<FCsItem*> Items;

	for (const FString& File : FoundFiles)
	{
		FString ItemJson;
		const FString Filename = Path + File;

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
					TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(ECsFileItemHeaderCached::Str::Header)->Get()->AsObject();

					// Id
					FGuid::Parse(JsonObject->GetStringField(ECsFileItemHeaderCached::Str::Id), Item->Id);
					// ShortCode
					Item->ShortCode = FName(*JsonObject->GetStringField(ECsFileItemHeaderCached::Str::ShortCode));
					// DisplayName
					Item->DisplayName = JsonObject->GetStringField(ECsFileItemHeaderCached::Str::DisplayName);
					// Type
					Item->Type = EMCsItemType::Get().GetEnum(JsonObject->GetStringField(ECsFileItemHeaderCached::Str::Type));
					// Created
					FDateTime::Parse(JsonObject->GetStringField(ECsFileItemHeaderCached::Str::Created), Item->Created);
					// Timespan
					FTimespan::Parse(JsonObject->GetStringField(ECsFileItemHeaderCached::Str::Timespan), Item->LifeTime);

					// Contents
					const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(ECsFileItemHeaderCached::Str::Contents);

					TArray<FString> Keys;
					Object->Values.GetKeys(Keys);

					for (const FString& Key : Keys)
					{
						TSharedPtr<FJsonValue>& JsonValue = Object->Values[Key];
						FString Value					  = JsonValue->AsString();

						TCsItemId Id;
						FGuid::Parse(Value, Id);

						Item->Contents.Add(Id);
					}
				}

				SetActiveItemData(Item);

				// Products
				{
					const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonParsed->Values.Find(ECsFileItemProductHeaderCached::Str::Products)->Get()->AsArray();

					TArray<TCsItemProductId> Keys;
					Item->Products.GetKeys(Keys);

					const int32 Count = Keys.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

						const TCsItemProductId& Key = Keys[I];
						FCsItemProduct& Product		= Item->Products[Key];

						LoadProduct(Object, Item, &Product);
					}
				}

				AddActiveItemByOwnerId(Item);
				SetItemFileName(Item);

				Item->IsSaved = true;

				ActiveItems.Add(Item->Id, Item);
				Items.Add(Item);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: %s is NOT Valid."), *Filename);
			}
		}
	}

	// Check / Validate Item Contents
	const int32 ItemCount = Items.Num();

	for (int32 I = 0; I < ItemCount; ++I)
	{
		FCsItem* Item = Items[I];

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

								UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: Item: %s with Id: %s and Item: %s with Id: %s share Content with UniqueId: %d."), *ItemName, *(Item->Id.ToString()), *OtherItemName, *(OtherItem->Id.ToString()), *(Item->Contents[M].ToString()));

								ContentMismatch = true;
							}
						}
					}
				}
			}

			if (ContentMismatch)
			{
				const FString ItemName = Item->ShortCode.ToString();

				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: DeAllocating Item: %s with Id: %s because it shares some Content with other Items."), *ItemName, *(Item->Id.ToString()));

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

void ACsManager_Item::LoadProduct(TSharedPtr<class FJsonObject>& JsonObject, FCsItem* Item, FCsItemProduct* Product)
{
	// Name
	Product->Name = JsonObject->GetStringField(ECsFileItemProductHeaderCached::Str::Name);
	// Id
	FGuid::Parse(JsonObject->GetStringField(ECsFileItemProductHeaderCached::Str::Id), Product->Id);

	// Current History
	{
		TSharedPtr<FJsonObject> Object = JsonObject->Values.Find(ECsFileItemHistoryHeaderCached::Str::CurrentHistory)->Get()->AsObject();

		LoadHistory(Object, Item, &(Product->CurrentHistory));
	}
	// Previous Histories
	{
		const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->Values.Find(ECsFileItemHistoryHeaderCached::Str::PreviousHistories)->Get()->AsArray();

		const int32 Count = JsonArray.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

			LoadHistory(Object, Item, &(Product->PreviousHistories[I]));
		}
	}
}

void ACsManager_Item::LoadHistory(TSharedPtr<class FJsonObject>& JsonObject, FCsItem* Item, FCsItemHistory* ItemHistory)
{
	// OwnerId
	FGuid::Parse(JsonObject->GetStringField(ECsFileItemHistoryHeaderCached::Str::OwnerId), ItemHistory->OwnerId);
	// OwnerType
	ItemHistory->OwnerType = EMCsItemOwner::Get().GetEnum(JsonObject->GetStringField(ECsFileItemHistoryHeaderCached::Str::OwnerType));
	// OwnerName
	ItemHistory->OwnerName = JsonObject->GetStringField(ECsFileItemHistoryHeaderCached::Str::OwnerName);

	// Members
	{
		const TSharedPtr<FJsonObject>& Object = JsonObject->Values.Find(ECsFileItemHistoryHeaderCached::Str::Members)->Get()->AsObject();

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
					UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::LoadHistory: INVALID ItemMemberValue Type: %s."), *(EMCsItemMemberValueType::Get().ToString(Type)));
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

void ACsManager_Item::RecordItemsInteraction(const TArray<FCsItem*>& Items, const FECsItemInteraction& Interaction)
{
	for (FCsItem* Item : Items)
	{
		RecordItemInteraction(Item, Interaction);
	}
}

void ACsManager_Item::RecordItemInteraction(FCsItem* Item, const FECsItemInteraction& Interaction){}

#pragma endregion Action