// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDataMapping.h"
#include "CsCore.h"
#include "Common/CsCommon_Load.h"
#include "Common/CsCommon.h"
#include "Data/CsData.h"
#include "Managers/CsManager_Loading.h"
#include "Data/CsData_Payload.h"

#if WITH_EDITOR
#include "Developer/SourceControl/Public/SourceControlHelpers.h"
#endif WITH_EDITOR

ACsDataMapping::ACsDataMapping(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AssetTypeToString = nullptr;
	StringToAssetType = nullptr;
}

void ACsDataMapping::ClearLoaded()
{
}

TArray<FCsDataMappingEntry>* ACsDataMapping::GetDataMappings(const TCsAssetType &AssetType)
{
	return nullptr;
}

TMap<FName, FCsDataMappingEntry>* ACsDataMapping::GetDataMappings_Map(const TCsAssetType &AssetType)
{
	return nullptr;
}

void ACsDataMapping::GenerateMaps(const TCsAssetType &AssetType)
{
	TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType);

	if (!Mapping)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GenerateMaps: Warning. No DataMapping found for AssetType: %s"), *((*AssetTypeToString)(AssetType)));
		return;
	}

	TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(AssetType);

	if (!Map)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GenerateMaps: Warning. No DataMapping_Map found for AssetType: %s"), *((*AssetTypeToString)(AssetType)));
		return;
	}

	Map->Reset();

	const uint16 Count = Mapping->Num();

	for (uint16 I = 0; I < Count; I++)
	{
		Map->Add((*Mapping)[I].ShortCode, (*Mapping)[I]);
	}
	Map->KeySort(TLess<FName>());
}

void ACsDataMapping::GenerateMaps()
{
	const uint8 AssetCount = AssetType_MAX;

	for (uint8 I = 0; I < AssetCount; I++)
	{
		GenerateMaps((TCsAssetType)I);
	}
}

TCsAssetType ACsDataMapping::GetDataAssetType(const FName &ShortCode)
{
	// Search TMaps - Populated if GenerateMaps was called
	const uint8 AssetCount = (uint8)AssetType_MAX;

	for (uint8 I = 0; I < AssetCount; I++)
	{
		const TCsAssetType AssetType		  = (TCsAssetType)I;
		TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(AssetType);

		if (!Map)
			continue;

		if (FCsDataMappingEntry* Entry = Map->Find(ShortCode))
		{
			if (Entry->Data)
			{
				return AssetType;
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GetDataAssetType: No Data set for AssetType: %s with ShortCode: %s"), *((*AssetTypeToString)(AssetType)), *ShortCode.ToString());
			}
		}
	}
	// Search TArrays
	for (uint8 I = 0; I < AssetCount; I++)
	{
		const TCsAssetType AssetType		 = (TCsAssetType)I;
		TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType);

		if (!Mapping)
			continue;

		const uint16 Count = Mapping->Num();

		for (uint16 J = 0; J < Count; J++)
		{
			if ((*Mapping)[J].ShortCode == ShortCode)
				return AssetType;
		}
	}
	return AssetType_MAX;
}

ACsData_Payload* ACsDataMapping::GetPayload()
{
	return Payload->GetDefaultObject<ACsData_Payload>();
}

// Asset References
#pragma region

void ACsDataMapping::PreSave(const class ITargetPlatform* TargetPlatform)
{
#if WITH_EDITOR
	// Set LookUpCodes
	const uint8 AssetCount = (uint8)AssetType_MAX;

	for (uint8 I = 0; I < AssetCount; I++)
	{
		const TCsAssetType AssetType		 = (TCsAssetType)I;
		TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType);

		const uint16 Count = Mapping->Num();

		for (uint16 J = 0; J < Count; J++)
		{
			(*Mapping)[J].LookUpCode = J;
		}
	}
#endif // #if WITH_EDITOR
	Super::PreSave(TargetPlatform);
#if WITH_EDITOR
	PopulateAssetReferences();
	UCsCommon_Load::GetCategoryMemberAssociations(this, GetClass(), CategoryMemberAssociations);
	SaveToJson();
#endif // #if WITH_EDITOR
}

bool ACsDataMapping::DoesDataAssetReferenceExist(const TCsAssetType &AssetType, const FName &ShortCode)
{
	// Search TMaps - Populated if GenerateMaps was called
	if (TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(AssetType))
	{
		if (FCsDataMappingEntry* Entry = Map->Find(ShortCode))
		{
			if (Entry->Data)
			{
				return true;
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::DoesDataAssetReferenceExist: No Data set for AssetType: %s with ShortCode: %s"), *((*AssetTypeToString)(AssetType)), *ShortCode.ToString());
			}
		}
	}
	// Search TArrays
	if (TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType))
	{
		const uint16 Count = Mapping->Num();

		for (uint16 I = 0; I < Count; I++)
		{
			if ((*Mapping)[I].ShortCode == ShortCode)
			{
				if ((*Mapping)[I].Data)
				{
					return true;
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::DoesDataAssetReferenceExist: No Data set for AssetType: %s with ShortCode: %s"), *((*AssetTypeToString)(AssetType)), *ShortCode.ToString());
				}
			}
		}
	}
	return false;
}

bool ACsDataMapping::DoesDataAssetReferenceExist(const FName &ShortCode)
{
	bool Exist			   = false;
	const uint8 AssetCount = (uint8)AssetType_MAX;

	for (uint8 I = 0; I < AssetCount; I++)
	{
		Exist |= DoesDataAssetReferenceExist((TCsAssetType)I, ShortCode);
	}
	return Exist;
}

