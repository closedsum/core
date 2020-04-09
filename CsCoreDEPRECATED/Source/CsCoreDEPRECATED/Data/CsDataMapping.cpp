// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDataMapping.h"
#include "CsCoreDEPRECATED.h"

// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Common_DEPRECATED.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Asset.h"
#include "Library/Load/CsLibrary_Load_DEPRECATED.h"
// Interface
#include "Data/CsData.h"

// Cache
#pragma region

namespace NCsDataMappingCached
{
	namespace Str
	{
		CSCOREDEPRECATED_API const FString LoadData = TEXT("UCsDataMapping::LoadData");
	}
}

#pragma endregion Cache

UCsDataMapping::UCsDataMapping(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsDataMapping::ClearLoaded()
{
}

// Mapping
#pragma region

TArray<FCsDataMappingEntry>* UCsDataMapping::GetDataMappings(const FECsDataType& DataType)
{
	TArray<FCsDataMappingEntry>** MappingPtr = Datas_Entry.Find(DataType);
	return MappingPtr ? *MappingPtr : nullptr;
}

TMap<FName, FCsDataMappingEntry>* UCsDataMapping::GetDataMappings_Map(const FECsDataType& DataType)
{
	TMap<FName, FCsDataMappingEntry>** MapPtr = Datas_Entry_Map.Find(DataType);
	return MapPtr ? *MapPtr : nullptr;
}

FCsDataMappingEntry* UCsDataMapping::GetDataMappingEntry(const FECsDataType& DataType, const FName& ShortCode)
{
	if (TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType))
	{
		if (FCsDataMappingEntry* Entry = Map->Find(ShortCode))
			return Entry;

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GetDataMappingEntry: No Entry found for DataType: %s with ShortCode: %s"), *(DataType.Name), *ShortCode.ToString());
	}
	return nullptr;
}

void UCsDataMapping::AssignDataMappingReferences()
{
}

void UCsDataMapping::GenerateMaps()
{
	// Assign References
	AssignDataMappingReferences();

	Datas_Loaded.Reset();
	Datas_Loaded_Map.Reset();
	Datas_ShortCodeToLookUpCode_Map.Reset();
	Datas_LookUpCodeToShortCode_Map.Reset();

	// Populate Map members
	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		TArray<FCsDataMappingEntry>* MappingPtr = GetDataMappings(DataType);

		if (!MappingPtr)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GenerateMaps: Warning. No DataMapping found for DataType: %s"), *(DataType.Name));
			return;
		}

		TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType);

		if (!Map)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GenerateMaps: Warning. No DataMapping_Map found for DataType: %s"), *(DataType.Name));
			return;
		}

		Datas_Loaded.Add(DataType);
		Datas_Loaded_Map.Add(DataType);
		Datas_ShortCodeToLookUpCode_Map.Add(DataType);
		Datas_LookUpCodeToShortCode_Map.Add(DataType);

		Map->Reset();

		TArray<FCsDataMappingEntry>& Mapping = *MappingPtr;

		uint16 I = 0;

		for (FCsDataMappingEntry& Entry : Mapping)
		{
			const FName& ShortCode = Entry.ShortCode;

			Map->Add(ShortCode, Entry);
			Datas_Loaded[DataType].AddDefaulted();
			Datas_Loaded_Map[DataType].Add(ShortCode);
			Datas_ShortCodeToLookUpCode_Map[DataType].Add(ShortCode, I);
			Datas_LookUpCodeToShortCode_Map[DataType].Add(I, ShortCode);
			++I;
		}
	
		//Map->KeySort(TLess<FName>());
		//Datas_ShortCodeToLookUpCode_Map[DataType].KeySort(TLess<FName>());
		//Datas_LookUpCodeToShortCode_Map[DataType].KeySort(TLess<uint16>());
	}
}

#pragma endregion Mapping

const FECsDataType& UCsDataMapping::GetDataType(const FName& ShortCode)
{
	// Search TMaps - Populated if GenerateMaps was called
	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType);

		if (!Map)
			continue;

		if (FCsDataMappingEntry* Entry = Map->Find(ShortCode))
		{
			if (Entry->Data)
			{
				return DataType;
			}
			else
			{
				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GetDataType: No Data set for DataType: %s with ShortCode: %s"), *(DataType.Name), *ShortCode.ToString());
			}
		}
	}
	// Search TArrays
	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		TArray<FCsDataMappingEntry>* MappingPtr = GetDataMappings(DataType);

		if (!MappingPtr)
			continue;

		TArray<FCsDataMappingEntry>& Mapping = *MappingPtr;

		for (FCsDataMappingEntry& Entry : Mapping)
		{
			if (Entry.ShortCode == ShortCode)
				return DataType;
		}
	}
	return EMCsDataType::Get().GetMAX();
}

UCsData_Payload* UCsDataMapping::GetPayload()
{
	return Payload->GetDefaultObject<UCsData_Payload>();
}

// Asset References
#pragma region

void UCsDataMapping::PreSave(const class ITargetPlatform* TargetPlatform)
{
#if WITH_EDITOR
	// Set LookUpCodes
	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(DataType);

		const uint16 Count = Mapping->Num();

		for (uint16 J = 0; J < Count; ++J)
		{
			(*Mapping)[J].LookUpCode = J;
		}
	}
#endif // #if WITH_EDITOR
	Super::PreSave(TargetPlatform);
#if WITH_EDITOR
	PopulateAssetReferences();
	//UCsLibrary_Load_DEPRECATED::GetCategoryMemberAssociations(this, GetClass(), CategoryMemberAssociations);
	SaveToJson();
#endif // #if WITH_EDITOR
}

bool UCsDataMapping::DoesDataAssetReferenceExist(const FECsDataType& DataType, const FName& ShortCode)
{
	// Search TMaps - Populated if GenerateMaps was called
	if (TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType))
	{
		if (FCsDataMappingEntry* Entry = Map->Find(ShortCode))
		{
			if (Entry->Data)
			{
				return true;
			}
			else
			{
				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::DoesDataAssetReferenceExist: No Data set for DataType: %s with ShortCode: %s"), *(DataType.Name), *ShortCode.ToString());
			}
		}
	}
	// Search TArrays
	if (TArray<FCsDataMappingEntry>* MappingPtr = GetDataMappings(DataType))
	{
		TArray<FCsDataMappingEntry>& Mapping = *MappingPtr;

		for (FCsDataMappingEntry& Entry : Mapping)
		{
			if (Entry.ShortCode == ShortCode)
			{
				if (Entry.Data)
				{
					return true;
				}
				else
				{
					UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::DoesDataAssetReferenceExist: No Data set for DataType: %s with ShortCode: %s"), *(DataType.Name), *ShortCode.ToString());
				}
			}
		}
	}
	return false;
}

