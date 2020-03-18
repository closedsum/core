// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CoreUObject/Public/UObject/Object.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_Async.h"
// Managers
#include "Managers/Load/CsManager_Load.h"
// Data
#include "Data/CsData.h"
#include "Data/CsData_Payload.h"
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
		extern CSCOREDEPRECATED_API const FString LoadData;
	}
}

#pragma endregion Cache

// Structs
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataMappingFindEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Find;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataMappingAddEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Add;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FECsDataType DataType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;

	FCsDataMappingAddEntry() :
		Add(false),
		ShortCode(NAME_None),
		DataType(EMCsDataType::Get().GetMAX()),
		LoadFlags(0),
		Message(),
		Output()

	{
		CS_SET_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags::Game);
	}
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataMappingRemoveEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Remove;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataMappingValidate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Validate;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

#pragma endregion Structs

class ICsData;
class UCsData_Payload;
class UWorld;

UCLASS(Abstract, NotBlueprintable)
class CSCOREDEPRECATED_API UCsDataMapping : public UObject
{
	GENERATED_UCLASS_BODY()

	virtual void ClearLoaded();

// Mapping
#pragma region
public:

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
	TMap<FECsDataType, TArray<FCsData>> Datas_Loaded;
	TMap<FECsDataType, TMap<FName, FCsData>> Datas_Loaded_Map;
	TMap<FECsDataType, TMap<FName, uint16>> Datas_ShortCodeToLookUpCode_Map;
	TMap<FECsDataType, TMap<uint16, FName>> Datas_LookUpCodeToShortCode_Map;

#pragma endregion Mapping

public:

	const FECsDataType& GetDataType(const FName& ShortCode);

	//UPROPERTY(VisibleDefaultsOnly, Category = "Data Mapping")
	//TArray<FCsCategoryMemberAssociation> CategoryMemberAssociations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Mapping")
	TSubclassOf<UCsData_Payload> Payload;

	UFUNCTION(BlueprintCallable, Category = "Payload")
	UCsData_Payload* GetPayload();

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

	//void AsyncLoadObjects(UWorld* World, const FECsDataCollectionType& CollectionType, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjectPaths& Delegate);

	virtual void OnFinishedAsyncLoadingAssetsSetReferences(const FECsDataCollectionType& CollectionType, const TArray<UObject*>& LoadedAssets);

	// ShortCode
#pragma region
public:

	const FCsData& LoadData(const FString& FunctionName, const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	const FCsData& LoadData(const FECsDataType& DataType, const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	const FCsData& LoadData(const FName& ShortCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

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

	const FCsData& LoadData(const FString& FunctionName, const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	const FCsData& LoadData(const FECsDataType& DataType, const uint16& LookUpCode, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

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

	const FCsData& LoadData_Internal(const FString& FunctionName, const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);
	const FCsData& LoadData_Internal(const FECsDataType& DataType, FCsDataMappingEntry& Mapping, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

public:

	void LoadAllData(const FString& FunctionName, const FECsDataType& DataType, const ECsLoadFlags& LoadFlags = ECsLoadFlags::Game);

	// Add
#pragma region
protected:

	virtual const FCsData& AddLoadedData(const FECsDataType& DataType, const FName& ShortCode, ICsData* InData);

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

	virtual const FCsData& AddLoadedData(const FECsDataType& DataType, const uint16& LookUpCode, ICsData* InData);

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

	virtual const FCsData& GetLoadedData(const FECsDataType& DataType, const FName& ShortCode);

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

	virtual const FCsData& GetLoadedData(const FName& ShortCode, FECsDataType& OutDataType);
	virtual const FCsData& GetLoadedData(const FName& ShortCode);
	virtual const FCsData& GetLoadedData(const FECsDataType& DataType, const uint16& LookUpCode);

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

	virtual void GetLoadedDatas(const FECsDataType& DataType, TArray<FCsData>& OutDatas);
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
public:

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

#pragma endregion Editor
};