bool ACsDataMapping::AddDataAssetReference(const TCsAssetType &AssetType, const FName &ShortCode, AActor* InData)
{
	if (AssetType == AssetType_MAX)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::AddDataAssetReference: Warning. Using INVALID AssetType: ECsAssetType_MAX when adding ShortCode: %s"), *ShortCode.ToString());
		return false;
	}

	if (TArray<FCsDataMappingEntry>* Mappings = GetDataMappings(AssetType))
	{
		if (!DoesDataAssetReferenceExist(AssetType, ShortCode))
		{
			// Add to DataMappings
			FCsDataMappingEntry Mapping;
			Mapping.ShortCode = ShortCode;
			Mapping.Data = InData;
			Mappings->Add(Mapping);
			// Add to TMap DataMappings
			TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(AssetType);

			if (!Map)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::AddDataAssetReference: Warning. No DataMapping_Map found for AssetType: %s"), *((*AssetTypeToString)(AssetType)));
				return true;
			}
			Map->Add(ShortCode, Mapping);
			Map->KeySort(TLess<FName>());
			return true;
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::AddDataAssetReference: Warning. Mapping AssetType: %s and ShortCode: %s have ALREADY been ADDED."), *((*AssetTypeToString)(AssetType)), *ShortCode.ToString());
			return false;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::AddDataAssetReference: Warning. Using AssetType: %s does NOT exist."), *((*AssetTypeToString)(AssetType)));
	return false;
}

FStringAssetReference ACsDataMapping::GetStringAssetReference(const TCsAssetType &AssetType, const FName &ShortCode)
{
	TMap<FName, FCsDataMappingEntry>* Mapping = GetDataMappings_Map(AssetType);
	FCsDataMappingEntry* Entry				  = Mapping->Find(ShortCode);
	return Entry ? Entry->Data.ToStringReference() : FStringAssetReference();
}

FStringAssetReference ACsDataMapping::GetStringAssetReference(const TCsAssetType &AssetType, const uint16 &LookUpCode)
{
	TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType);

	if (Mapping->Num() <= LookUpCode)
		return FStringAssetReference();
	return (*Mapping)[LookUpCode].Data.ToStringReference();
}

void ACsDataMapping::GetStringAssetReferences(const TCsAssetType &AssetType, const FName &ShortCode, const ECsLoadFlags &LoadFlags, TArray<FStringAssetReference> &OutReferences)
{
	TMap<FName, FCsDataMappingEntry>* Mapping = GetDataMappings_Map(AssetType);
	FCsDataMappingEntry* Entry				  = Mapping->Find(ShortCode);

	if (!Entry)
		return;
	Entry->AssetReferences[(int32)LoadFlags].Get(OutReferences);
}

void ACsDataMapping::GetStringAssetReferences(const TCsAssetType &AssetType, const uint16 &LookUpCode, const ECsLoadFlags &LoadFlags, TArray<FStringAssetReference> &OutReferences)
{
	TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType);

	if (Mapping->Num() <= LookUpCode)
		return;
	(*Mapping)[LookUpCode].AssetReferences[(int32)LoadFlags].Get(OutReferences);
}

void ACsDataMapping::PopulateDataAssetReferences()
{
	int32 AssetTypeIndex = INDEX_NONE;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					AssetTypeIndex++;

					const TCsAssetType AssetType = (TCsAssetType)AssetTypeIndex;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; I++)
						{
							const FStringAssetReference AssetRef = (*Member)[I].Data.ToStringReference();
							const FString Asset					 = AssetRef.ToString();

							if (Asset == TEXT(""))
							{
								UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PopulateAssetReferences: No data set for AssetType: %s using Short Code: %s"), *((*AssetTypeToString)(AssetType)), *((*Member)[I].ShortCode.ToString()));
								continue;
							}
							DataAssetReferences.Add(AssetRef);
						}
					}
					continue;
				}
				continue;
			}
			continue;
		}
	}
}

void ACsDataMapping::PopulateAssetReferences()
{
	const int32 FlagCount = ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX;

	for (int32 I = 0; I < FlagCount; I++)
	{
		AssetReferences[I].Reset();
	}

	int32 AssetTypeIndex = INDEX_NONE;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					AssetTypeIndex++;

					const TCsAssetType AssetType = (TCsAssetType)AssetTypeIndex;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; I++)
						{
							ACsData* OutAsset;

							UCsCommon_Load::LoadTAssetSubclassOf<ACsData>((*Member)[I].Data, OutAsset, TEXT("Actor"));

							if (!OutAsset)
							{
								UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PopulateAssetReferences: No data set for AssetType: %s using Short Code: %s"), *((*AssetTypeToString)(AssetType)), *((*Member)[I].ShortCode.ToString()));
								continue;
							}

							const FStringAssetReference AssetRef = (*Member)[I].Data.ToStringReference();
							const FString Asset					 = AssetRef.ToString();

							const int32 LoadFlags = (*Member)[I].Data_LoadFlags;

							for (int32 J = 0; J < FlagCount; J++)
							{
								(*Member)[I].AssetReferences[J].References.Reset();

								if (!CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags(J)))
									continue;

								// Reference to "Root" Data
								(*Member)[I].AssetReferences[J].References.AddDefaulted();

								const int32 Size = (*Member)[I].AssetReferences[J].References.Num();

								FCsStringAssetReference& Reference = (*Member)[I].AssetReferences[J].References[Size - 1];
								Reference.Reference				   = Asset;
								Reference.Reference_Internal	   = AssetRef;
								Reference.Size.Bytes			   = OutAsset->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
								Reference.Size.Kilobytes		   = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
								Reference.Size.Megabytes		   = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);

								AssetReferences[J].References.Add(Reference);

								// References to anything Data references
								int32 ReferenceCount = OutAsset->AssetReferences[J].References.Num();
								
								for (int32 K = 0; K < ReferenceCount; K++)
								{
									(*Member)[I].AssetReferences[J].References.Add(OutAsset->AssetReferences[J].References[K]);
									AssetReferences[J].References.Add(OutAsset->AssetReferences[J].References[K]);
								}

								(*Member)[I].AssetReferences[J].CalculateSize();
							}
						}
					}
					continue;
				}
				continue;
			}
			continue;
		}
	}

	for (int32 I = 0; I < FlagCount; I++)
	{
		AssetReferences[I].CalculateSize();
	}
}