bool UCsDataMapping::DoesDataAssetReferenceExist(const FName& ShortCode)
{
	bool Exist = false;

	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		Exist |= DoesDataAssetReferenceExist(DataType, ShortCode);
	}
	return Exist;
}

bool UCsDataMapping::AddDataAssetReference(const FECsDataType& DataType, const FName& ShortCode, ICsData* InData)
{
	if (DataType == EMCsDataType::Get().GetMAX())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::AddDataAssetReference: Warning. Using INVALID DataType: ECsDataType_MAX when adding ShortCode: %s"), *ShortCode.ToString());
		return false;
	}

	if (TArray<FCsDataMappingEntry>* Mappings = GetDataMappings(DataType))
	{
		if (!DoesDataAssetReferenceExist(DataType, ShortCode))
		{
			// Add to DataMappings
			FCsDataMappingEntry Mapping;
			Mapping.ShortCode = ShortCode;
			Mapping.Data	  = InData->_getUObject();
			Mappings->Add(Mapping);
			// Add to TMap DataMappings
			TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType);

			if (!Map)
			{
				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::AddDataAssetReference: Warning. No DataMapping_Map found for DataType: %s"), *(DataType.Name));
				return true;
			}
			Map->Add(ShortCode, Mapping);
			//Map->KeySort(TLess<FName>());
			return true;
		}
		else
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::AddDataAssetReference: Warning. Mapping DataType: %s and ShortCode: %s have ALREADY been ADDED."), *(DataType.Name), *ShortCode.ToString());
			return false;
		}
	}
	UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::AddDataAssetReference: Warning. Using DataType: %s does NOT exist."), *(DataType.Name));
	return false;
}

FStringAssetReference UCsDataMapping::GetStringAssetReference(const FECsDataType& DataType, const FName& ShortCode)
{
	TMap<FName, FCsDataMappingEntry>* Mapping = GetDataMappings_Map(DataType);
	FCsDataMappingEntry* Entry				  = Mapping->Find(ShortCode);
	return Entry ? Entry->Data.ToSoftObjectPath() : FStringAssetReference();
}

FStringAssetReference UCsDataMapping::GetStringAssetReference(const FECsDataType& DataType, const uint16& LookUpCode)
{
	TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(DataType);

	if (Mapping->Num() <= LookUpCode)
		return FStringAssetReference();
	return (*Mapping)[LookUpCode].Data.ToSoftObjectPath();
}

void UCsDataMapping::GetStringAssetReferences(const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags, TArray<FStringAssetReference>& OutReferences)
{
	TMap<FName, FCsDataMappingEntry>* Mapping = GetDataMappings_Map(DataType);
	FCsDataMappingEntry* Entry				  = Mapping->Find(ShortCode);

	if (!Entry)
		return;
	Entry->AssetReferences[(int32)LoadFlags].Get(OutReferences);
}

void UCsDataMapping::GetStringAssetReferences(const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags, TArray<FStringAssetReference>& OutReferences)
{
	TArray<FCsDataMappingEntry>* Mapping = GetDataMappings(DataType);

	if (Mapping->Num() <= LookUpCode)
		return;
	(*Mapping)[LookUpCode].AssetReferences[(int32)LoadFlags].Get(OutReferences);
}

