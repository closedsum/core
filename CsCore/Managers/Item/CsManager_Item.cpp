// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Item/CsManager_Item.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "FileManager.h"

// Managers
#include "Managers/Inventory/CsManager_Inventory.h"

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

	const FString GameDir   = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	const FString ItemsDir  = TEXT("Items/");
	const FString Directory = GameDir + ItemsDir;

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
					FDateTime::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Created), Item->Created); continue;
					// Timespan
					FTimespan::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Timespan), Item->LifeTime); continue;
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