#pragma endregion Asset References

// Load
#pragma region

ECsLoadFlags ACsDataMapping::GetLoadAssetsFlags(const TCsLoadAssetsType &AssetsType)
{
	return ECsLoadFlags::All;
}

void ACsDataMapping::GetLoadAssetsShortCodes(const TCsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes)
{
}

void ACsDataMapping::GetLoadStringAssetReferences(const TCsLoadAssetsType &AssetsType, TArray<FStringAssetReference> &OutAssetReferences)
{
}

void ACsDataMapping::OnFinishedAsyncLoadingAssetsSetReferences(const TCsLoadAssetsType &AssetsType, const TArray<UObject*> &LoadedAssets)
{
}

ACsData* ACsDataMapping::LoadData(const FName &ShortCode, const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::Game*/)
{
	TCsAssetType AssetType = AssetType_MAX;

	// Search Loaded Data TMaps / TArray
	if (ACsData* Data = GetLoadedData(ShortCode, AssetType))
		return Data;

	// Search TMaps - Populated if GenerateMaps was called
	const uint8 AssetCount = (uint8)AssetType_MAX;

	for (uint8 I = 0; I < AssetCount; I++)
	{
		TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map((TCsAssetType)I);

		if (!Map)
			continue;

		FCsDataMappingEntry* Entry = Map->Find(ShortCode);

		if (!Entry)
			continue;

		if (ACsData* Data = LoadData_Internal<ACsData>(AssetType, *Entry, LoadFlags))
			return Data;
	}
	// Search TArrays
	for (uint8 I = 0; I < AssetCount; I++)
	{
		TArray<FCsDataMappingEntry>* Mapping = GetDataMappings((TCsAssetType)I);

		if (!Mapping)
			continue;

		const uint16 Count = Mapping->Num();

		for (uint16 J = 0; J < Count; J++)
		{
			if ((*Mapping)[J].ShortCode == ShortCode)
			{
				if (ACsData* Data = LoadData_Internal<ACsData>(AssetType, (*Mapping)[J], LoadFlags))
					return Data;
			}
		}
	}
	UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::LoadData: Could NOT find Data with ShortCode: %s"), *ShortCode.ToString());
	return nullptr;
}

// Add
#pragma region

void ACsDataMapping::AddLoadedData(const TCsAssetType &AssetType, const FName &ShortCode, ACsData* InData)
{
}

void ACsDataMapping::AddLoadedData(const TCsAssetType &AssetType, const uint16 &LookUpCode, ACsData* InData)
{
}

#pragma endregion Add

// Get
#pragma region

ACsData* ACsDataMapping::GetLoadedData(const TCsAssetType &AssetType, const FName &ShortCode)
{
	return nullptr;
}

ACsData* ACsDataMapping::GetLoadedData(const FName &ShortCode, TCsAssetType &OutAssetType)
{
	OutAssetType = AssetType_MAX;
	return nullptr;
}

ACsData* ACsDataMapping::GetLoadedData(const FName &ShortCode)
{
	TCsAssetType OutAssetType;
	return GetLoadedData(ShortCode, OutAssetType);
}

ACsData* ACsDataMapping::GetLoadedData(const TCsAssetType &AssetType, const uint16 &LookUpCode)
{
	return nullptr;
}

#pragma endregion Get

#pragma endregion Load

// IsValid
#pragma region

template<typename T>
bool ACsDataMapping::CheckDataIsValid(const FString &FunctionName, const TCsAssetType &AssetType, const FName &ShortCode, const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::Game*/)
{
	if (ShortCode == NAME_None)
		return true;

	bool Pass = true;

	TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(AssetType);
	const int32 Count					 = Mapping.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		if (ShortCode != Mapping[Index].ShortCode)
			continue;

		// Load the Data
		if (T* DataDOb = LoadData<T>(FunctionName, AssetType, Mapping[Index], IsUI))
		{
			ACsData* Data = CastChecked<ACsData>(DataDOb);

			Data->Load(LoadFlags);
			Pass &= Data->IsValid();
			return Pass;
		}
	}
	return true;
}

template<typename T>
bool ACsDataMapping::CheckDataIsValid(const FString &FunctionName, const TCsAssetType &AssetType, FCsDataMappingEntry& Mapping, const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::Game*/)
{
	// Load the Data
	AActor* OutAsset;

	UCsCommon_Load::LoadTAssetSubclassOf<AActor>(Mapping.Data, OutAsset, TEXT("Actor"));

	T* DataDOb = Cast<T>(OutAsset);

	if (!DataDOb)
	{
		const FString ShortCode		   = Mapping.ShortCode.ToString();
		const FString AssetDescription = UCsCommon_Load::GetAssetDescription<AActor>(Mapping.Data);

		UE_LOG(LogCs, Warning, TEXT("%s: Failed to load data using Short Code: %s with Path Location: %s"), *FunctionName, *ShortCode, *AssetDescription);
		return true;
	}

	ACsData* Data = CastChecked<ACsData>(DataDOb);

	Data->Load(LoadFlags);
	return Data->IsValid();
}

