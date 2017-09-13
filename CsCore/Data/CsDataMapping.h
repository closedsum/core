// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "CsTypes.h"
#include "CsCommon.h"
#include "Managers/CsManager_Loading.h"
#include "CsDataMapping.generated.h"

// Macros - Only use for CHILD of ACsDataMapping
#pragma region

#define CS_DATA_MAPPINGS_CLEAR_LOADED(TYPE) TYPE##_Loaded.Reset(); \
											TYPE##_Loaded_Map.Reset();

#define CS_GET_DATA_MAPPINGS(TYPE)	if (AssetType == ECsAssetType::TYPE) \
										return &TYPE;

#define CS_GET_DATA_MAPPINGS_MAP(TYPE)	if (AssetType == ECsAssetType::TYPE) \
											return &TYPE##_Map;

#define CS_ADD_LOADED_DATA_BY_SHORTCODE(MAPPING, CLASS, LOG, TYPE)	if (AssetType == ECsAssetType::TYPE) \
																	{ \
																		if (TYPE##_Loaded_Map.Find(ShortCode)) \
																		{ \
																			UE_LOG(LOG, Warning, TEXT("%s::AddLoadedData: Attempting to Add AssetType: %s with ShortCode: %s which has ALREADY been Added."), #MAPPING, *ECsAssetType::ToString(AssetType), *ShortCode.ToString()); \
																			return; \
																		} \
																		AddLoadData_Internal<CLASS>(TYPE, TYPE##_Loaded_Map, TYPE##_Loaded, ShortCode, InData); \
																		return; \
																	}

#define CS_ADD_LOADED_DATA_BY_LOOKUPCODE(MAPPING, CLASS, LOG, TYPE)	if (AssetType == ECsAssetType::TYPE) \
																	{ \
																		if (ACsData* Data = GetLoadedData(AssetType, LookUpCode)) \
																		{ \
																			const FName ShortCode = TYPE[LookUpCode].ShortCode; \
																			UE_LOG(LOG, Warning, TEXT("%s::AddLoadedData: Attempting to Add AssetType: %s with ShortCode: %s and LookUpCode: %d which has ALREADY been Added."), #MAPPING, *ECsAssetType::ToString(AssetType), *ShortCode.ToString(), LookUpCode); \
																		} \
																		else \
																		{ \
																			AddLoadData_Internal<CLASS>(TYPE, TYPE##_Loaded_Map, TYPE##_Loaded, LookUpCode, InData); \
																		} \
																		return; \
																	}

#define CS_GET_LOADED_DATA_BY_SHORTCODE(CLASS, TYPE) if (AssetType == ECsAssetType::TYPE) \
														return GetLoadedData_Internal<ACsData, CLASS>(TYPE, TYPE##_Map, TYPE##_Loaded_Map, TYPE##_Loaded, ShortCode);

#define CS_GET_LOADED_DATA_OUT(CLASS, TYPE) if (CLASS** Data = TYPE##_Loaded_Map.Find(ShortCode)) \
											{ \
												OutAssetType = ECsAssetType::TYPE; \
												return *Data; \
											}

#define CS_GET_LOADED_DATA_BY_LOOKUPCODE(CLASS, TYPE)	if (AssetType == ECsAssetType::TYPE) \
															return GetLoadedData_Internal<ACsData, CLASS>(TYPE, TYPE##_Loaded_Map, TYPE##_Loaded, LookUpCode);

#pragma endregion Macros

DECLARE_DELEGATE_TwoParams(FBindableDynEvent_CsDataMapping_OnGetLoadAssetsShortCodes, const TCsLoadAssetsType&, TArray<FName>&);

USTRUCT()
struct FCsDataMappingFindEntry
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

USTRUCT()
struct FCsDataMappingAddEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Add;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FString AssetType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;

	FCsDataMappingAddEntry()
	{
		CS_SET_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags::All);
		CS_SET_BLUEPRINT_BITFLAG(LoadFlags, ECsLoadFlags::Game);
	}
};

USTRUCT()
struct FCsDataMappingRemoveEntry
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

USTRUCT()
struct FCsDataMappingValidate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Validate;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsDataMapping : public AActor
{
	GENERATED_UCLASS_BODY()

	TCsAssetTypeToString AssetTypeToString;
	TCsStringToAssetType StringToAssetType;

	TCsAssetType AssetType_MAX;

	virtual void ClearLoaded();

	virtual TArray<FCsDataMappingEntry>* GetDataMappings(const TCsAssetType &AssetType);

	virtual TMap<FName, FCsDataMappingEntry>* GetDataMappings_Map(const TCsAssetType &AssetType);

	void GenerateMaps(const TCsAssetType &AssetType);
	void GenerateMaps();

	TCsAssetType GetDataAssetType(const FName &ShortCode);

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	TArray<FCsCategoryMemberAssociation> CategoryMemberAssociations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "00 Default")
	class ACsData_Payload* Payload;

// Asset References
#pragma region
public:

	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;

	bool DoesDataAssetReferenceExist(const TCsAssetType &AssetType, const FName &ShortCode);
	bool DoesDataAssetReferenceExist(const FName &ShortCode);

	bool AddDataAssetReference(const TCsAssetType &AssetType, const FName &ShortCode, AActor* InData);

	FStringAssetReference GetStringAssetReference(const TCsAssetType &AssetType, const FName &ShortCode);
	FStringAssetReference GetStringAssetReference(const TCsAssetType &AssetType, const uint16 &LookUpCode);

	void GetStringAssetReferences(const TCsAssetType &AssetType, const FName &ShortCode, const ECsLoadFlags &LoadFlags, TArray<FStringAssetReference> &OutReferences);
	void GetStringAssetReferences(const TCsAssetType &AssetType, const uint16 &LookUpCode, const ECsLoadFlags &LoadFlags, TArray<FStringAssetReference> &OutReferences);

	void PopulateDataAssetReferences();

	TArray<FStringAssetReference> DataAssetReferences;

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	bool ForcePopulateAssetReferences;

	void PopulateAssetReferences();

	UPROPERTY(VisibleDefaultsOnly, Category = "00 Default")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

#pragma endregion Asset References

// Load
#pragma region
public:

	virtual ECsLoadFlags GetLoadAssetsFlags(const TCsLoadAssetsType &AssetsType);
	virtual void GetLoadAssetsShortCodes(const TCsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes);

	FBindableDynEvent_CsDataMapping_OnGetLoadAssetsShortCodes OnGetLoadAssetsShortCodes_Event;

	virtual void GetLoadStringAssetReferences(const TCsLoadAssetsType &AssetsType, TArray<FStringAssetReference> &OutAssetReferences);

	template<typename T>
	void AsyncLoadAssets(const TCsLoadAssetsType &AssetsType, const TCsLoadAsyncOrder &AsyncOrder, T* CallbackCaller,  void (T::*Callback)(const TArray<UObject*>&, const float&))
	{
		TArray<FStringAssetReference> References;

		GetLoadStringAssetReferences(AssetsType, References);

		if (References.Num() == 0)
		{
			UE_LOG(LogLoad, Warning, TEXT("ACsDataMapping::AsyncLoadAssets: Trying to load 0 assets."));
			return;
		}
		UCsManager_Loading::Get()->LoadAssetReferences<T>(Cast<UObject>(CallbackCaller)->GetWorld(), References, AsyncOrder, CallbackCaller, Callback);
	}

	virtual void OnFinishedAsyncLoadingAssetsSetReferences(const TCsLoadAssetsType &AssetsType, const TArray<UObject*> &LoadedAssets);

	ACsData* LoadData(const FName &ShortCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game);

	template<typename T>
	T* LoadData(const FString &FunctionName, const TCsAssetType &AssetType, const uint16 &LookUpCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		if (LookUpCode == INVALID_LOOK_UP_CODE_MAX)
			return nullptr;

		// Search Loaded Data TMaps / TArray
		if (ACsData* Data = GetLoadedData(AssetType, LookUpCode))
			return Data;

		TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(AssetType);
		const int32 Count					 = Mapping.Num();

		if (LookUpCode > Count)
		{
			UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load AssetType: %s. LookUpCode: %d does NOT exist."), *FunctionName, *((*AssetTypeToString)(AssetType)), LookUpCode);
			return nullptr;
		}

		// Load the Data
		if (T* DataDOb = LoadData_Internal<T>(FunctionName, AssetType, Mapping[LookUpCode]))
			return DataDOb;
		UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load AssetType: %s. LookUpCode: %d does NOT exist."), *FunctionName, *((*AssetTypeToString)(AssetType)), LookUpCode);
		return nullptr;
	}

	template<typename T>
	T* LoadData(const TCsAssetType &AssetType, const uint16 &LookUpCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		return LoadData<T>(TEXT("ACsDataMapping::LoadData"), AssetType, LookUpCode, LoadFlags);
	}

	template<typename T>
	T* LoadData(const FString &FunctionName, const TCsAssetType &AssetType, const uint8 &LookUpCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		if (LookUpCode == CS_INVALID_LOOK_UP_CODE)
			return nullptr;

		// Search Loaded Data TMaps / TArray
		if (ACsData* Data = GetLoadedData(AssetType, LookUpCode))
			return Data;

		TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(AssetType);
		const int32 Count					 = Mapping.Num();

		if (LookUpCode > Count)
		{
			UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load AssetType: %s. LookUpCode: %d does NOT exist."), *FunctionName, *((*AssetTypeToString)(AssetType)), LookUpCode);
			return nullptr;
		}

		// Load the Data
		if (T* DataDOb = LoadData_Internal<T>(FunctionName, AssetType, Mapping[LookUpCode]))
			return DataDOb;
		UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load AssetType: %s. LookUpCode: %d does NOT exist."), *FunctionName, *((*AssetTypeToString)(AssetType)), LookUpCode);
		return nullptr;
	}

	template<typename T>
	T* LoadData(const TCsAssetType &AssetType, const uint8 &LookUpCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		return LoadData<T>(TEXT("ACsDataMapping::LoadData"), AssetType, LookUpCode, LoadFlags);
	}

	template<typename T>
	T* LoadData(const FString &FunctionName, const TCsAssetType &AssetType, const FName &ShortCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		if (ShortCode == NAME_None)
			return nullptr;

		// Search Loaded Data TMaps
		if (ACsData* Data = GetLoadedData(AssetType, ShortCode))
			return Cast<T>(Data);

		// Search TMap
		TMap<FName, FCsDataMappingEntry>& Map = *GetDataMappings_Map(AssetType);

		if (FCsDataMappingEntry* Entry = Map.Find(ShortCode))
		{
			// Load the Data
			if (T* DataDOb = LoadData_Internal<T>(FunctionName, AssetType, *Entry, LoadFlags))
				return DataDOb;
		}

		// Search TArray
		TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(AssetType);
		const int32 Count					 = Mapping.Num();

		for (int32 Index = 0; Index < Count; Index++)
		{
			if (ShortCode != Mapping[Index].ShortCode)
				continue;

			// Load the Data
			if (T* DataDOb = LoadData_Internal<T>(FunctionName, AssetType, Mapping[Index], LoadFlags))
				return DataDOb;
		}
		UE_LOG(LogLoad, Warning, TEXT("%s: Trying to load AssetType: %s. ShortCode: %s does NOT exist."), *FunctionName, *((*AssetTypeToString)(AssetType)), *ShortCode.ToString());
		return nullptr;
	}

	template<typename T>
	T* LoadData(const TCsAssetType &AssetType, const FName &ShortCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		return LoadData<T>(TEXT("ACsDataMapping::LoadData"), AssetType, ShortCode, LoadFlags);
	}

	template<typename T>
	T* LoadData_Internal(const TCsAssetType &AssetType, FCsDataMappingEntry& Mapping, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		return LoadData_Internal<T>(TEXT("ACsDataMapping::LoadData"), AssetType, Mapping, LoadFlags);
	}

	template<typename T>
	T* LoadData_Internal(const FString &FunctionName, const TCsAssetType &AssetType, FCsDataMappingEntry& Mapping, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		// Load the Data
		ACsData* OutAsset;

		UCsCommon::LoadTAssetSubclassOf<ACsData>(Mapping.Data, OutAsset, TEXT("Actor"));

		T* DataDOb = Cast<T>(OutAsset);

		if (!DataDOb)
		{
			const FString ShortCode		   = Mapping.ShortCode.ToString();
			const FString AssetDescription = UCsCommon::GetAssetDescription<ACsData>(Mapping.Data);

			UE_LOG(LogLoad, Warning, TEXT("%s: Failed to load data using Short Code: %s with Path Location: %s"), *FunctionName, *ShortCode, *AssetDescription);
			return nullptr;
		}

		ACsData* Data = CastChecked<ACsData>(DataDOb);

		AddLoadedData(AssetType, Mapping.ShortCode, Data);
		Data->Load(LoadFlags);

		FString Name = Data->ShortCode == CS_INVALID_SHORT_CODE || Data->ShortCode == NAME_None ? Data->GetName() : Data->ShortCode.ToString();
		checkf(Data->IsValid(), TEXT("%s: Data: %s is NOT Valid"), *FunctionName, *Name);
		return DataDOb;
	}

	template<typename T>
	void LoadAllData(const FString &FunctionName, const TCsAssetType &AssetType, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game)
	{
		TArray<FCsDataMappingEntry>& Mapping = *GetDataMappings(AssetType);
		const int32 Count					 = Mapping.Num();

		for (int32 Index = 0; Index < Count; Index++)
		{
			LoadData<T>(FunctionName, AssetType, Mapping[Index], LoadFlags);
		}
	}

	// Add
#pragma region
public:

	virtual void AddLoadedData(const TCsAssetType &AssetType, const FName &ShortCode, ACsData* InData);
protected:
	template<typename T>
	void AddLoadData_Internal(TArray<FCsDataMappingEntry> &Datas, TMap<FName, T*> &Datas_Loaded_Map, TArray<T*> &Datas_Loaded, const FName &ShortCode, ACsData* InData)
	{
		const uint16 Count = Datas.Num();
		uint16 LookUpCode = CS_INVALID_LOOK_UP_CODE_MAX;

		for (uint16 I = 0; I < Count; I++)
		{
			if (Datas[I].ShortCode == ShortCode)
			{
				LookUpCode = I;
				break;
			}
		}

		Datas_Loaded_Map.Add(ShortCode, Cast<T>(InData));
		Datas_Loaded_Map.KeySort(TLess<FName>());

		if (Datas_Loaded.Num() == CS_EMPTY)
		{
			for (uint16 I = 0; I < Count; I++)
			{
				Datas_Loaded.Add(nullptr);
			}
		}
		Datas_Loaded[LookUpCode] = Cast<T>(InData);
	}
public:
	virtual void AddLoadedData(const TCsAssetType &AssetType, const uint16 &LookUpCode, ACsData* InData);
protected:
	template<typename T>
	void AddLoadData_Internal(TArray<FCsDataMappingEntry> &Datas, TMap<FName, T*> &Datas_Loaded_Map, TArray<T*> &Datas_Loaded, const uint16 &LookUpCode, ACsData* InData)
	{
		const FName ShortCode = Datas[LookUpCode].ShortCode;
		T** Data = Datas_Loaded_Map.Find(ShortCode);

		check(InData == *Data);

		Datas_Loaded_Map.Add(ShortCode, Cast<T>(InData));

		if (Datas_Loaded.Num() == CS_EMPTY)
		{
			const uint16 Count = Datas.Num();

			for (uint16 I = 0; I < Count; I++)
			{
				Datas_Loaded.Add(nullptr);
			}
		}
		Datas_Loaded[LookUpCode] = Cast<T>(InData);
	}

#pragma endregion Add

	// Get
#pragma region
public:

	virtual class ACsData* GetLoadedData(const TCsAssetType &AssetType, const FName &ShortCode);
protected:
	template<typename T, typename U>
	T* GetLoadedData_Internal(TArray<FCsDataMappingEntry> &Datas, TMap<FName, FCsDataMappingEntry> &Datas_Map, TMap<FName, U*> &Datas_Loaded_Map, TArray<U*> &Datas_Loaded, const FName &ShortCode)
	{
		U** Data = Datas_Loaded_Map.Find(ShortCode);

		if (Datas_Loaded.Num() == CS_EMPTY)
		{
			const uint16 Count = Datas.Num();

			for (uint16 I = 0; I < Count; I++)
			{
				Datas_Loaded.Add(nullptr);
			}
		}

		if (!Data)
			return nullptr;

		FCsDataMappingEntry* Entry = Datas_Map.Find(ShortCode);
		const uint16 LookUpCode	   = Entry->LookUpCode;
		Datas_Loaded[LookUpCode]   = *Data;

		return Cast<T>(*Data);
	}
public:
	virtual class ACsData* GetLoadedData(const FName &ShortCode, TCsAssetType &OutAssetType);
	virtual class ACsData* GetLoadedData(const FName &ShortCode);
	virtual class ACsData* GetLoadedData(const TCsAssetType &AssetType, const uint16 &LookUpCode);
protected:
	template<typename T, typename U>
	T* GetLoadedData_Internal(TArray<FCsDataMappingEntry> &Datas, TMap<FName, U*> &Datas_Loaded_Map, TArray<U*> &Datas_Loaded, const uint16 &LookUpCode)
	{
		const FName ShortCode = Datas[LookUpCode].ShortCode;
		U** Data			  = Datas_Loaded_Map.Find(ShortCode);

		if (Datas_Loaded.Num() == CS_EMPTY)
		{
			uint16 Count = Datas.Num();

			for (uint16 I = 0; I < Count; I++)
			{
				Datas_Loaded.Add(nullptr);
			}
		}
		Datas_Loaded[LookUpCode] = *Data;
		return Cast<T>(*Data);
	}

#pragma endregion Get

#pragma endregion Load

// IsValid
#pragma region
public:

	template<typename T>
	bool CheckDataIsValid(const FString &FunctionName, const TCsAssetType &AssetType, const FName &ShortCode, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game);

	template<typename T>
	bool CheckDataIsValid(const FString &FunctionName, const TCsAssetType &AssetType, FCsDataMappingEntry& Mapping, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game);

	template<typename T>
	bool CheckAllDataIsValid(const FString &FunctionName, const TCsAssetType &AssetType, const ECsLoadFlags &LoadFlags = ECsLoadFlags::Game);

#pragma endregion IsValid
	
// Get
#pragma region
public:

	FName GetShortCode(const TCsAssetType &AssetType, const uint16 &LookUpCode);

	uint16 GetLookUpCode(const TCsAssetType &AssetType, const FName &ShortCode);

#pragma endregion Get

// Json
#pragma region

	virtual void PostLoad() override;

	virtual FString GetAbsolutePath();

	TCsWriteObjectToJson_Internal WriteObjectToJson_Internal;
	TCsReadObjectFromJson_Internal ReadObjectFromJson_Internal;

	virtual void SaveToJson();

	bool HasLoadedFromJson;

	virtual void LoadFromJson();

#pragma endregion Json

// 99 Editor
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "99 Editor")
	FCsDataMappingFindEntry FindEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "99 Editor")
	FCsDataMappingAddEntry AddEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "99 Editor")
	FCsDataMappingRemoveEntry RemoveEntry;

#if WITH_EDITOR

	bool PerformFindEntry(const FName &ShortCode, TArray<FCsDataMappingEntry*> &OutEntries, TArray<TCsAssetType> &OutAssetTypes, TArray<int32> &OutIndices);
	bool PerformAddEntry(const FName &ShortCode, const TCsAssetType &AssetType, const int32 &LoadFlags, FString &OutMessage, FString &OutOutput);
	bool PerformAddEntry(const FName &ShortCode, const int32 &LoadFlags, FString &OutMessage, FString &OutOutput);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	bool CheckEntryExists(const FName &ShortCode, const TCsAssetType &AssetType, const TCsLoadFlags_Editor &LoadFlags, FString &OutMessage);

#endif // #if WITH_EDITOR

#pragma endregion 99 Editor
};