void UCsDataMapping::PopulateDataAssetReferences()
{
	int32 DataTypeIndex = INDEX_NONE;

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
					++DataTypeIndex;

					const FECsDataType& DataType = EMCsDataType::Get().GetEnumAt(DataTypeIndex);

					if (TArray<FCsDataMappingEntry>* MemberPtr = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						TArray<FCsDataMappingEntry>& Member = *MemberPtr;

						for (FCsDataMappingEntry& Entry : Member)
						{
							const FStringAssetReference AssetRef = Entry.Data.ToSoftObjectPath();
							const FString Asset					 = AssetRef.ToString();

							if (Asset == TEXT(""))
							{
								UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PopulateAssetReferences: No data set for DataType: %s using Short Code: %s"), *(DataType.Name), *(Entry.ShortCode.ToString()));
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

void UCsDataMapping::PopulateAssetReferences()
{
	const uint8 FlagCount = (uint8)ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX;

	for (int32 I = 0; I < FlagCount; ++I)
	{
		AssetReferences[I].Reset();
	}

	int32 DataTypeIndex = INDEX_NONE;

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
					++DataTypeIndex;

					const FECsDataType& DataType = EMCsDataType::Get().GetEnumAt(DataTypeIndex);

					if (TArray<FCsDataMappingEntry>* MemberPtr = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						TArray<FCsDataMappingEntry>& Member = *MemberPtr;

						for (FCsDataMappingEntry& Entry : Member)
						{
							UObject* OutAsset = nullptr;

							//UCsLibrary_Load_DEPRECATED::LoadTSoftClassPtr<UObject>((*Member)[I].Data, OutAsset, TEXT("Object"));

							if (!OutAsset)
							{
								UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PopulateAssetReferences: No data set for DataType: %s using Short Code: %s"), *(DataType.Name), *(Entry.ShortCode.ToString()));
								continue;
							}

							const FStringAssetReference AssetRef = Entry.Data.ToSoftObjectPath();
							const FString Asset					 = AssetRef.ToString();

							const int32 LoadFlags = Entry.Data_LoadFlags;

							for (int32 J = 0; J < FlagCount; ++J)
							{
								Entry.AssetReferences[J].References.Reset();

								if (J != (uint8)ECsLoadFlags::Game &&
									!CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, (ECsLoadFlags)J))
								{
									continue;
								}

								// Reference to "Root" Data
								Entry.AssetReferences[J].References.AddDefaulted();

								const int32 Size = Entry.AssetReferences[J].References.Num();

								FCsStringAssetReference& Reference = Entry.AssetReferences[J].References[Size - 1];
								Reference.Reference				   = Asset;
								Reference.Reference_Internal	   = AssetRef;
								Reference.Size.Bytes			   = OutAsset->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
								Reference.Size.Kilobytes		   = UCsLibrary_Math::BytesToKilobytes(Reference.Size.Bytes);
								Reference.Size.Megabytes		   = UCsLibrary_Math::BytesToMegabytes(Reference.Size.Bytes);

								AssetReferences[J].References.Add(Reference);

								// References to anything Data references
								/*
								int32 ReferenceCount = OutAsset->AssetReferences[J].References.Num();
								
								for (int32 K = 0; K < ReferenceCount; ++K)
								{
									Entry.AssetReferences[J].References.Add(OutAsset->AssetReferences[J].References[K]);
									AssetReferences[J].References.Add(OutAsset->AssetReferences[J].References[K]);
								}

								(*Member)[I].AssetReferences[J].CalculateSize();
								*/
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

	for (int32 I = 0; I < FlagCount; ++I)
	{
		AssetReferences[I].CalculateSize();
	}
}

#pragma endregion Asset References

// Load
#pragma region

ECsLoadFlags UCsDataMapping::GetLoadAssetsFlags(const FECsDataCollectionType& CollectionType)
{
	return ECsLoadFlags::Game;
}

void UCsDataMapping::GetDataCollectionShortCodes(const FECsDataCollectionType& CollectionType, TArray<FName>& OutShortCodes)
{
}

const FECsDataType& UCsDataMapping::GetDataTypeFromShortCode(const FName &ShortCode) { return EMCsDataType::Get().GetMAX(); }

void UCsDataMapping::GetLoadStringAssetReferences(const FECsDataCollectionType& CollectionType, TArray<FStringAssetReference>& OutAssetReferences)
{
}

/*
void UCsDataMapping::AsyncLoadObjects(UWorld* World, const FECsDataCollectionType& CollectionType, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjectPaths& Delegate)
{
	TArray<FStringAssetReference> References;

	GetLoadStringAssetReferences(CollectionType, References);

	if (References.Num() == CS_EMPTY)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::AsyncLoadObjects: Trying to load 0 assets."));

		TArray<UObject*> LoadedObjects;
		Delegate.Execute(LoadedObjects, 0.0f);
		return;
	}
	UCsManager_Load::Get()->LoadObjectPaths(World, References, AsyncOrder, Delegate);
}
*/

void UCsDataMapping::OnFinishedAsyncLoadingAssetsSetReferences(const FECsDataCollectionType& CollectionType, const TArray<UObject*>& LoadedAssets)
{
}

	// ShortCode
#pragma region

const FCsData& UCsDataMapping::LoadData(const FString& FunctionName, const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	if (ShortCode == CS_INVALID_SHORT_CODE)
		return FCsData::Empty;

	// Search Loaded Data TMaps / TArray
	const FCsData& IData = GetLoadedData(DataType, ShortCode);

	if (IData.IsValid())
		return IData;

	// Search TMaps - Populated if GenerateMaps was called
	if (TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType))
	{
		if (FCsDataMappingEntry* Entry = Map->Find(ShortCode))
		{
			const FCsData& Data = LoadData_Internal(DataType, *Entry, LoadFlags);

			if (Data.IsValid())
				return Data;
		}
	}

	// Search TArrays
	if (TArray<FCsDataMappingEntry>* MappingPtr = GetDataMappings(DataType))
	{
		TArray<FCsDataMappingEntry>& Mapping = *MappingPtr;

		for (FCsDataMappingEntry& Entry : Mapping)
		{
			if (Entry.ShortCode == ShortCode)
			{
				const FCsData& Data = LoadData_Internal(DataType, Entry, LoadFlags);

				if (Data.IsValid())
					return Data;
			}
		}
	}
	UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::LoadData: Could NOT find Data with ShortCode: %s"), *ShortCode.ToString());
	return FCsData::Empty;
}

const FCsData& UCsDataMapping::LoadData(const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	return LoadData(NCsDataMappingCached::Str::LoadData, DataType, ShortCode, LoadFlags);
}

const FCsData& UCsDataMapping::LoadData(const FName& ShortCode, const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::Game*/)
{
	if (ShortCode == NAME_None)
		return FCsData::Empty;

	// Search Loaded Data TMaps / TArray
	const FCsData& IData = GetLoadedData(ShortCode);

	if (IData.IsValid())
		return IData;

	// Search TMaps - Populated if GenerateMaps was called
	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		TMap<FName, FCsDataMappingEntry>* Map = GetDataMappings_Map(DataType);

		if (!Map)
			continue;

		FCsDataMappingEntry* Entry = Map->Find(ShortCode);

		if (!Entry)
			continue;

		const FCsData& Data = LoadData_Internal(DataType, *Entry, LoadFlags);

		if (Data.IsValid())
			return Data;
	}

	// Search TArrays
	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		TArray<FCsDataMappingEntry>* MappingPtr = GetDataMappings(DataType);

		if (!MappingPtr)
			continue;

		TArray<FCsDataMappingEntry>& Mapping = *MappingPtr;

		for (FCsDataMappingEntry& Entry : Mapping)
		{
			if (Entry.ShortCode == ShortCode)
			{
				const FCsData& Data = LoadData_Internal(DataType, Entry, LoadFlags);

				if (Data.IsValid())
					return Data;
			}
		}
	}
	UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::LoadData: Could NOT find Data with ShortCode: %s"), *ShortCode.ToString());
	return FCsData::Empty;
}

#pragma endregion ShortCode

	// LookUpCode
#pragma region

const FCsData& UCsDataMapping::LoadData(const FString& FunctionName, const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	if (LookUpCode == CS_INVALID_LOOK_UP_CODE)
		return FCsData::Empty;

	// Search Loaded Data TMaps / TArray
	{
		const FCsData& Data = GetLoadedData(DataType, LookUpCode);

		if (Data.IsValid())
			return Data;
	}

	TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(DataType);
	const int32 Count					 = Mapping.Num();

	if (LookUpCode > Count)
	{
		UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load DataType: %s. LookUpCode: %d does NOT exist."), *FunctionName, *(DataType.Name), LookUpCode);
		return FCsData::Empty;
	}

	// Load the Data
	{
		const FCsData& Data = LoadData_Internal(FunctionName, DataType, Mapping[LookUpCode]);

		if (Data.IsValid())
			return Data;
	}
	UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load DataType: %s. LookUpCode: %d does NOT exist."), *FunctionName, *(DataType.Name), LookUpCode);
	return FCsData::Empty;
}

const FCsData& UCsDataMapping::LoadData(const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	return LoadData(NCsDataMappingCached::Str::LoadData, DataType, LookUpCode, LoadFlags);
}

#pragma endregion LookUpCode

const FCsData& UCsDataMapping::LoadData_Internal(const FString& FunctionName, const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	// Load the Data
	UObject* Object = nullptr;
	ICsData* Data = nullptr;

	UCsLibrary_Load_DEPRECATED::LoadTSoftClassPtr(Mapping.Data, Object);

	Data = Cast<ICsData>(Object);

	if (!Data)
	{
		const FString ShortCode		   = Mapping.ShortCode.ToString();
		const FString AssetDescription = UCsLibrary_Load_DEPRECATED::GetAssetDescription(Mapping.Data);

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: Failed to load data using Short Code: %s with Path Location: %s."), *FunctionName, *ShortCode, *AssetDescription);
		return FCsData::Empty;
	}

	const FCsData& IData = AddLoadedData(DataType, Mapping.ShortCode, Data);
	Data->Load(LoadFlags);

	FString Name = Data->GetShortCode().ToString();
	checkf(Data->IsValid(), TEXT("%s: Data: %s is NOT Valid."), *FunctionName, *Name);
	return IData;
}

const FCsData& UCsDataMapping::LoadData_Internal(const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	return LoadData_Internal(NCsDataMappingCached::Str::LoadData, DataType, Mapping, LoadFlags);
}

void UCsDataMapping::LoadAllData(const FString& FunctionName, const FECsDataType& DataType, const ECsLoadFlags& LoadFlags /*= ECsLoadFlags::Game*/)
{
	TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(DataType);

	for (FCsDataMappingEntry& Entry : Mapping)
	{
		LoadData(FunctionName, DataType, Entry.ShortCode, LoadFlags);
	}
}

	// Add
#pragma region

const FCsData& UCsDataMapping::AddLoadedData(const FECsDataType& DataType, const FName& ShortCode, ICsData* InData)
{
	// Map
	{
		FCsData& Data = Datas_Loaded_Map[DataType].FindOrAdd(ShortCode);
		Data.SetInterface(InData);
		Data.SetObject(InData->_getUObject());
	}

	const int32& LookUpCode = Datas_ShortCodeToLookUpCode_Map[DataType][ShortCode];

	// Array
	{
		FCsData& Data = Datas_Loaded[DataType][LookUpCode];
		Data.SetInterface(InData);
		Data.SetObject(InData->_getUObject());

		return Data;
	}
}

const FCsData& UCsDataMapping::AddLoadedData(const FECsDataType& DataType, const uint16& LookUpCode, ICsData* InData)
{
	// Array
	{
		FCsData& Data = Datas_Loaded[DataType][LookUpCode];
		Data.SetInterface(InData);
		Data.SetObject(InData->_getUObject());
	}

	const FName& ShortCode = Datas_LookUpCodeToShortCode_Map[DataType][LookUpCode];

	// Map
	{
		FCsData& Data = Datas_Loaded_Map[DataType].FindOrAdd(ShortCode);
		Data.SetInterface(InData);
		Data.SetObject(InData->_getUObject());

		return Data;
	}
}

#pragma endregion Add

	// Get
#pragma region

const FCsData& UCsDataMapping::GetLoadedData(const FECsDataType& DataType, const FName& ShortCode)
{
	if (TMap<FName, FCsData>* Map = Datas_Loaded_Map.Find(DataType))
	{
		if (FCsData* Data = Map->Find(ShortCode))
			return *Data;
	}
	return FCsData::Empty;
}

const FCsData& UCsDataMapping::GetLoadedData(const FName& ShortCode, FECsDataType& OutDataType)
{
	if (ShortCode == CS_INVALID_SHORT_CODE)
		return FCsData::Empty;

	OutDataType = EMCsDataType::Get().GetMAX();

	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		if (TMap<FName, FCsData>* Map = Datas_Loaded_Map.Find(DataType))
		{
			if (FCsData* Data = Map->Find(ShortCode))
			{
				OutDataType = DataType;
				return *Data;
			}
		}
	}
	return FCsData::Empty;
}

const FCsData& UCsDataMapping::GetLoadedData(const FName& ShortCode)
{
	if (ShortCode == CS_INVALID_SHORT_CODE)
		return FCsData::Empty;

	for (const FECsDataType& DataType : EMCsDataType::Get())
	{
		if (TMap<FName, FCsData>* Map = Datas_Loaded_Map.Find(DataType))
		{
			if (FCsData* Data = Map->Find(ShortCode))
			{
				return *Data;
			}
		}
	}
	return FCsData::Empty;
}

const FCsData& UCsDataMapping::GetLoadedData(const FECsDataType& DataType, const uint16& LookUpCode)
{
	if (TArray<FCsData>* Datas = Datas_Loaded.Find(DataType))
	{
		if (LookUpCode < Datas->Num())
			return (*Datas)[LookUpCode];
	}
	return FCsData::Empty;
}

void UCsDataMapping::GetLoadedDatas(const FECsDataType& DataType, TArray<FCsData>& OutDatas)
{
	if (TMap<FName, FCsData>* MapPtr = Datas_Loaded_Map.Find(DataType))
	{
		TMap<FName, FCsData>& Map = *MapPtr;

		for (TPair<FName, FCsData>& Pair : Map)
		{
			OutDatas.Add(Pair.Value);
		}
	}
}

void UCsDataMapping::GetLoadedDataShortCodes(const FECsDataType& DataType, TArray<FName>& OutShortCodes)
{
	if (TMap<FName, FCsData>* MapPtr = Datas_Loaded_Map.Find(DataType))
	{
		TMap<FName, FCsData>& Map = *MapPtr;

		for (TPair<FName, FCsData>& Pair : Map)
		{
			OutShortCodes.Add(Pair.Key);
		}
	}
}

#pragma endregion Get

#pragma endregion Load

// IsValid
#pragma region

bool UCsDataMapping::CheckDataIsValid(const FString& FunctionName, const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::Game*/)
{
	/*
	if (ShortCode == NAME_None)
		return true;

	bool Pass = true;

	TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(DataType);

	for (FCsDataMappingEntry& Entry : Mapping)
	{
		if (ShortCode != Entry.ShortCode)
			continue;

		// Load the Data
		if (ICsData* Data = LoadData(FunctionName, DataType, Entry))
		{
			Data->Load(LoadFlags);
			Pass &= Data->IsValid();
			return Pass;
		}
	}
	*/
	return true;
}

bool UCsDataMapping::CheckDataIsValid(const FString& FunctionName, const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::Game*/)
{
	// Load the Data
	UObject* Object = nullptr;

	UCsLibrary_Load_DEPRECATED::LoadTSoftClassPtr(Mapping.Data, Object);

	ICsData* Data = Cast<ICsData>(Object);

	if (!Data)
	{
		const FString ShortCode		   = Mapping.ShortCode.ToString();
		const FString AssetDescription = UCsLibrary_Load_DEPRECATED::GetAssetDescription(Mapping.Data);

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: Failed to load data using Short Code: %s with Path Location: %s"), *FunctionName, *ShortCode, *AssetDescription);
		return true;
	}

	Data->Load(LoadFlags);
	return Data->IsValid();
}

bool UCsDataMapping::CheckAllDataIsValid(const FString& FunctionName, const FECsDataType& DataType, const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::Game*/)
{
	TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(DataType);

	bool Pass = true;

	for (FCsDataMappingEntry& Entry : Mapping)
	{
		Pass &= CheckDataIsValid(FunctionName, DataType, Entry, LoadFlags);
	}
	return Pass;
}

#pragma endregion IsValid

// Get
#pragma region

FName UCsDataMapping::GetShortCode(const FECsDataType& DataType, const uint16& LookUpCode)
{
	if (LookUpCode == CS_INVALID_LOOK_UP_CODE)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GetShortCode: Failed find ShortCode using INVALID LookUpCode."));
		return CS_INVALID_SHORT_CODE;
	}

	TArray<FCsDataMappingEntry>* Mapping= GetDataMappings(DataType);

	const int32 Count = Mapping->Num();

	if (LookUpCode >= Count)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GetShortCode: LookUpCode: %d is Out of Bounds (%d)."), LookUpCode, Count);
		return CS_INVALID_SHORT_CODE;
	}
	return (*Mapping)[LookUpCode].ShortCode;
}