template<typename T>
bool ACsDataMapping::CheckAllDataIsValid(const FString &FunctionName, const TCsAssetType &AssetType, const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::Game*/)
{
	TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(AssetType);
	const int32 Count					 = Mapping.Num();

	bool Pass = true;

	for (int32 Index = 0; Index < Count; Index++)
	{
		Pass &= CheckDataIsValid<T>(FunctionName, AssetType, Mapping[Index], LoadFlags);
	}
	return Pass;
}

#pragma endregion IsValid

// Get
#pragma region

FName ACsDataMapping::GetShortCode(const TCsAssetType &AssetType, const uint16 &LookUpCode)
{
	if (LookUpCode == CS_INVALID_LOOK_UP_CODE_MAX)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GetShortCode: Failed find ShortCode using INVALID LookUpCode."));
		return CS_INVALID_SHORT_CODE;
	}

	TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(AssetType);

	const int32 Count = Mapping->Num();

	if (LookUpCode >= Count)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GetShortCode: LookUpCode: %d is Out of Bounds (%d)."), LookUpCode, Count);
		return CS_INVALID_SHORT_CODE;
	}
	return (*Mapping)[LookUpCode].ShortCode;
}

uint16 ACsDataMapping::GetLookUpCode(const TCsAssetType &AssetType, const FName &ShortCode)
{
	if (ShortCode == CS_INVALID_SHORT_CODE)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GetLookUpCode: Failed to find LookUpCode using INVALID ShortCode."));
		return CS_INVALID_LOOK_UP_CODE_MAX;
	}

	TMap<FName, FCsDataMappingEntry>* Mapping = GetDataMappings_Map(AssetType);
	FCsDataMappingEntry* Entry = Mapping->Find(ShortCode);

	if (!Entry)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::GetLookUpCode: Failed to find LookUpCode using ShortCode: %s."), *ShortCode.ToString());
		return CS_INVALID_LOOK_UP_CODE_MAX;
	}
	return Entry->LookUpCode;
}

#pragma endregion Get

// Json
#pragma region

void ACsDataMapping::PostLoad()
{
	Super::PostLoad();
	LoadFromJson();
	PopulateDataAssetReferences();
}

FString ACsDataMapping::GetAbsolutePath()
{
	const FString AssetName	   = TEXT("bp_data_mapping.");
	const FString InternalName = GetName();
	FString PathName		   = GetPathName();

	PathName = PathName.Replace(*InternalName, TEXT(""));
	PathName = PathName.Replace(*AssetName, TEXT(""));
	PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

	const FString GameContentDir = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir());
	const FString JsonDir		 = TEXT("Json/");
	return GameContentDir + JsonDir + PathName;
}

void ACsDataMapping::SaveToJson()
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	UCsCommon_Load::WriteObjectToJson(JsonWriter, (void*)this, GetClass(), CategoryMemberAssociations, WriteObjectToJson_Internal);

	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Filename = GetAbsolutePath() + TEXT("bp_data_mapping") + TEXT(".json");

	FFileHelper::SaveStringToFile(OutputString, *Filename);

#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()) || UCsCommon::IsPlayInGame(GetWorld()))
		return;

	FText ErrorMessage;

	SourceControlHelpers::CheckoutOrMarkForAdd(Filename, FText::FromString(Filename), NULL, ErrorMessage);
#endif // #if WITH_EDITOR
}

void ACsDataMapping::LoadFromJson()
{
	const FString AssetName = TEXT("bp_data_mapping");
	const FString Filename  = GetAbsolutePath() + AssetName + TEXT(".json");

	FString DataJson;

	if (FFileHelper::LoadFileToString(DataJson, *Filename))
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(DataJson);

		TSharedPtr<FJsonObject> JsonParsed;

		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
		{
			if (CategoryMemberAssociations.Num() == 0)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::LoadFromJson (%s): Data needs to be saved at least ONCE to generate CategoryMemberAssociations"), *AssetName);
				return;
			}
			UCsCommon_Load::ReadObjectFromJson(JsonParsed, this, GetClass(), CategoryMemberAssociations, ReadObjectFromJson_Internal);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::LoadFromJson (%s): %s is NOT Valid"), *AssetName, *Filename);
			return;
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::LoadFromJson (%s): %s NOT found"), *AssetName, *Filename);
		return;
	}

	if (UCsCommon::IsPlayInPIE(GetWorld()) || UCsCommon::IsPlayInGame(GetWorld()))
		HasLoadedFromJson = true;
}

#pragma endregion Json

// 99 Editor
#pragma region

#if WITH_EDITOR

bool ACsDataMapping::PerformFindEntry(const FName &ShortCode, TArray<FCsDataMappingEntry*> &OutEntries, TArray<TCsAssetType> &OutAssetTypes, TArray<int32> &OutIndices)
{
	int32 AssetTypeIndex = INDEX_NONE;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					AssetTypeIndex++;

					const TCsAssetType AssetType    = (TCsAssetType)AssetTypeIndex;
					const FString AssetTypeAsString = (*AssetTypeToString)(AssetType);

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; I++)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								OutEntries.Add(&Entry);
								OutAssetTypes.Add(AssetType);
								OutIndices.Add(I);
							}
						}
					}
				}
			}
		}
	}
	return OutEntries.Num() > CS_EMPTY;
}

