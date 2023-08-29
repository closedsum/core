// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
// Load
#include "Load/CsSoftObjectPath.h"
// DataTable
#include "Engine/DataTable.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_DataEntry.generated.h"

// DataEntryData
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FECsDataEntryData : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDataEntryData)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDataEntryData)

struct CSCORE_API EMCsDataEntryData : public TCsEnumStructMap<FECsDataEntryData, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDataEntryData, FECsDataEntryData, uint8)
};

class UObject;

namespace NCsDataEntryData
{
	typedef FECsDataEntryData Type;

	CSCORE_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion DataEntryData

// FCsDataEntry_Data
#pragma region

class UObject;
class UClass;

// NCsLoad::FGetObjectPaths
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsLoad, FGetObjectPaths)

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataEntry_Data : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category = DataTable)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bPopulateOnSave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (MustImplement = "/Script.CsCore.CsData"))
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UClass* Data_Class;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	FCsTArraySoftObjectPath Paths;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath PathsByGroup[(uint8)ECsObjectPathDependencyGroup::ECsObjectPathDependencyGroup_MAX];

	FCsDataEntry_Data() :
		Index(INDEX_NONE),
		Name(NAME_None),
		bPopulateOnSave(false),
		Data(),
		Data_Internal(nullptr),
		Data_Class(nullptr),
		Paths()
	{
	}

	FORCEINLINE FCsDataEntry_Data& operator=(const FCsDataEntry_Data& B)
	{
		Name = B.Name;
		bPopulateOnSave = B.bPopulateOnSave;
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		Data_Class = B.Data_Class;
		Paths = B.Paths;

		const int32 Count = (int32)ECsObjectPathDependencyGroup::ECsObjectPathDependencyGroup_MAX;

		for (int32 I = 0; I < Count; ++I)
		{
			PathsByGroup[I] = B.PathsByGroup[I];
		}
		return *this;
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Reset()
	{
		Data = nullptr;
		Data_Internal = nullptr;
		Data_Class = nullptr;
		ClearPaths();
	}

	void ClearPaths()
	{
		Paths.Reset();

		for (FCsTArraySoftObjectPath& Arr : PathsByGroup)
		{
			Arr.Reset();
		}
	}

	FORCEINLINE UObject* Get() { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get(){ return Cast<T>(Get()); }

	FORCEINLINE UObject* GetChecked(const FString& Context)
	{
		checkf(Data_Internal, TEXT("%s: Failed to load Data with Entry: %s @ Path: %s."), *Context, *(Name.ToString()), *(Data.ToSoftObjectPath().ToString()));

		return Data_Internal;
	}

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context)
	{
		checkf(Cast<T>(GetChecked(Context)), TEXT("%s: Failed to cast Object: %s with Class: %s to type: T."), *Context, *(Data_Internal->GetName()), *(Data_Class->GetName()));

		return Cast<T>(GetChecked(Context));
	}

	template<typename InterfaceType>
	FORCEINLINE InterfaceType* GetInterfaceChecked(const FString& Context)
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsDataEntry_Data::GetInterfaceChecked: InterfaceType must be Abstract.");

		checkf(Cast<InterfaceType>(GetChecked(Context)), TEXT("%s: Object: %s with Class: %s does NOT implement interface: InterfaceType."), *Context, *(Data_Internal->GetName()), *(Data_Class->GetName()));

		return Cast<InterfaceType>(GetChecked(Context));
	}

	FORCEINLINE UClass* GetClass() { return Data_Class; }

	void BuildFromPaths()
	{
		Paths.BuildFromPaths();

		for (FCsTArraySoftObjectPath& Arr : PathsByGroup)
		{
			Arr.BuildFromPaths();
		}
	}

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from Data and
	*  store that in Paths.
	*/
	void Populate();

	void Populate(const TSet<FSoftObjectPath>& PathSet, const TArray<TSet<FSoftObjectPath>>& PathSetsByGroup);

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_Data

// FCsDataEntry_DataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataEntry_DataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category = DataTable)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bPopulateOnSave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TSoftObjectPtr<UDataTable> DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 DataTable_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UDataTable* DataTable_Internal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bAllRows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TSet<FName> Rows;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	FCsTArraySoftObjectPath Paths;

	UPROPERTY(VisibleDefaultsOnly, Category = DataTable)
	FCsTArraySoftObjectPath PathsByGroup[(uint8)ECsObjectPathDependencyGroup::ECsObjectPathDependencyGroup_MAX];

	/** */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsTArraySoftObjectPath> PathsByRowMap;

	/** */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsTArraySoftObjectPathByGroup> PathsByGroupByRowMap;

	FCsDataEntry_DataTable() :
		Index(INDEX_NONE),
		Name(NAME_None),
		bPopulateOnSave(false),
		DataTable(),
		DataTable_Internal(nullptr),
		bAllRows(false),
		Rows(),
		Paths(),
		PathsByRowMap(),
		PathsByGroupByRowMap()
	{
	}

	FORCEINLINE FCsDataEntry_DataTable& operator=(const FCsDataEntry_DataTable& B)
	{
		Name = B.Name;
		bPopulateOnSave = B.bPopulateOnSave;
		DataTable = B.DataTable;
		DataTable_Internal = B.DataTable_Internal;
		bAllRows = B.bAllRows;
		Rows = B.Rows;
		Paths = B.Paths;
		PathsByRowMap = B.PathsByRowMap;
		return *this;
	}

	FORCEINLINE bool IsValid() const
	{
		return DataTable.IsValid();
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Reset()
	{
		DataTable = nullptr;
		DataTable_Internal = nullptr;
		bAllRows = false;
		Rows.Reset();
		ClearPaths();
	}

	void ClearPaths()
	{
		Paths.Reset();

		for (FCsTArraySoftObjectPath& Arr : PathsByGroup)
		{
			Arr.Reset();
		}

		PathsByRowMap.Reset();

		for (TPair<FName, FCsTArraySoftObjectPathByGroup>& Pair : PathsByGroupByRowMap)
		{
			Pair.Value.Reset();
		}
	}

	FORCEINLINE UDataTable* Get() { return DataTable_Internal; }

	FORCEINLINE UDataTable* GetChecked(const FString& Context)
	{
		checkf(DataTable_Internal, TEXT("%s: Failed to load DataTable with Entry: %s @ Path: %s."), *Context, *(Name.ToString()), *(DataTable.ToSoftObjectPath().ToString()));

		return DataTable_Internal;
	}

	void BuildFromPaths()
	{
		Paths.BuildFromPaths();

		for (FCsTArraySoftObjectPath& Arr : PathsByGroup)
		{
			Arr.BuildFromPaths();
		}

		for (TPair<FName, FCsTArraySoftObjectPath>& Pair : PathsByRowMap)
		{
			Pair.Value.BuildFromPaths();
		}

		for (TPair<FName, FCsTArraySoftObjectPathByGroup>& Pair : PathsByGroupByRowMap)
		{
			for (FCsTArraySoftObjectPath& Arr : Pair.Value.PathsByGroup)
			{
				Arr.BuildFromPaths();
			}
		}
	}

#if WITH_EDITOR

	void SetupRows(const TArray<FName>& RowNames)
	{
		for (const FName& RowName : RowNames)
		{
			PathsByRowMap.FindOrAdd(RowName);
			PathsByGroupByRowMap.FindOrAdd(RowName);
		}
	}

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from DataTable and
	*  store that in Paths.
	*/
	void Populate();

	void PopulateRow(const FName& RowName, const TSet<FSoftObjectPath>& PathSet, const TArray<TSet<FSoftObjectPath>>& PathSetsByGroup);

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_DataTable