uint16 UCsDataMapping::GetLookUpCode(const FECsDataType& DataType, const FName& ShortCode)
{
	if (ShortCode == CS_INVALID_SHORT_CODE)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GetLookUpCode: Failed to find LookUpCode using INVALID ShortCode."));
		return CS_INVALID_LOOK_UP_CODE;
	}

	TMap<FName, FCsDataMappingEntry>* Mapping = GetDataMappings_Map(DataType);
	FCsDataMappingEntry* Entry				  = Mapping->Find(ShortCode);

	if (!Entry)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::GetLookUpCode: Failed to find LookUpCode using ShortCode: %s."), *ShortCode.ToString());
		return CS_INVALID_LOOK_UP_CODE;
	}
	return Entry->LookUpCode;
}

#pragma endregion Get

// Json
#pragma region

void UCsDataMapping::PostLoad()
{
	Super::PostLoad();
	LoadFromJson();
	PopulateDataAssetReferences();
}

FString UCsDataMapping::GetAbsolutePath()
{
	const FString AssetName	   = TEXT("bp_data_mapping.");
	const FString InternalName = GetName();
	FString PathName		   = GetPathName();

	PathName = PathName.Replace(*InternalName, TEXT(""));
	PathName = PathName.Replace(*AssetName, TEXT(""));
	PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

	const FString ProjectContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	const FString JsonDir		    = TEXT("Json/");
	return ProjectContentDir + JsonDir + PathName;
}

