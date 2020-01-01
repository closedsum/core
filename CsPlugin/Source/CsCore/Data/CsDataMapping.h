// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Load.h"
#include "CsDataMapping.generated.h"

// Macros - Only use for CHILD of UCsDataMapping
#pragma region

#define RS_DATA_MAPPINGS_CLEAR_LOADED(TYPE) TYPE##_Loaded.Reset(); \
											TYPE##_Loaded_Map.Reset();

#define RS_GET_DATA_MAPPINGS(TYPE)	if (DataType == NCsDataType::TYPE) \
										return &TYPE;

#define RS_GET_DATA_MAPPINGS_MAP(TYPE)	if (DataType == NCsDataType::TYPE) \
											return &TYPE##_Map;

#define RS_ADD_LOADED_DATA_BY_SHORTCODE(MAPPING, CLASS, LOG, TYPE)	if (DataType == NCsDataType::TYPE) \
																	{ \
																		if (TYPE##_Loaded_Map.Find(ShortCode)) \
																		{ \
																			UE_LOG(LOG, Warning, TEXT("%s::AddLoadedData: Attempting to Add DataType: %s with ShortCode: %s which has ALREADY been Added."), #MAPPING, *(DataType.Name), *ShortCode.ToString()); \
																			return; \
																		} \
																		AddLoadData_Internal<CLASS>(TYPE, TYPE##_Loaded_Map, TYPE##_Loaded, ShortCode, InData); \
																		return; \
																	}

#define RS_ADD_LOADED_DATA_BY_LOOKUPCODE(MAPPING, CLASS, LOG, TYPE)	if (DataType == NCsDataType::TYPE) \
																	{ \
																		if (LookUpCode < TYPE.Num() && TYPE##_Loaded[LookUpCode]) \
																		{ \
																			const FName ShortCode = TYPE[LookUpCode].ShortCode; \
																			UE_LOG(LOG, Warning, TEXT("%s::AddLoadedData: Attempting to Add DataType: %s with ShortCode: %s and LookUpCode: %d which has ALREADY been Added."), #MAPPING, *(DataType.Name), *ShortCode.ToString(), LookUpCode); \
																		} \
																		else \
																		{ \
																			AddLoadData_Internal<CLASS>(TYPE, TYPE##_Loaded_Map, TYPE##_Loaded, LookUpCode, InData); \
																		} \
																		return; \
																	}

#define RS_GET_LOADED_DATA_BY_SHORTCODE(CLASS, TYPE) if (DataType == NCsDataType::TYPE) \
														return GetLoadedData_Internal<ICsData, CLASS>(TYPE, TYPE##_Map, TYPE##_Loaded_Map, TYPE##_Loaded, ShortCode);

#define RS_GET_LOADED_DATA_OUT(CLASS, TYPE) if (CLASS** Data = TYPE##_Loaded_Map.Find(ShortCode)) \
											{ \
												OutDataType = NCsDataType::TYPE; \
												return *Data; \
											}

#define RS_GET_LOADED_DATA_BY_LOOKUPCODE(CLASS, TYPE)	if (DataType == NCsDataType::TYPE) \
															return GetLoadedData_Internal<ICsData, CLASS>(TYPE, TYPE##_Loaded_Map, TYPE##_Loaded, LookUpCode);

#define RS_GET_LOADED_DATAS(TYPE)	if (DataType == NCsDataType::TYPE) \
									{ \
										TArray<FName> Keys; \
										TYPE##_Loaded_Map.GetKeys(Keys); \
										\
										const int32 Count = Keys.Num(); \
										\
										for (int32 I = 0; I < Count; ++I) \
										{ \
											OutDatas.Add(*(TYPE##_Loaded_Map.Find(Keys[I]))); \
										} \
										return; \
									}

#pragma endregion Macros

// Cache
#pragma region

namespace NCsDataMappingCached
{
	namespace Str
	{
		extern CSCORE_API const FString LoadData;
	}
}

#pragma endregion Cache

class ICsData;

UCLASS(Abstract, NotBlueprintable)
class CSCORE_API UCsDataMapping : public UObject
{
	GENERATED_UCLASS_BODY()

	virtual void ClearLoaded();

// Mapping
#pragma region
protected:

	TArray<FCsDataMappingEntry>* GetDataMappings(const FECsDataType& DataType);

	TMap<FName, FCsDataMappingEntry>* GetDataMappings_Map(const FECsDataType& DataType);

	FCsDataMappingEntry* GetDataMappingEntry(const FECsDataType& DataType, const FName& ShortCode);

	/**
	* Assign Datas_Entry and Datas_Entry_Map references from the entries setup in the child class.
	* This should only be called ONCE.
	*/
	virtual void AssignDataMappingReferences();

public:

	virtual void GenerateMaps();

protected:

	TMap<FECsDataType, TArray<FCsDataMappingEntry>*> Datas_Entry;
	TMap<FECsDataType, TMap<FName, FCsDataMappingEntry>*> Datas_Entry_Map;
	TMap<FECsDataType, TArray<ICsData*>> Datas_Loaded;
	TMap<FECsDataType, TMap<FName, ICsData*>> Datas_Loaded_Map;
	TMap<FECsDataType, TMap<FName, uint16>> Datas_ShortCodeToLookUpCode_Map;
	TMap<FECsDataType, TMap<uint16, FName>> Datas_LookUpCodeToShortCode_Map;

#pragma endregion Mapping

public:

	const FECsDataType& GetDataType(const FName &ShortCode);

	//UPROPERTY(VisibleDefaultsOnly, Category = "Data Mapping")
	//TArray<FCsCategoryMemberAssociation> CategoryMemberAssociations;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Mapping")
	//TSubclassOf<class ACsData_Payload> Payload;

	//UFUNCTION(BlueprintCallable, Category = "Payload")
	//class ACsData_Payload* GetPayload();

// Asset References
#pragma region
public:

	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;

	bool DoesDataAssetReferenceExist(const FECsDataType& DataType, const FName& ShortCode);
	bool DoesDataAssetReferenceExist(const FName& ShortCode);

	bool AddDataAssetReference(const FECsDataType& DataType, const FName& ShortCode, ICsData* InData);

	FStringAssetReference GetStringAssetReference(const FECsDataType& DataType, const FName& ShortCode);
	FStringAssetReference GetStringAssetReference(const FECsDataType& DataType, const uint16& LookUpCode);

	void GetStringAssetReferences(const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags, TArray<FStringAssetReference>& OutReferences);
	void GetStringAssetReferences(const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags, TArray<FStringAssetReference>& OutReferences);

	void PopulateDataAssetReferences();

	TArray<FStringAssetReference> DataAssetReferences;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data Mapping")
	bool bForcePopulateAssetReferences;

	void PopulateAssetReferences();

	UPROPERTY(VisibleDefaultsOnly, Category = "Data Mapping")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

#pragma endregion Asset References

// Load
#pragma region
public:

	virtual ECsLoadFlags GetLoadAssetsFlags(const FECsDataCollectionType& CollectionType);
	virtual void GetDataCollectionShortCodes(const FECsDataCollectionType& CollectionType, TArray<FName>& OutShortCodes);

	DECLARE_DELEGATE_TwoParams(FOnGetDataCollectionShortCodes, const FECsDataCollectionType&, TArray<FName>&);

	FOnGetDataCollectionShortCodes OnGetDataCollectionShortCodes_Event;

	virtual const FECsDataType& GetDataTypeFromShortCode(const FName& ShortCode);

	virtual void GetLoadStringAssetReferences(const FECsDataCollectionType& CollectionType, TArray<FStringAssetReference>& OutAssetReferences);

	template<typename T>
	void AsyncLoadAssets(const FECsDataCollectionType& CollectionType, const ECsLoadAsyncOrder& AsyncOrder, T* CallbackCaller,  void (T::*Callback)(const TArray<UObject*>&, const float&))
	{
		TArray<FStringAssetReference> References;

		GetLoadStringAssetReferences(CollectionType, References);

		if (References.Num() == RS_EMPTY)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsDataMapping::AsyncLoadAssets: Trying to load 0 assets."));

			TArray<UObject*> LoadedAssets;
			(CallbackCaller->*Callback)(LoadedAssets, 0.0f);
			return;
		}
		UCsManager_Load::Get()->LoadAssetReferences<T>(Cast<UObject>(CallbackCaller)->GetWorld(), References, AsyncOrder, CallbackCaller, Callback);
	}

	virtual void OnFinishedAsyncLoadingAssetsSetReferences(const FECsDataCollectionType& CollectionType, const TArray<UObject*>& LoadedAssets);

	// ShortCode
#pragma region
public:

	ICsData* LoadData(const FString& FunctionName, const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	ICsData* LoadData(const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	ICsData* LoadData(const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	template<typename T>
	T* LoadData(const FString& FunctionName, const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game)
	{
		return Cast<T>(LoadData(FunctionName, DataType, ShortCode, LoadFlags));
	}

	template<typename T>
	T* LoadData(const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game)
	{
		return Cast<T>(LoadData(NCsDataMappingCached::Str::LoadData, DataType, ShortCode, LoadFlags));
	}

#pragma endregion ShortCode

	// LookUpCode
#pragma region
public:

	ICsData* LoadData(const FString& FunctionName, const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	ICsData* LoadData(const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	template<typename T>
	T* LoadData(const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game)
	{
		return Cast<T>(LoadData(NCsDataMappingCached::Str::LoadData, DataType, LookUpCode, LoadFlags));
	}

	template<typename T>
	T* LoadData(const FString& FunctionName, const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game)
	{
		return Cast<T>(LoadData(FunctionName, DataType, LookUpCode, LoadFlags));
	}

#pragma endregion LookUpCode

protected:

	ICsData* LoadData_Internal(const FString& FunctionName, const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	ICsData* LoadData_Internal(const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

public:

	void LoadAllData(const FString& FunctionName, const FECsDataType& DataType, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	// Add
#pragma region
protected:

	virtual void AddLoadedData(const FECsDataType& DataType, const FName& ShortCode, ICsData* InData);

	template<typename T>
	void AddLoadData_Internal(const TArray<FCsDataMappingEntry>& Datas, TMap<FName, T*>& OutDatas_Loaded_Map, TArray<T*>& OutDatas_Loaded, const FName& ShortCode, ICsData* InData)
	{
		const uint16 Count = Datas.Num();
		uint16 LookUpCode  = RS_INVALID_LOOK_UP_CODE;

		for (uint16 I = 0; I < Count; ++I)
		{
			if (Datas[I].ShortCode == ShortCode)
			{
				LookUpCode = I;
				break;
			}
		}

		OutDatas_Loaded_Map.Add(ShortCode, Cast<T>(InData));
		OutDatas_Loaded_Map.KeySort(TLess<FName>());

		if (OutDatas_Loaded.Num() == RS_EMPTY)
		{
			for (uint16 I = 0; I < Count; ++I)
			{
				OutDatas_Loaded.Add(nullptr);
			}
		}
		OutDatas_Loaded[LookUpCode] = Cast<T>(InData);
	}

	virtual void AddLoadedData(const FECsDataType& DataType, const uint16& LookUpCode, ICsData* InData);

	template<typename T>
	void AddLoadData_Internal(const TArray<FCsDataMappingEntry>& Datas, TMap<FName, T*>& OutDatas_Loaded_Map, TArray<T*>& OutDatas_Loaded, const uint16& LookUpCode, ICsData* InData)
	{
		const FName ShortCode = Datas[LookUpCode].ShortCode;
		T** Data			  = OutDatas_Loaded_Map.Find(ShortCode);

		T* DataOb = Cast<T>(InData->GetObject());

		check(DataOb == *Data);

		OutDatas_Loaded_Map.Add(ShortCode, DataOb);
		OutDatas_Loaded_Map.KeySort(TLess<FName>());

		if (OutDatas_Loaded.Num() == RS_EMPTY)
		{
			const uint16 Count = Datas.Num();

			for (uint16 I = 0; I < Count; ++I)
			{
				OutDatas_Loaded.Add(nullptr);
			}
		}
		OutDatas_Loaded[LookUpCode] = DataOb;
	}

#pragma endregion Add

	// Get
#pragma region
public:

	virtual ICsData* GetLoadedData(const FECsDataType& DataType, const FName& ShortCode);
protected:
	template<typename T, typename U>
	T* GetLoadedData_Internal(const TArray<FCsDataMappingEntry>& Datas, const TMap<FName, FCsDataMappingEntry>& Datas_Map, const TMap<FName, U*>& InDatas_Loaded_Map, TArray<U*>& OutDatas_Loaded, const FName& ShortCode)
	{
		U** Data = InDatas_Loaded_Map.Find(ShortCode);

		if (OutDatas_Loaded.Num() == RS_EMPTY)
		{
			const uint16 Count = Datas.Num();

			for (uint16 I = 0; I < Count; ++I)
			{
				OutDatas_Loaded.Add(nullptr);
			}
		}

		if (!Data)
			return nullptr;

		FCsDataMappingEntry* Entry = Datas_Map.Find(ShortCode);
		const uint16& LookUpCode   = Entry->LookUpCode;
		OutDatas_Loaded[LookUpCode]= *Data;

		return Cast<T>(*Data);
	}
public:
	virtual ICsData* GetLoadedData(const FName& ShortCode, FECsDataType& OutDataType);
	virtual ICsData* GetLoadedData(const FName& ShortCode);
	virtual ICsData* GetLoadedData(const FECsDataType& DataType, const uint16& LookUpCode);
protected:
	template<typename T, typename U>
	T* GetLoadedData_Internal(const TArray<FCsDataMappingEntry>& Datas, const TMap<FName, U*>& InDatas_Loaded_Map, TArray<U*>& OutDatas_Loaded, const uint16& LookUpCode)
	{
		const FName ShortCode = Datas[LookUpCode].ShortCode;
		U** Data			  = InDatas_Loaded_Map.Find(ShortCode);

		if (OutDatas_Loaded.Num() == RS_EMPTY)
		{
			uint16 Count = Datas.Num();

			for (uint16 I = 0; I < Count; ++I)
			{
				OutDatas_Loaded.Add(nullptr);
			}
		}
		OutDatas_Loaded[LookUpCode] = *Data;
		return Cast<T>(*Data);
	}
public:
	virtual void GetLoadedDatas(const FECsDataType& DataType, TArray<ICsData*>& OutDatas);
	virtual void GetLoadedDataShortCodes(const FECsDataType& DataType, TArray<FName>& OutShortCodes);

#pragma endregion Get

#pragma endregion Load

// IsValid
#pragma region
public:

	bool CheckDataIsValid(const FString& FunctionName, const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	bool CheckDataIsValid(const FString& FunctionName, const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	bool CheckAllDataIsValid(const FString& FunctionName, const FECsDataType& DataType, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

#pragma endregion IsValid
	
// Get
#pragma region
public:

	FName GetShortCode(const FECsDataType& DataType, const uint16& LookUpCode);

	uint16 GetLookUpCode(const FECsDataType& DataType, const FName& ShortCode);

#pragma endregion Get

// Json
#pragma region

	virtual void PostLoad() override;

	virtual FString GetAbsolutePath();

	//TCsWriteObjectToJson_Internal WriteObjectToJson_Internal;
	//TCsReadObjectFromJson_Internal ReadObjectFromJson_Internal;

	virtual void SaveToJson();

	bool bHasLoadedFromJson;

	virtual void LoadFromJson();

#pragma endregion Json

// Editor
#pragma region
/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Mapping|Editor")
	FCsDataMappingFindEntry FindEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Mapping|Editor")
	FCsDataMappingAddEntry AddEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Mapping|Editor")
	FCsDataMappingRemoveEntry RemoveEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Mapping|Editor")
	FCsDataMappingValidate Validate;

#if WITH_EDITOR

	bool PerformFindEntry(const FName& ShortCode, TArray<FCsDataMappingEntry*>& OutEntries, TArray<FECsDataType>& OutDataTypes, TArray<int32>& OutIndices);
	bool PerformAddEntry(const FName& ShortCode, const FECsDataType& DataType, const int32& LoadFlags, FString& OutMessage, FString& OutOutput);
	bool PerformAddEntry(const FName& ShortCode, const int32& LoadFlags, FString& OutMessage, FString& OutOutput);
	
	virtual bool IsValid();
	virtual bool PerformValidate(FString& OutMessage, FString& OutOutput);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	bool CheckEntryExists(const FName& ShortCode, const FECsDataType& DataType, const ECsLoadFlags_Editor& LoadFlags, FString& OutMessage);

#endif // #if WITH_EDITOR

	FCsMutex AsyncTaskMutex;
*/
#pragma endregion Editor
};