bool ACsDataMapping::PerformAddEntry(const FName &ShortCode, const TCsAssetType &AssetType, const int32 &LoadFlags, FString &OutMessage, FString &OutOutput)
{
	// Check for valid ShortCode
	if (ShortCode == NAME_None ||
		ShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	// Check if AssetType Exists
	if (AssetType == AssetType_MAX)
	{
		OutMessage = TEXT("INVALID AssetType.");
		OutOutput = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	// Search Entries

	int32 AssetTypeIndex = INDEX_NONE;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					AssetTypeIndex++;

					if ((TCsAssetType)AssetTypeIndex != AssetType)
						continue;

					const FString AssetTypeAsString = (*AssetTypeToString)(AssetType);

					bool Found = false;
					int32 FoundCount = 0;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						// Check if Asset has ALREADY been added
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; I++)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								if (Found)
									OutOutput += TEXT(", ");
								// Check Data exists
								if (Entry.Data.ToString() == TEXT(""))
								{
									const FString Output = TEXT("ACsDataMapping::PerformAddEntry: Warning. No Data set for [") + AssetTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("].");

									if (UCsCommon::IsDefaultObject(this))
										UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

									UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
								}
								// Check LoadFlags
								if (Entry.Data_LoadFlags != LoadFlags)
								{
									for (int32 J = 0; J < ECS_LOAD_FLAGS_EDITOR_MAX; J++)
									{
										if (CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, J))
										{
											if (!CS_TEST_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J))
											{
												const FString PreviousDataLoadFlagsAsString = TEXT("(") + UCsCommon::LoadFlagsToString(Entry.Data_LoadFlags) + TEXT(")");

												CS_SET_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J);

												const FString DataLoadFlagsAsString = TEXT("(") + UCsCommon::LoadFlagsToString(Entry.Data_LoadFlags) + TEXT(")");
												const FString LoadFlagsAsString		= TEXT("(") + UCsCommon::LoadFlagsToString(J) + TEXT(")");

												const FString Output = TEXT("ACsDataMapping::PerformAddEntry: [") + AssetTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("] Adding LoadFlags ") + PreviousDataLoadFlagsAsString + TEXT(" + ") + LoadFlagsAsString + TEXT(" = ") + DataLoadFlagsAsString + TEXT(".");

												if (UCsCommon::IsDefaultObject(this))
													UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

												UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
											}
										}
									}
								}

								OutOutput += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(I) + TEXT("]");
								Found = true;
								FoundCount++;
							}
						}

						// Asset has ALREADY been added
						if (Found)
						{
							if (FoundCount > 1)
								OutMessage = TEXT("Already Exists. WARNING, Duplicates. REMOVE extra entries.");
							else
								OutMessage = TEXT("Already Exists");

							if (UCsCommon::IsDefaultObject(this))
							{
								UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
								UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
							}
							return false;
						}
						// Search for Asset, and ADD it
						else
						{
							TArray<UBlueprint*> Bps;

							UCsCommon::GetAssets<UBlueprint>(ShortCode, Bps);

							// Multiple Assets with the same name.
							if (Bps.Num() > 1)
							{
								UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformAddEntry: FAILED. Multiple Assets with the same ShortCode name."));

								const int32 BpCount = Bps.Num();

								for (int32 I = 0; I < BpCount; I++)
								{
									UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformAddEntry: %s at %s"), *AssetTypeAsString, *(Bps[I]->GetPathName()));
								}

								OutOutput = TEXT("ERROR");
								OutMessage = TEXT("FAILED. Multiple Assets with the same ShortCode name. Check LOG.");

								if (UCsCommon::IsDefaultObject(this))
								{
									UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
									UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
								}
								return false;
							}
							// Single Asset
							else
							if (Bps.Num() == 1)
							{
								// Check ShortCode on Data
								if (ACsData* DOb = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<ACsData>())
								{
									// ADD
									if (ShortCode == DOb->ShortCode &&
										AssetType == DOb->Type)
									{
										Member->AddDefaulted();
										(*Member)[EntryCount].ShortCode		 = ShortCode;
										(*Member)[EntryCount].Data			 = Cast<UBlueprintCore>(Bps[0])->GeneratedClass;
										(*Member)[EntryCount].Data_LoadFlags = LoadFlags;

										CS_SET_BLUEPRINT_BITFLAG((*Member)[EntryCount].Data_LoadFlags, ECsLoadFlags::All);

										OutOutput = AssetTypeAsString + TEXT(", ") + FString::FromInt(EntryCount);
										OutMessage = TEXT("SUCCESS.");

										if (UCsCommon::IsDefaultObject(this))
										{
											UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
											UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
										}
										MarkPackageDirty();
										return true;
									}
									// Mismatch. FAILED
									else
									{
										if (ShortCode != DOb->ShortCode)
											OutOutput = TEXT("ShortCode mismatch. ") + DOb->ShortCode.ToString() + TEXT(" != ") + ShortCode.ToString();
										else
											OutOutput = TEXT("AssetType mismatch. ") + (*AssetTypeToString)(DOb->Type) + TEXT(" != ") + AssetTypeAsString;
										OutMessage = TEXT("FAILED.");

										if (UCsCommon::IsDefaultObject(this))
										{
											UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
											UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
										}
										return false;
									}
								}
								// Data NOT the correct Class type
								else
								{
									UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformAddEntry: FAILED. %s at %s is NOT of type ACsData."), *AssetTypeAsString, *(Bps[0]->GetPathName()));

									OutOutput = TEXT("Asset is NOT of type ACsData. Check LOG.");
									OutMessage = TEXT("FAILED.");

									if (UCsCommon::IsDefaultObject(this))
									{
										UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
										UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
									}
									return false;
								}
							}
							// No Asset
							else
							{
								OutOutput = TEXT("No Asset Found.");
								OutMessage = TEXT("FAILED.");

								if (UCsCommon::IsDefaultObject(this))
								{
									UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
									UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
								}
								return false;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool ACsDataMapping::PerformAddEntry(const FName &ShortCode, const int32 &LoadFlags, FString &OutMessage, FString &OutOutput)
{
	// Check for valid ShortCode
	if (ShortCode == NAME_None ||
		ShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	// Search for Asset
	TArray<UBlueprint*> Bps;

	UCsCommon::GetAssets<UBlueprint>(ShortCode, Bps);

	TSubclassOf<UObject> Data = nullptr;
	ACsData* DataDOb		  = nullptr;

	const int32 BpCount = Bps.Num();

	// Multiple Assets with the same name.
	if (BpCount > 1)
	{
		const FString Output = TEXT("ACsDataMapping::PerformAddEntry: FAILED. Multiple Assets with the same ShortCode name.");

		if (UCsCommon::IsDefaultObject(this))
			UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

		UE_LOG(LogCs, Warning, TEXT("%s"), *Output);

		for (int32 I = 0; I < BpCount; I++)
		{
			const FString AdditionalOutput = TEXT("ACsDataMapping::PerformAddEntry: ") + Bps[I]->GetPathName();

			if (UCsCommon::IsDefaultObject(this))
				UCsCommon::DisplayNotificationInfo(AdditionalOutput, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

			UE_LOG(LogCs, Warning, TEXT("%s"), *AdditionalOutput);
		}

		OutOutput = TEXT("ERROR");
		OutMessage = TEXT("FAILED. Multiple Assets with the same ShortCode name. Check LOG.");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}
	// Single Asset
	else
	if (BpCount == 1)
	{
		// Check ShortCode on Data
		DataDOb = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<ACsData>();

		if (DataDOb)
		{
			// ADD
			if (ShortCode == DataDOb->ShortCode &&
				DataDOb->Type != AssetType_MAX)
			{
				Data = Cast<UBlueprintCore>(Bps[0])->GeneratedClass;
			}
			// Mismatch. FAILED
			else
			{
				if (ShortCode != DataDOb->ShortCode)
					OutOutput = TEXT("ShortCode mismatch. ") + DataDOb->ShortCode.ToString() + TEXT(" != ") + ShortCode.ToString();
				else
					OutOutput = TEXT("Asset: ") + ShortCode.ToString() + TEXT(" has an INVALID AssetType");
				OutMessage = TEXT("FAILED.");

				if (UCsCommon::IsDefaultObject(this))
				{
					UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
					UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
				}
				return false;
			}
		}
		// Data NOT the correct Class type
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformAddEntry: FAILED. %s is NOT of type ACsData."), *(Bps[0]->GetPathName()));

			OutOutput = TEXT("Asset is NOT of type ACsData. Check LOG.");
			OutMessage = TEXT("FAILED.");

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
			}
			return false;
		}
	}
	// No Asset
	else
	{
		OutOutput = TEXT("No Asset Found.");
		OutMessage = TEXT("FAILED.");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	const TCsAssetType AssetType = DataDOb->Type;

	// Search Entries
	int32 AssetTypeIndex = INDEX_NONE;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					AssetTypeIndex++;

					if ((TCsAssetType)AssetTypeIndex != AssetType)
						continue;

					const FString AssetTypeAsString = (*AssetTypeToString)(AssetType);

					bool Found = false;
					int32 FoundCount = 0;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						// Check if Asset has ALREADY been added
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; I++)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								if (Found)
									OutOutput += TEXT(", ");
								// Check Data
								if (Entry.Data.ToString() == TEXT(""))
								{
									Entry.Data = Data;

									const FString Output = TEXT("ACsDataMapping::PerformAddEntry: Warning. No Data was set for [") + AssetTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("]. Manually setting it to ") + DataDOb->GetPathName() + TEXT(".");

									if (UCsCommon::IsDefaultObject(this))
										UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

									UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
								}
								// Check LoadFlags
								if (Entry.Data_LoadFlags != LoadFlags)
								{
									for (int32 J = 0; J < ECS_LOAD_FLAGS_EDITOR_MAX; J++)
									{
										if (CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, J))
										{
											if (!CS_TEST_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J))
											{
												const FString PreviousDataLoadFlagsAsString = TEXT("(") + UCsCommon::LoadFlagsToString(Entry.Data_LoadFlags) + TEXT(")");

												CS_SET_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J);
												
												const FString DataLoadFlagsAsString = TEXT("(") + UCsCommon::LoadFlagsToString(Entry.Data_LoadFlags) + TEXT(")");
												const FString LoadFlagsAsString     = TEXT("(") + UCsCommon::LoadFlagsToString(J) + TEXT(")");

												const FString Output = TEXT("ACsDataMapping::PerformAddEntry: [") + AssetTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("] Adding LoadFlags ") + PreviousDataLoadFlagsAsString + TEXT(" + ") + LoadFlagsAsString + TEXT(" = ") + DataLoadFlagsAsString + TEXT(".");

												if (UCsCommon::IsDefaultObject(this))
													UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

												UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
											}
										}
									}
								}
								OutOutput += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(I) + TEXT("]");
								Found = true;
								FoundCount++;
							}
						}

						// Asset has ALREADY been added
						if (Found)
						{
							if (FoundCount > 1)
								OutMessage = TEXT("Already Exists. WARNING, Duplicates. REMOVE extra entries.");
							else
								OutMessage = TEXT("Already Exists");

							if (UCsCommon::IsDefaultObject(this))
							{
								UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
								UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
							}
							return false;
						}
						else
						{
							Member->AddDefaulted();
							(*Member)[EntryCount].ShortCode		 = ShortCode;
							(*Member)[EntryCount].Data			 = Data;
							(*Member)[EntryCount].Data_LoadFlags = LoadFlags;

							CS_SET_BLUEPRINT_BITFLAG((*Member)[EntryCount].Data_LoadFlags, ECsLoadFlags::All);

							OutOutput = AssetTypeAsString + TEXT(", ") + FString::FromInt(EntryCount);
							OutMessage = TEXT("SUCCESS.");

							if (UCsCommon::IsDefaultObject(this))
							{
								UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
								UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
							}
							MarkPackageDirty();
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool ACsDataMapping::IsValid()
{
	// Check Payload is SET
	if (!Payload.Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformValidate: No Payload set."));
		return false;
	}
	// Check Payload is VALID
	ACsData_Payload* PayloadDOb = Payload->GetDefaultObject<ACsData_Payload>();

	if (!PayloadDOb->IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformValidate: Payload is NOT Valid."));
		return false;
	}
	return true;
}

bool ACsDataMapping::PerformValidate(FString &OutMessage, FString &OutOutput)
{
	bool Pass = true;

	// Check Payload is SET
	if (!Payload.Get())
	{
		OutMessage = TEXT("No Payload set.");
		OutOutput  = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformValidateOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformValidateMessage"), 5.0f);
		}

		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformValidate: No Payload set."));
		return false;
	}
	// Check Payload is VALID
	ACsData_Payload* PayloadDOb = Payload->GetDefaultObject<ACsData_Payload>();

	if (!PayloadDOb->IsValid())
	{
		OutMessage = TEXT("Payload is NOT Valid.");
		OutOutput  = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformValidateOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformValidateMessage"), 5.0f);
		}

		UE_LOG(LogCs, Warning, TEXT("ACsDataMapping::PerformValidate: Payload is NOT Valid."));
		return false;
	}

	int32 AssetTypeIndex = INDEX_NONE;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					AssetTypeIndex++;

					const TCsAssetType AssetType    = (TCsAssetType)AssetTypeIndex;
					const FString AssetTypeAsString = (*AssetTypeToString)(AssetType);

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = EntryCount - 1; I >= 0; I--)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							TArray<UBlueprint*> Bps;
							TArray<FName> PackagePaths;

							UCsCommon::GetAssets<UBlueprint>(Entry.ShortCode, Bps, PackagePaths);

							const int32 BpCount = Bps.Num();
							// ShortCode NO longer EXISTS in AssetRegistry
							if (BpCount == CS_EMPTY)
							{
								const FString Output = TEXT("ACsDataMapping::PerformValidate: Data with ShortCode: ") + Entry.ShortCode.ToString() + TEXT("is NOT found.");

								if (UCsCommon::IsDefaultObject(this))
									UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

								UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
								Pass &= false;
								continue;
							}
							// More than ONE Blueprint Asset EXISTS with the same ShortCode
							if (BpCount > 1)
							{
								const FString Output = TEXT("ACsDataMapping::PerformValidate: Multiple Data with ShortCode: ") + Entry.ShortCode.ToString();

								if (UCsCommon::IsDefaultObject(this))
									UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

								UE_LOG(LogCs, Warning, TEXT("%s"), *Output);

								for (int32 J = 0; J < BpCount; J++)
								{
									const FString AdditionalOutput = TEXT("ACsDataMapping::PerformValidate: ShortCode: ") + Entry.ShortCode.ToString() + TEXT(" at ") + PackagePaths[J].ToString();

									if (UCsCommon::IsDefaultObject(this))
										UCsCommon::DisplayNotificationInfo(AdditionalOutput, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

									UE_LOG(LogCs, Warning, TEXT("%s"), *AdditionalOutput);
								}
								Pass &= false;
								continue;
							}
							// Asset is NOT of type ACsData
							ACsData* DataDOb = Cast<UBlueprintCore>(Bps[CS_FIRST])->GeneratedClass->GetDefaultObject<ACsData>();

							if (!DataDOb)
							{
								const FString Output = TEXT("ACsDataMapping::PerformValidate: Data with ShortCode: ") + Entry.ShortCode.ToString() + TEXT(" is NOT of type ACsData.");

								if (UCsCommon::IsDefaultObject(this))
									UCsCommon::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

								UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
								Pass &= false;
								continue;
							}
						}
					}
				}
			}
		}
	}

	if (Pass)
	{
		OutMessage = TEXT("DataMapping is Valid.");
		OutOutput  = TEXT("SUCCESS");
	}
	else
	{
		OutMessage = TEXT("DataMapping is NOT Valid.");
		OutOutput = TEXT("ERROR");
	}
	return Pass;
}