void UCsDataMapping::SaveToJson()
{
	/*
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	UCsLibrary_Load_DEPRECATED::WriteObjectToJson(JsonWriter, (void*)this, GetClass(), CategoryMemberAssociations, WriteObjectToJson_Internal);

	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Filename = GetAbsolutePath() + TEXT("bp_data_mapping") + TEXT(".json");

	FFileHelper::SaveStringToFile(OutputString, *Filename);

#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()) || UCsLibrary_Common::IsPlayInGame(GetWorld()))
		return;

	FText ErrorMessage;

	SourceControlHelpers::CheckoutOrMarkForAdd(Filename, FText::FromString(Filename), NULL, ErrorMessage);
#endif // #if WITH_EDITOR
*/
}

void UCsDataMapping::LoadFromJson()
{
	/*
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
				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::LoadFromJson (%s): Data needs to be saved at least ONCE to generate CategoryMemberAssociations"), *AssetName);
				return;
			}
			UCsLibrary_Load_DEPRECATED::ReadObjectFromJson(JsonParsed, this, GetClass(), CategoryMemberAssociations, ReadObjectFromJson_Internal);
		}
		else
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::LoadFromJson (%s): %s is NOT Valid"), *AssetName, *Filename);
			return;
		}
	}
	else
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::LoadFromJson (%s): %s NOT found"), *AssetName, *Filename);
		return;
	}

	if (UCsLibrary_Common::IsPlayInPIE(GetWorld()) || UCsLibrary_Common::IsPlayInGame(GetWorld()))
		bHasLoadedFromJson = true;
		*/
}

#pragma endregion Json

// Editor
#pragma region

#if WITH_EDITOR

bool UCsDataMapping::PerformFindEntry(const FName& ShortCode, TArray<FCsDataMappingEntry*>& OutEntries, TArray<FECsDataType>& OutDataTypes, TArray<int32>& OutIndices)
{
	int32 DataTypeIndex = INDEX_NONE;

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
					DataTypeIndex++;

					const FECsDataType& DataType   = EMCsDataType::Get().GetEnumAt(DataTypeIndex);
					const FString& DataTypeAsString = DataType.Name;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; ++I)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								OutEntries.Add(&Entry);
								OutDataTypes.Add(DataType);
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

