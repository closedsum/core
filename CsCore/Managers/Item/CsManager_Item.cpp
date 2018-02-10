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
// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Item.h"
#include "Data/CsData_Interactive.h"

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
	UniqueIdIndex = CS_ITEM_UNIQUE_ID_START_INDEX;

	SaveDirectory = TEXT("Items/");
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

void ACsManager_Item::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, const FCsItem* const Item)
{
	if (CsCVarLogManagerItemTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ItemName				  = Item->ShortCode.ToString();
		const FString Id					  = FString::Printf(TEXT("%llu"), Item->UniqueId);
		const FString DataName				  = Item->GetData()->ShortCode.ToString();
		const ACsData_Interactive* Data_Actor = Item->GetData_Actor();
		const FString DataActorName			  = Data_Actor ? Data_Actor->ShortCode.ToString() : ECsCachedString::Str::Empty;
		const float CurrentTime				  = GetWorld()->GetTimeSeconds();

		if (Data_Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with ID: %s, Data: %s, and with Data_Actor: %s at %f."), *FunctionName, *TransactionAsString, *ItemName,*Id, *DataName, *DataActorName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Item: %s with ID: % and Data: %s at %f."), *FunctionName, *TransactionAsString, *ItemName, *Id, *DataName, CurrentTime);
		}
	}
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
	Item->Capacity = Data->GetCapacity();

	Item->Data = Data;
	// Get Data for Actor when this Item is Dropped
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
	Item->Data					= Cast<ACsData_Item>(DataMapping->GetLoadedData(ItemAssetType, Item->ShortCode));

	Item->InventoryProperties.Dimension = *(Item->Data->GetDimension());
	Item->Capacity						= Item->Data->GetCapacity();

	if (ACsData_Item* Data = Item->GetData())
		Item->Data_Actor = Cast<ACsData_Interactive>(DataMapping->GetLoadedData(InteractiveAssetType, Data->GetSpawnedActorDataShortCode()));
}

// Get
#pragma region

FCsItem* ACsManager_Item::GetItem(const uint64 &Id)
{
	return *(ActiveItems.Find(Id));
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
		OutItems.Reset();
		return;
	}

	const int32 Count = Items->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutItems.Add((*Items)[I]);
	}
}

#pragma endregion Get

// DeAllocate
#pragma region

void ACsManager_Item::DeAllocate(FCsItem* Item)
{
	DeAllocate(Item->UniqueId);
}

void ACsManager_Item::DeAllocate(const uint64 &Id)
{
	FCsItem* Item = *(ActiveItems.Find(Id));

	if (!Item)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::DeAllocate: Attempting to deallocate an Item with UniqueId: %d, but it is already deallocated."), Id);
		return;
	}

	// If Save EXISTS, Delete it.
	if (Item->IsSaved)
	{
		const FString Path	   = GetSavePath();
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

#pragma endregion DeAllocate

// Transfer
#pragma region

bool ACsManager_Item::Transfer(FCsItem* Item, UObject* Instigator)
{
	DeAllocate(Item);
	return true;
}

bool ACsManager_Item::Transfer(TArray<FCsItem*> &Items, UObject* Instigator, const TCsPoolTransactionOrder &Order)
{
	const int32 Count = Items.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		Transfer(Items[I], Instigator);
	}
	return true;
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
			JsonWriter->WriteObjectStart();

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

			JsonWriter->WriteObjectEnd();
		}
	JsonWriter->WriteObjectEnd();
}

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

				FCsItem* Item = Allocate();

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
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: %s is NOT Valid"), *Filename);

#if WITH_EDITOR
				OnPopulateExistingItems_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
				OnPopulateExistingItems_Event.Broadcast();
				return;
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
		TSharedPtr<FJsonObject> Object = JsonObject->Values.Find(ECsFileItemHistoryHeaderCachedString::Str::Members)->Get()->AsObject();

		TArray<FCsItemMemberDescription>* Members = Item->GetData()->GetMembers();

		const uint8 Count = Members->Num();

		for (uint8 I = 0; I < Count; ++I)
		{
			FCsItemMemberDescription& Member = (*Members)[I];

			const FString MemberNameAsString = Member.Name.ToString();
			const FName& MemberName			 = Member.Name;

			const TCsItemMemberValueType& Type = Member.Type;

			FCsItemMemberValue Value;
			Value.Type = Type;

			// bool
			if (Type == ECsItemMemberValueType::Bool)
			{
				Value.Value_bool = Object->GetBoolField(MemberNameAsString);
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
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::LoadHistory: INVALID ItemMemberValue Type: %s"), *(ECsItemMemberValueType::ToString(Type)));
			}
			ItemHistory->Members.Add(MemberName, Value);
		}
	}
}

void ACsManager_Item::InitInventory(ACsManager_Inventory* Manager_Inventory){}
void ACsManager_Item::AsyncInitInventory(ACsManager_Inventory* Manager_Inventory) {}

#pragma endregion Save / Load