void ACsDataMapping::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Find Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataMappingFindEntry, Find))
	{
		if (!FindEntry.Find)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		FindEntry.Message = TEXT("");
		FindEntry.Output  = TEXT("");

		// Check for valid ShortCode
		if (FindEntry.ShortCode == NAME_None ||
			FindEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			FindEntry.Message = TEXT("INVALID ShortCode.");
			FindEntry.Output  = TEXT("ERROR");
			FindEntry.Find	  = false;

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(FindEntry.Output, TEXT("DataMapping"), TEXT("FindEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(FindEntry.Message, TEXT("DataMapping"), TEXT("FindEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}

		// Search Entries
		TArray<FCsDataMappingEntry*> OutEntries; 
		TArray<TCsAssetType> OutAssetTypes;
		TArray<int32> OutIndices;

		PerformFindEntry(FindEntry.ShortCode, OutEntries, OutAssetTypes, OutIndices);

		const int32 EntryCount = OutEntries.Num();

		for (int32 I = 0; I < EntryCount; I++)
		{
			if (I > 0)
				FindEntry.Output += TEXT(", ");

			const FString AssetTypeAsString = (*AssetTypeToString)(OutAssetTypes[I]);
			FindEntry.Output			   += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");
		}

		if (EntryCount == CS_EMPTY)
			FindEntry.Output = TEXT("No Results.");
		FindEntry.Message = TEXT("SUCCESS");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(FindEntry.Output, TEXT("DataMapping"), TEXT("FindEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(FindEntry.Message, TEXT("DataMapping"), TEXT("FindEntryMessage"), 5.0f);
		}
		FindEntry.Find= false;
	}
	// Add Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataMappingAddEntry, Add))
	{
		if (!AddEntry.Add)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		AddEntry.Message = TEXT("");
		AddEntry.Output  = TEXT("");

		PerformAddEntry(AddEntry.ShortCode, (*StringToAssetType)(AddEntry.AssetType), AddEntry.LoadFlags, AddEntry.Message, AddEntry.Output);
		AddEntry.Add = false;
	}
	// Remove Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataMappingRemoveEntry, Remove))
	{
		if (!RemoveEntry.Remove)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		RemoveEntry.Message = TEXT("");
		RemoveEntry.Output = TEXT("");

		// Check for valid ShortCode
		if (RemoveEntry.ShortCode == NAME_None ||
			RemoveEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			RemoveEntry.Message = TEXT("INVALID ShortCode.");
			RemoveEntry.Output = TEXT("ERROR");
			RemoveEntry.Remove = false;

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(RemoveEntry.Output, TEXT("DataMapping"), TEXT("RemoveEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(RemoveEntry.Message, TEXT("DataMapping"), TEXT("RemoveEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}

		// Search Entries
		bool Found = false;

		int32 AssetTypeIndex = INDEX_NONE;

		UClass* Class = GetClass();

		for (TFieldIterator<UProperty> It(Class); It; ++It)
		{
			UProperty* Property = Cast<UProperty>(*It);

			const FString MemberName = Property->GetName();

			// Array
			if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
			{
				// Struct
				if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
				{
					// FCsDataMappingEntry
					if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
					{
						AssetTypeIndex++;

						const TCsAssetType AssetType    = (TCsAssetType)AssetTypeIndex;
						const FString AssetTypeAsString = (*AssetTypeToString)(AssetType);

						if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
						{
							const int32 EntryCount = Member->Num();

							for (int32 I = EntryCount - 1; I >= 0; I--)
							{
								FCsDataMappingEntry& Entry = (*Member)[I];

								if (RemoveEntry.ShortCode == Entry.ShortCode)
								{
									if (Found)
										RemoveEntry.Output += TEXT(", ");

									RemoveEntry.Output += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(I) + TEXT("]");
									Found = true;

									Member->RemoveAt(I);
								}
							}
						}
					}
				}
			}
		}

		if (RemoveEntry.Output == TEXT(""))
			RemoveEntry.Output = TEXT("Nothing Removed.");
		RemoveEntry.Message = TEXT("SUCCESS");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(RemoveEntry.Output, TEXT("DataMapping"), TEXT("RemoveEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(RemoveEntry.Message, TEXT("DataMapping"), TEXT("RemoveEntryMessage"), 5.0f);
		}
		RemoveEntry.Remove = false;
	}
	// Validate
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataMappingValidate, Validate))
	{
		if (!Validate.Validate)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		Validate.Message = TEXT("");
		Validate.Output  = TEXT("");

		PerformValidate(Validate.Output, Validate.Message);

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(Validate.Output, TEXT("DataMapping"), TEXT("ValidateOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(Validate.Message, TEXT("DataMapping"), TEXT("ValidateMessage"), 5.0f);
		}
		Validate.Validate = false;
	}
	Super::PostEditChangeProperty(e);
}

bool ACsDataMapping::CheckEntryExists(const FName &ShortCode, const TCsAssetType &AssetType, const TCsLoadFlags_Editor &LoadFlags, FString &OutMessage)
{
	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{
					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; I++)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								bool Found = true;
								// Check AssetType
								if (AssetType != (*StringToAssetType)(MemberName))
								{
									OutMessage += TEXT("AssetType mismatch: ") + (*AssetTypeToString)(AssetType) + TEXT(" != ") + MemberName + TEXT(".");
									Found = false;
								}
								// Check LoadFlags
								const ECsLoadFlags Flags = ECsLoadFlags_Editor::ToBaseType(LoadFlags);

								if (!CS_TEST_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, Flags))
								{
									OutMessage += TEXT(" LoadFlags: [") + UCsCommon::LoadFlagsToString(Entry.Data_LoadFlags) + TEXT("] does NOT include ") + ECsLoadFlags_Editor::ToString(LoadFlags) + TEXT(".");
									Found = false;
								}
								// Check Data
								if (Entry.Data->StaticClass() == nullptr)
								{
									OutMessage += TEXT(" Data is NULL.");
									Found = false;
								}
								return Found;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

#endif // #if WITH_EDITOR

#pragma endregion 99 Editor