bool UCsDataMapping::PerformAddEntry(const FName& ShortCode, const FECsDataType& DataType, const int32& LoadFlags, FString& OutMessage, FString& OutOutput)
{
	// Check for valid ShortCode
	if (ShortCode == NAME_None ||
		ShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	// Check if DataType Exists
	if (!EMCsDataType::Get().IsValidEnum(DataType))
	{
		OutMessage = TEXT("INVALID DataType.");
		OutOutput = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	// Search Entries

	int32 DataTypeIndex = INDEX_NONE;

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
					DataTypeIndex++;

					if (EMCsDataType::Get().GetEnumAt(DataTypeIndex) != DataType)
						continue;

					const FString& DataTypeAsString = DataType.Name;

					bool Found = false;
					int32 FoundCount = 0;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						// Check if Asset has ALREADY been added
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; ++I)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								if (Found)
									OutOutput += TEXT(", ");
								// Check Data exists
								if (Entry.Data.ToString() == TEXT(""))
								{
									const FString Output = TEXT("UCsDataMapping::PerformAddEntry: Warning. No Data set for [") + DataTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("].");

									if (UCsLibrary_Common::IsDefaultObject(this))
										UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

									UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);
								}
								// Check LoadFlags
								if (Entry.Data_LoadFlags != LoadFlags)
								{
									for (int32 J = 0; J < NCsLoadFlags_Editor::MAX; J++)
									{
										if (CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, J))
										{
											if (!CS_TEST_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J))
											{
												const FString PreviousDataLoadFlagsAsString = TEXT("(") + EMCsLoadFlags::Get().MaskToString(Entry.Data_LoadFlags) + TEXT(")");

												CS_SET_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J);

												const FString DataLoadFlagsAsString = TEXT("(") + EMCsLoadFlags::Get().MaskToString(Entry.Data_LoadFlags) + TEXT(")");
												const FString LoadFlagsAsString		= TEXT("(") + EMCsLoadFlags::Get().ToString((int32)J) + TEXT(")");

												const FString Output = TEXT("UCsDataMapping::PerformAddEntry: [") + DataTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("] Adding LoadFlags ") + PreviousDataLoadFlagsAsString + TEXT(" + ") + LoadFlagsAsString + TEXT(" = ") + DataLoadFlagsAsString + TEXT(".");

												if (UCsLibrary_Common::IsDefaultObject(this))
													UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

												UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);
											}
										}
									}
								}

								OutOutput += TEXT("[") + DataTypeAsString + TEXT(", ") + FString::FromInt(I) + TEXT("]");
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

							if (UCsLibrary_Common::IsDefaultObject(this))
							{
								UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
								UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
							}
							return false;
						}
						// Search for Asset, and ADD it
						else
						{
							TArray<UBlueprint*> Bps;

							UCsLibrary_Asset::GetAssets<UBlueprint>(ShortCode, ECsStringCompare::Equals, Bps);

							// Multiple Assets with the same name.
							if (Bps.Num() > 1)
							{
								UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformAddEntry: FAILED. Multiple Assets with the same ShortCode name."));

								const int32 BpCount = Bps.Num();

								for (int32 I = 0; I < BpCount; ++I)
								{
									UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformAddEntry: %s at %s"), *DataTypeAsString, *(Bps[I]->GetPathName()));
								}

								OutOutput = TEXT("ERROR");
								OutMessage = TEXT("FAILED. Multiple Assets with the same ShortCode name. Check LOG.");

								if (UCsLibrary_Common::IsDefaultObject(this))
								{
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
								}
								return false;
							}
							// Single Asset
							else
							if (Bps.Num() == 1)
							{
								// Check ShortCode on Data
								if (UObject* DOb = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject())
								{
									ICsData* IData = Cast<ICsData>(DOb);

									// ADD
									if (ShortCode == IData->GetShortCode() &&
										DataType == IData->GetType())
									{
										Member->AddDefaulted();
										(*Member)[EntryCount].ShortCode		 = ShortCode;
										(*Member)[EntryCount].Data			 = Cast<UBlueprintCore>(Bps[0])->GeneratedClass;
										(*Member)[EntryCount].Data_LoadFlags = LoadFlags;

										CS_SET_BLUEPRINT_BITFLAG((*Member)[EntryCount].Data_LoadFlags, ECsLoadFlags::Game);

										OutOutput = DataTypeAsString + TEXT(", ") + FString::FromInt(EntryCount);
										OutMessage = TEXT("SUCCESS.");

										if (UCsLibrary_Common::IsDefaultObject(this))
										{
											UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
											UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
										}
										MarkPackageDirty();
										return true;
									}
									// Mismatch. FAILED
									else
									{
										if (ShortCode != IData->GetShortCode())
											OutOutput = TEXT("ShortCode mismatch. ") + IData->GetShortCode().ToString() + TEXT(" != ") + ShortCode.ToString();
										else
											OutOutput = TEXT("DataType mismatch. ") + IData->GetType().Name + TEXT(" != ") + DataTypeAsString;
										OutMessage = TEXT("FAILED.");

										if (UCsLibrary_Common::IsDefaultObject(this))
										{
											UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
											UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
										}
										return false;
									}
								}
								// Data NOT the correct Class type
								else
								{
									UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformAddEntry: FAILED. %s at %s is NOT of type IsCsData."), *DataTypeAsString, *(Bps[0]->GetPathName()));

									OutOutput = TEXT("Asset is NOT of type ICsData. Check LOG.");
									OutMessage = TEXT("FAILED.");

									if (UCsLibrary_Common::IsDefaultObject(this))
									{
										UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
										UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
									}
									return false;
								}
							}
							// No Asset
							else
							{
								OutOutput = TEXT("No Asset Found.");
								OutMessage = TEXT("FAILED.");

								if (UCsLibrary_Common::IsDefaultObject(this))
								{
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
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

bool UCsDataMapping::PerformAddEntry(const FName& ShortCode, const int32& LoadFlags, FString& OutMessage, FString& OutOutput)
{
	// Check for valid ShortCode
	if (ShortCode == NAME_None ||
		ShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	// Search for Asset
	TArray<UBlueprint*> Bps;

	UCsLibrary_Asset::GetAssets<UBlueprint>(ShortCode, ECsStringCompare::Equals, Bps);

	TSubclassOf<UObject> Data = nullptr;
	UObject* DataDOb		  = nullptr;
	ICsData* IData		      = nullptr;

	const int32 BpCount = Bps.Num();

	// Multiple Assets with the same name.
	if (BpCount > 1)
	{
		const FString Output = TEXT("UCsDataMapping::PerformAddEntry: FAILED. Multiple Assets with the same ShortCode name.");

		if (UCsLibrary_Common::IsDefaultObject(this))
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);

		for (int32 I = 0; I < BpCount; ++I)
		{
			const FString AdditionalOutput = TEXT("UCsDataMapping::PerformAddEntry: ") + Bps[I]->GetPathName();

			if (UCsLibrary_Common::IsDefaultObject(this))
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(AdditionalOutput, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *AdditionalOutput);
		}

		OutOutput = TEXT("ERROR");
		OutMessage = TEXT("FAILED. Multiple Assets with the same ShortCode name. Check LOG.");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}
	// Single Asset
	else
	if (BpCount == 1)
	{
		// Check ShortCode on Data
		DataDOb = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject();
		IData   = Cast<ICsData>(DataDOb);

		if (IData)
		{
			// ADD
			if (ShortCode == IData->GetShortCode() &&
				EMCsDataType::Get().IsValidEnum(IData->GetType()))
			{
				Data = Cast<UBlueprintCore>(Bps[0])->GeneratedClass;
			}
			// Mismatch. FAILED
			else
			{
				if (ShortCode != IData->GetShortCode())
					OutOutput = TEXT("ShortCode mismatch. ") + IData->GetShortCode().ToString() + TEXT(" != ") + ShortCode.ToString();
				else
					OutOutput = TEXT("Asset: ") + ShortCode.ToString() + TEXT(" has an INVALID DataType");
				OutMessage = TEXT("FAILED.");

				if (UCsLibrary_Common::IsDefaultObject(this))
				{
					UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
					UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
				}
				return false;
			}
		}
		// Data NOT the correct Class type
		else
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformAddEntry: FAILED. %s is NOT of type ICsData."), *(Bps[0]->GetPathName()));

			OutOutput = TEXT("Asset is NOT of type ICsData. Check LOG.");
			OutMessage = TEXT("FAILED.");

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
			}
			return false;
		}
	}
	// No Asset
	else
	{
		OutOutput = TEXT("No Asset Found.");
		OutMessage = TEXT("FAILED.");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}

	const FECsDataType& DataType = IData->GetType();

	// Search Entries
	int32 DataTypeIndex = INDEX_NONE;

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
					DataTypeIndex++;

					if (EMCsDataType::Get().GetEnumAt(DataTypeIndex) != DataType)
						continue;

					const FString& DataTypeAsString = DataType.Name;

					bool Found = false;
					int32 FoundCount = 0;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						// Check if Asset has ALREADY been added
						const int32 EntryCount = Member->Num();

						for (int32 I = 0; I < EntryCount; ++I)
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

									const FString Output = TEXT("UCsDataMapping::PerformAddEntry: Warning. No Data was set for [") + DataTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("]. Manually setting it to ") + DataDOb->GetPathName() + TEXT(".");

									if (UCsLibrary_Common::IsDefaultObject(this))
										UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

									UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);
								}
								// Check LoadFlags
								if (Entry.Data_LoadFlags != LoadFlags)
								{
									for (int32 J = 0; J < NCsLoadFlags_Editor::MAX; J++)
									{
										if (CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, J))
										{
											if (!CS_TEST_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J))
											{
												const FString PreviousDataLoadFlagsAsString = TEXT("(") + EMCsLoadFlags::Get().MaskToString(Entry.Data_LoadFlags) + TEXT(")");

												CS_SET_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, J);
												
												const FString DataLoadFlagsAsString = TEXT("(") + EMCsLoadFlags::Get().MaskToString(Entry.Data_LoadFlags) + TEXT(")");
												const FString LoadFlagsAsString     = TEXT("(") + EMCsLoadFlags::Get().ToString((int32)J) + TEXT(")");

												const FString Output = TEXT("UCsDataMapping::PerformAddEntry: [") + DataTypeAsString + TEXT(", ") + ShortCode.ToString() + TEXT(", ") + FString::FromInt(I) + TEXT("] Adding LoadFlags ") + PreviousDataLoadFlagsAsString + TEXT(" + ") + LoadFlagsAsString + TEXT(" = ") + DataLoadFlagsAsString + TEXT(".");

												if (UCsLibrary_Common::IsDefaultObject(this))
													UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformAddEntryAdditionalOutput"), 1.5f);

												UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);
											}
										}
									}
								}
								OutOutput += TEXT("[") + DataTypeAsString + TEXT(", ") + FString::FromInt(I) + TEXT("]");
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

							if (UCsLibrary_Common::IsDefaultObject(this))
							{
								UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
								UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
							}
							return false;
						}
						else
						{
							Member->AddDefaulted();
							(*Member)[EntryCount].ShortCode		 = ShortCode;
							(*Member)[EntryCount].Data			 = Data;
							(*Member)[EntryCount].Data_LoadFlags = LoadFlags;

							CS_SET_BLUEPRINT_BITFLAG((*Member)[EntryCount].Data_LoadFlags, ECsLoadFlags::Game);

							OutOutput = DataTypeAsString + TEXT(", ") + FString::FromInt(EntryCount);
							OutMessage = TEXT("SUCCESS.");

							if (UCsLibrary_Common::IsDefaultObject(this))
							{
								UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformAddEntryOutput"), 5.0f);
								UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformAddEntryMessage"), 5.0f);
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

bool UCsDataMapping::IsValid()
{
	// Check Payload is SET
	if (!Payload.Get())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformValidate: No Payload set."));
		return false;
	}
	// Check Payload is VALID
	UCsData_Payload* PayloadDOb = Payload->GetDefaultObject<UCsData_Payload>();

	if (!PayloadDOb->IsValid())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformValidate: Payload is NOT Valid."));
		return false;
	}
	return true;
}

