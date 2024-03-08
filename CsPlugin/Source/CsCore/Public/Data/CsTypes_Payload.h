// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Load
#include "Load/CsSoftObjectPath.h"
// DataTable
#include "Engine/DataTable.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Payload.generated.h"

// FCsPayload_Data
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_Data
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Data Object. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FName Name;

	/** Object that implements the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load", meta = (MustImplement = "/Script/CsCore.CsData"))
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Data_LoadFlags;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Data. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath Paths;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath PathsByGroup[(uint8)ECsObjectPathDependencyGroup::ECsObjectPathDependencyGroup_MAX];

	FCsPayload_Data() :
		Name(NAME_None),
		Data(),
		Paths()
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return Data.IsValid();
	}

	FORCEINLINE bool IsPopulated() const
	{
		return IsValid() && Name != NAME_None;
	}

	void Reset()
	{
		Name = NAME_None;
		Data.Reset();
		Paths.Reset();

		for (FCsTArraySoftObjectPath& Arr : PathsByGroup)
		{
			Arr.Reset();
		}
	}

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from Data and 
	*  store that in Paths.
	*/
	void Populate();

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_Data

// FCsPayload_ScriptData
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_ScriptData
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Data Object. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FName Name;

	/** Object that implements the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load", meta = (MustImplement = "/Script/CsCore.CsScriptData"))
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Data_LoadFlags;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Data. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath Paths;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath PathsByGroup[(uint8)ECsObjectPathDependencyGroup::ECsObjectPathDependencyGroup_MAX];

	FCsPayload_ScriptData() :
		Name(NAME_None),
		Data(),
		Paths()
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return Data.IsValid();
	}

	FORCEINLINE bool IsPopulated() const
	{
		return IsValid() && Name != NAME_None;
	}

	void Reset()
	{
		Name = NAME_None;
		Data.Reset();
		Paths.Reset();

		for (FCsTArraySoftObjectPath& Arr : PathsByGroup)
		{
			Arr.Reset();
		}
	}

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from Data and 
	*  store that in Paths.
	*/
	void Populate();

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_ScriptData

// FCsPayload_DataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_DataTable
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the DataTable */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TSoftObjectPtr<UDataTable> DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor DataTable_LoadFlags;

	/** Whether to store all rows or use specific row names of 
	    the DataTable to store ObjectPaths for in Paths. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	bool bAllRows;

	/** Specific row names of the DataTable to store ObjectPaths 
		for in Paths. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TSet<FName> Rows;

	/** All ObjectPaths and Resource Sizes (Memory Size) for DataTable. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath Paths;

	/** */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TMap<FName, FCsTArraySoftObjectPath> PathsByRowMap;

	FCsPayload_DataTable() :
		Name(NAME_None),
		DataTable(),
		bAllRows(false),
		Rows(),
		Paths(),
		PathsByRowMap()
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return DataTable.IsValid();
	}

	FORCEINLINE bool IsPopulated() const
	{
		return IsValid() && Name != NAME_None;
	}

	void Reset()
	{
		Name = NAME_None;
		DataTable.Reset();
		bAllRows = false;
		Rows.Reset();
		Paths.Reset();
		PathsByRowMap.Reset();
	}

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from DataTable and
	*  store that in Paths.
	*/
	void Populate();

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_DataTable

// FCsPayload
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bUpdateDataRootSetOnSave;

	/** List of all Payload information related to objects that
	    implement the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_Data> Datas;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsPayload_Data> DataMap;

	/** List of all Payload information related to objects that
	    implement the interface: ICsScriptData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_ScriptData> ScriptDatas;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsPayload_ScriptData> ScriptDataMap;

	/** List of all Payload information related to DataTables. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_DataTable> DataTables;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsPayload_DataTable> DataTableMap;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Datas and DataTables. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	FCsTArraySoftObjectPath Paths;

	FCsPayload() :
		Index(INDEX_NONE),
		bUpdateDataRootSetOnSave(true),
		Datas(),
		DataMap(),
		ScriptDatas(),
		ScriptDataMap(),
		DataTables(),
		DataTableMap(),
		Paths()
	{
	}

	FORCEINLINE FCsPayload& operator=(const FCsPayload& B)
	{
		bUpdateDataRootSetOnSave = B.bUpdateDataRootSetOnSave;
		Datas = B.Datas;
		DataMap = B.DataMap;
		ScriptDatas = B.ScriptDatas;
		ScriptDataMap = B.ScriptDataMap;
		DataTables = B.DataTables;
		DataTableMap = B.DataTableMap;
		Paths = B.Paths;
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
		Datas.Reset(Datas.Max());
		DataMap.Reset();
		ScriptDatas.Reset(ScriptDatas.Max());
		ScriptDataMap.Reset();
		DataTables.Reset();
		DataTableMap.Reset();
		Paths.Reset();
	}

	void Unload() {}

#if WITH_EDITOR

	/**
	*
	*/
	void BuildMaps()
	{
		// Datas
		DataMap.Reset();

		for (FCsPayload_Data& Data : Datas)
		{
			if (Data.IsPopulated())
				DataMap.Add(Data.Name, Data);
		}
		// ScriptDatas
		ScriptDataMap.Reset();

		for (FCsPayload_ScriptData& Data : ScriptDatas)
		{
			if (Data.IsPopulated())
				ScriptDataMap.Add(Data.Name, Data);
		}
		// DataTables
		DataTableMap.Reset();

		for (FCsPayload_DataTable& DataTable : DataTables)
		{
			if (DataTable.IsPopulated())
				DataTableMap.Add(DataTable.Name, DataTable);
		}
	}

	/**
	*
	*/
	void BuildFromMaps()
	{
		// Datas
		Datas.Reset(DataMap.Num());

		for (TPair<FName, FCsPayload_Data>& Pair : DataMap)
		{
			Datas.Add(Pair.Value);
		}
		// ScriptDatas
		ScriptDatas.Reset(ScriptDataMap.Num());

		for (TPair<FName, FCsPayload_ScriptData>& Pair : ScriptDataMap)
		{
			ScriptDatas.Add(Pair.Value);
		}
		// DataTables
		DataTables.Reset(DataTableMap.Num());

		for (TPair<FName, FCsPayload_DataTable>& Pair : DataTableMap)
		{
			DataTables.Add(Pair.Value);
		}
	}

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from Datas and
	*  DataTables and store that in Paths. This also calls Populate on each
	*  Data and DataTable.
	*/
	void Populate()
	{
		Paths.Reset();

		// Data
		for (TPair<FName, FCsPayload_Data>& Pair : DataMap)
		{
			FCsPayload_Data& Data = Pair.Value;

			Data.Populate();

			Paths.Append(Data.Paths);
		}
		// ScriptData
		for (TPair<FName, FCsPayload_ScriptData>& Pair : ScriptDataMap)
		{
			FCsPayload_ScriptData& Data = Pair.Value;

			Data.Populate();

			Paths.Append(Data.Paths);
		}
		// DataTable
		for (TPair<FName, FCsPayload_DataTable>& Pair : DataTableMap)
		{
			FCsPayload_DataTable& DataTable = Pair.Value;

			DataTable.Populate();

			Paths.Append(DataTable.Paths);
		}
	}

	/**
	*
	*
	* @param DataTableMap
	* @param AllRows
	*/
	void Append(TMap<FName, UDataTable*>& InDataTableMap, const bool& AllRows = false);

	/**
	* 
	*
	* @param Payload
	*/
	void Append(const FCsPayload& Payload);

	/**
	*
	*
	* @param PayloadMap
	*/
	void Append(const TMap<FName, FCsPayload>& PayloadMap);

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload