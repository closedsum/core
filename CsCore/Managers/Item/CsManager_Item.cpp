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

ACsManager_Item::ACsManager_Item(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UniqueIdIndex = CS_ITEM_UNIQUE_ID_START_INDEX;

	SavePath = TEXT("Items/");
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

void ACsManager_Item::SetItemOwnerInfo(FCsItem* Item, UObject* ItemOwner){}

FCsItem* ACsManager_Item::Allocate(const TCsItemType &ItemType, UObject* ItemOwner)
{
	FCsItem* Item = Allocate(ItemType);

	SetItemOwnerInfo(Item, ItemOwner);

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
	return Item;
}

FCsItem* ACsManager_Item::GetItem(const uint64 &Id)
{
	return *(ActiveItems.Find(Id));
}

void ACsManager_Item::GetItemsByOwnerType(const TCsItemOwner &OwnerType, TArray<FCsItem*> &OutItems)
{
	TArray<uint64> OutKeys;
	ActiveItems.GetKeys(OutKeys);

	const int32 Count = OutKeys.Num();

	for (int32 I = 0; I < Count; I++)
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

	for (int32 I = 0; I < Count; I++)
	{
		OutItems.Add((*Items)[I]);
	}
}

void ACsManager_Item::SetItemFileName(FCsItem* Item)
{
	const FString Id = UCsCommon::UInt64ToString(Item->UniqueId);
	Item->FileName   = Id + TEXT("_") + (*ItemTypeToString)(Item->Type);
}

FString ACsManager_Item::GetSaveDirectory()
{
	const FString GameSaveDir = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir());
	const FString ItemsDir	  = SavePath;
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
			// Name
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Name, Item->Name.ToString());
			// DisplayName
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::DisplayName, Item->DisplayName);
			// Type
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Type, (*ItemTypeToString)(Item->Type));
			// Created
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Created, Item->Created.ToString());
			// Timespan
			JsonWriter->WriteValue(ECsFileItemHeaderCachedString::Str::Timespan, Item->LifeTime.ToString());

		JsonWriter->WriteObjectEnd();
	}

	// Current History
	{
		JsonWriter->WriteObjectStart(ECsFileItemHistoryHeaderCachedString::Str::CurrentHistory);

			// OwnerId
			JsonWriter->WriteValue(ECsFileItemHistoryHeaderCachedString::Str::OwnerId, FString::Printf(TEXT("%llu"), Item->CurrentHistory.OwnerId));
			// OwnerType
			JsonWriter->WriteValue(ECsFileItemHistoryHeaderCachedString::Str::OwnerType, (*ItemOwnerToString)(Item->CurrentHistory.OwnerType));
			// OwnerName
			JsonWriter->WriteValue(ECsFileItemHistoryHeaderCachedString::Str::OwnerName, Item->CurrentHistory.OwnerName);

			// Members
			JsonWriter->WriteObjectStart(ECsFileItemHistoryHeaderCachedString::Str::Members);

				TArray<FName> OutKeys;
				Item->CurrentHistory.Members.GetKeys(OutKeys);

				const int32 Count = OutKeys.Num();

				for (int32 I = 0; I < Count; I++)
				{
					FCsItemMemberValue* Value = Item->CurrentHistory.Members.Find(OutKeys[I]);

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

		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Directory = GetSaveDirectory();
	const FString Filename  = Directory + Item->FileName + ECsCachedString::Str::Json;

	FFileHelper::SaveStringToFile(OutputString, *Filename);
}

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
	}
	AvailableUnqiueIds.Add(Item->UniqueId);
	Item->Reset();
}

void ACsManager_Item::PopulateExistingItems()
{
	TArray<FString> FoundFiles;

	const FString Directory = GetSaveDirectory();

	IFileManager::Get().FindFiles(FoundFiles, *Directory, *ECsCachedString::Str::Json);

	const int32 FileCount = FoundFiles.Num();

	if (FileCount == CS_EMPTY)
		return;

	for (int32 I = 0; I < FileCount; I++)
	{
		FString ItemJson;
		const FString Filename = FoundFiles[I];

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
				//UCsCommon_Load::ReadObjectFromJson(JsonParsed, this, GetClass(), CategoryMemberAssociations, ReadObjectFromJson_Internal);

				FCsItem* Item = Allocate();

				// ReadItemFromJson

				// Header
				{
					TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(TEXT("Header"))->Get()->AsObject();

					// UniqueId
					Item->UniqueId = (uint64)JsonObject->GetNumberField(ECsFileItemHeaderCachedString::Str::UniqueId);
					// Name
					Item->Name = FName(*JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Name));
					// DisplayName
					Item->DisplayName = JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::DisplayName);
					// Type
					Item->Type = (*StringToItemType)(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Type));
					// Created
					FDateTime::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Created), Item->Created);
					// Timespan
					FTimespan::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Timespan), Item->LifeTime);
				}
					// Current History
				LoadCurrentHistory(JsonParsed, Item);
				LoadPreviousHistories(JsonParsed, Item);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: %s is NOT Valid"), *Filename);
				return;
			}
		}
	}
}

void ACsManager_Item::LoadCurrentHistory(TSharedPtr<FJsonObject> &JsonParsed, FCsItem* Item){}
void ACsManager_Item::LoadPreviousHistories(TSharedPtr<FJsonObject> &JsonParsed, FCsItem* Item){}

void ACsManager_Item::InitInventory(ACsManager_Inventory* Manager_Inventory){}