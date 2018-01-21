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

		SaveHistory(JsonWriter, &(Item->CurrentHistory));

		JsonWriter->WriteObjectEnd();
	}
	// Previous Histories
	{
		JsonWriter->WriteArrayStart(ECsFileItemHistoryHeaderCachedString::Str::PreviousHistories);

		const int32 Count = Item->PreviousHistories.Num();

		for (int32 I = 0; I < Count; I++)
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

		for (int32 I = 0; I < Count; I++)
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

UScriptStruct* ACsManager_Item::GetScriptStructForItemType(const TCsItemType &ItemType)
{
	return nullptr;
}

void ACsManager_Item::PopulateExistingItems()
{
	TArray<FString> FoundFiles;

	const FString Path = GetSavePath();

	IFileManager::Get().FindFiles(FoundFiles, *Path, *ECsCachedString::Str::Json);

	const int32 FileCount = FoundFiles.Num();

	if (FileCount == CS_EMPTY)
		return;

	for (int32 I = 0; I < FileCount; I++)
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
					// Name
					Item->Name = FName(*JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Name));
					// DisplayName
					Item->DisplayName = JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::DisplayName);
					// Type
					Item->TypeAsString = JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Type);
					Item->SetType((*StringToItemType)(Item->TypeAsString));
					// Created
					FDateTime::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Created), Item->Created);
					// Timespan
					FTimespan::Parse(JsonObject->GetStringField(ECsFileItemHeaderCachedString::Str::Timespan), Item->LifeTime);
				}
				// Current History
				{
					TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(ECsFileItemHistoryHeaderCachedString::Str::CurrentHistory)->Get()->AsObject();
					
					LoadHistory(JsonObject, Item, &(Item->CurrentHistory));
				}
				// Previous Histories
				{
					const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonParsed->Values.Find(ECsFileItemHistoryHeaderCachedString::Str::PreviousHistories)->Get()->AsArray();

					const int32 Count = JsonArray.Num();

					for (int32 I = 0; I < Count; I++)
					{
						TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

						LoadHistory(Object, Item, &(Item->PreviousHistories[I]));
					}
				}

				AddActiveItemByOwnerId(Item);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_Item::PopulateExistingItems: %s is NOT Valid"), *Filename);
				return;
			}
		}
	}
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

		UScriptStruct* ScriptStruct = GetScriptStructForItemType(Item->Type);

		for (TFieldIterator<UProperty> It(ScriptStruct); It; ++It)
		{
			UProperty* Property = Cast<UProperty>(*It);

			const FString MemberNameAsString = Property->GetName();
			const FName MemberName			 = Property->GetFName();

			// bool
			if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			{
				FCsItemMemberValue Value;
				Value.Type		 = ECsItemMemberValueType::Bool;
				Value.Value_bool = Object->GetBoolField(MemberNameAsString);
				ItemHistory->Members.Add(MemberName, Value);
				continue;
			}
			// uint8
			if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
			{
				// enum
				if (ByteProperty->IsEnum())
				{
				}
				else
				{
					FCsItemMemberValue Value;
					Value.Type		  = ECsItemMemberValueType::Uint8;
					Value.Value_uint8 = (uint8)Object->GetIntegerField(MemberNameAsString);
					ItemHistory->Members.Add(MemberName, Value);
					continue;
				}
			}
			// int32
			if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			{
				FCsItemMemberValue Value;
				Value.Type		  = ECsItemMemberValueType::Int32;
				Value.Value_int32 = Object->GetIntegerField(MemberNameAsString);
				ItemHistory->Members.Add(MemberName, Value);
				continue;
			}
			// float
			if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			{
				FCsItemMemberValue Value;
				Value.Type		  = ECsItemMemberValueType::Float;
				Value.Value_float = (float)Object->GetNumberField(MemberNameAsString);
				ItemHistory->Members.Add(MemberName, Value);
				continue;
			}
		}
	}
}

void ACsManager_Item::InitInventory(ACsManager_Inventory* Manager_Inventory){}