bool UCsDataMapping::PerformValidate(FString& OutMessage, FString& OutOutput)
{
	bool Pass = true;

	// Check Payload is SET
	if (!Payload.Get())
	{
		OutMessage = TEXT("No Payload set.");
		OutOutput  = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformValidateOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformValidateMessage"), 5.0f);
		}

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformValidate: No Payload set."));
		return false;
	}
	// Check Payload is VALID
	UCsData_Payload* PayloadDOb = Payload->GetDefaultObject<UCsData_Payload>();

	if (!PayloadDOb->IsValid())
	{
		OutMessage = TEXT("Payload is NOT Valid.");
		OutOutput  = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutOutput, TEXT("DataMapping"), TEXT("PerformValidateOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(OutMessage, TEXT("DataMapping"), TEXT("PerformValidateMessage"), 5.0f);
		}

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsDataMapping::PerformValidate: Payload is NOT Valid."));
		return false;
	}

	int32 DataTypeIndex = INDEX_NONE;

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
					++DataTypeIndex;

					const FECsDataType& DataType    = EMCsDataType::Get().GetEnumAt(DataTypeIndex);
					const FString& DataTypeAsString = DataType.Name;

					if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
					{
						const int32 EntryCount = Member->Num();

						for (int32 I = EntryCount - 1; I >= 0; --I)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							TArray<UBlueprint*> Bps;
							TArray<FName> PackagePaths;

							UCsLibrary_Asset::GetAssets<UBlueprint>(Entry.ShortCode, ECsStringCompare::Equals, Bps, PackagePaths);

							const int32 BpCount = Bps.Num();
							// ShortCode NO longer EXISTS in AssetRegistry
							if (BpCount == CS_EMPTY)
							{
								const FString Output = TEXT("UCsDataMapping::PerformValidate: Data with ShortCode: ") + Entry.ShortCode.ToString() + TEXT("is NOT found.");

								if (UCsLibrary_Common::IsDefaultObject(this))
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

								UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);
								Pass &= false;
								continue;
							}
							// More than ONE Blueprint Asset EXISTS with the same ShortCode
							if (BpCount > 1)
							{
								const FString Output = TEXT("UCsDataMapping::PerformValidate: Multiple Data with ShortCode: ") + Entry.ShortCode.ToString();

								if (UCsLibrary_Common::IsDefaultObject(this))
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

								UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);

								for (int32 J = 0; J < BpCount; J++)
								{
									const FString AdditionalOutput = TEXT("UCsDataMapping::PerformValidate: ShortCode: ") + Entry.ShortCode.ToString() + TEXT(" at ") + PackagePaths[J].ToString();

									if (UCsLibrary_Common::IsDefaultObject(this))
										UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(AdditionalOutput, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

									UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *AdditionalOutput);
								}
								Pass &= false;
								continue;
							}
							// Check Asset is NOT of type ICsData
							UObject* DataDOb = Cast<UBlueprintCore>(Bps[CS_FIRST])->GeneratedClass->GetDefaultObject();
							ICsData* IData   = Cast<ICsData>(DataDOb);

							if (!IData)
							{
								const FString Output = TEXT("UCsDataMapping::PerformValidate: Data with ShortCode: ") + Entry.ShortCode.ToString() + TEXT(" is NOT of type ICsData.");

								if (UCsLibrary_Common::IsDefaultObject(this))
									UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Output, TEXT("DataMapping"), TEXT("PerformValidate"), 1.5f);

								UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s"), *Output);
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

void UCsDataMapping::PostEditChangeProperty(struct FPropertyChangedEvent& e)
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

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(FindEntry.Output, TEXT("DataMapping"), TEXT("FindEntryOutput"), 5.0f);
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(FindEntry.Message, TEXT("DataMapping"), TEXT("FindEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}

		// Search Entries
		TArray<FCsDataMappingEntry*> OutEntries; 
		TArray<FECsDataType> OutDataTypes;
		TArray<int32> OutIndices;

		PerformFindEntry(FindEntry.ShortCode, OutEntries, OutDataTypes, OutIndices);

		const int32 EntryCount = OutEntries.Num();

		for (int32 I = 0; I < EntryCount; ++I)
		{
			if (I > 0)
				FindEntry.Output += TEXT(", ");

			const FString& DataTypeAsString = OutDataTypes[I].Name;
			FindEntry.Output			    += TEXT("[") + DataTypeAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");
		}

		if (EntryCount == CS_EMPTY)
			FindEntry.Output = TEXT("No Results.");
		FindEntry.Message = TEXT("SUCCESS");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(FindEntry.Output, TEXT("DataMapping"), TEXT("FindEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(FindEntry.Message, TEXT("DataMapping"), TEXT("FindEntryMessage"), 5.0f);
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

		PerformAddEntry(AddEntry.ShortCode, AddEntry.DataType, AddEntry.LoadFlags, AddEntry.Message, AddEntry.Output);
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

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(RemoveEntry.Output, TEXT("DataMapping"), TEXT("RemoveEntryOutput"), 5.0f);
				UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(RemoveEntry.Message, TEXT("DataMapping"), TEXT("RemoveEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}

		// Search Entries
		bool Found = false;

		int32 DataTypeIndex = INDEX_NONE;

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
						++DataTypeIndex;

						const FECsDataType& DataType   = EMCsDataType::Get().GetEnumAt(DataTypeIndex);
						const FString& DataTypeAsString = DataType.Name;

						if (TArray<FCsDataMappingEntry>* Member = Property->ContainerPtrToValuePtr<TArray<FCsDataMappingEntry>>(this))
						{
							const int32 EntryCount = Member->Num();

							for (int32 I = EntryCount - 1; I >= 0; --I)
							{
								FCsDataMappingEntry& Entry = (*Member)[I];

								if (RemoveEntry.ShortCode == Entry.ShortCode)
								{
									if (Found)
										RemoveEntry.Output += TEXT(", ");

									RemoveEntry.Output += TEXT("[") + DataTypeAsString + TEXT(", ") + FString::FromInt(I) + TEXT("]");
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

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(RemoveEntry.Output, TEXT("DataMapping"), TEXT("RemoveEntryOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(RemoveEntry.Message, TEXT("DataMapping"), TEXT("RemoveEntryMessage"), 5.0f);
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

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Validate.Output, TEXT("DataMapping"), TEXT("ValidateOutput"), 5.0f);
			UCsLibrary_Common_DEPRECATED::DisplayNotificationInfo(Validate.Message, TEXT("DataMapping"), TEXT("ValidateMessage"), 5.0f);
		}
		Validate.Validate = false;
	}
	Super::PostEditChangeProperty(e);

	GenerateMaps();
}

bool UCsDataMapping::CheckEntryExists(const FName& ShortCode, const FECsDataType& DataType, const ECsLoadFlags_Editor& LoadFlags, FString& OutMessage)
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

						for (int32 I = 0; I < EntryCount; ++I)
						{
							FCsDataMappingEntry& Entry = (*Member)[I];

							if (ShortCode == Entry.ShortCode)
							{
								bool Found = true;
								// Check DataType
								if (DataType != EMCsDataType::Get().GetSafeEnum(MemberName))
								{
									OutMessage += TEXT("DataType mismatch: ") + DataType.Name + TEXT(" != ") + MemberName + TEXT(".");
									Found = false;
								}
								// Check LoadFlags
								const ECsLoadFlags Flags = NCsLoadFlags_Editor::ToBaseType(LoadFlags);

								if (!CS_TEST_BLUEPRINT_BITFLAG(Entry.Data_LoadFlags, Flags))
								{
									OutMessage += TEXT(" LoadFlags: [") + EMCsLoadFlags::Get().MaskToString(Entry.Data_LoadFlags) + TEXT("] does NOT include ") + EMCsLoadFlags_Editor::Get().ToString(LoadFlags) + TEXT(".");
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

#pragma endregion Editor