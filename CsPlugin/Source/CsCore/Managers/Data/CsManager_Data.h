// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Load.h"
#include "CsManager_Data.generated.h"

class ICsGetManagerData;
class UDataTable;
class ICsData;
class UScriptStruct;

UCLASS(transient)
class CSCORE_API UCsManager_Data : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

	static UCsManager_Data* Get(UObject* InRoot = nullptr);
	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerData* Get_GetManagerData(UObject* InRoot);
	static ICsGetManagerData* GetSafe_GetManagerData(UObject* Object);

	static UCsManager_Data* GetSafe(UObject* Object);

public:

	static UCsManager_Data* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_Data* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Root Set
#pragma region
public:

	UPROPERTY()
	FCsDataRootSetContainer DataRootSet;

#pragma endregion Root Set

// Maps
#pragma region
public:

	// Data
#pragma region
protected:

	TMap<FName, FCsDataEntry_Data*> DataEntryMap;
	TMap<FSoftObjectPath, FCsDataEntry_Data*> DataEntryByPathMap;

#if WITH_EDITOR
	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Added;
#endif // #if WITH_EDITOR

	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Loaded;
	TMap<FSoftObjectPath, FCsDataEntry_Data*> DataEntryByPathMap_Loaded;

	TMap<FName, ICsData*> DataMap_Loaded;
	TMap<FSoftObjectPath, ICsData*> DataByPathMap_Loaded;

#pragma endregion Data

	// DataTable
#pragma region
protected:

	TMap<FName, FCsDataEntry_DataTable*> DataTableEntryMap;
	TMap<FSoftObjectPath, FCsDataEntry_DataTable*> DataTableEntryByPathMap;

#if WITH_EDITOR
	TMap<FName, FCsDataEntry_DataTable*> DataTableEntryMap_Added;
#endif // #if WITH_EDITOR

	TMap<FName, TMap<FName, FCsDataEntry_DataTable*>> DataTableEntryRowMap_Loaded;
	TMap<FSoftObjectPath, TMap<FName, FCsDataEntry_DataTable*>> DataTableEntryRowByPathMap_Loaded;

	TMap<FName, UDataTable*> DataTableMap_Loaded;
	TMap<FSoftObjectPath, UDataTable*> DataTableByPathMap_Loaded;
	TMap<FName, TMap<FName, uint8*>> DataTableRowMap_Loaded;
	TMap<FSoftObjectPath, TMap<FName, uint8*>> DataTableRowByPathMap_Loaded;

	void UpdateDataTableRowMap(const FName& TableName, const FName& RowName, uint8* RowPtr);

#pragma endregion DataTable

	// Payload
#pragma region
protected:

	TMap<FName, FCsPayload*> PayloadMap;
	TMap<FName, FCsPayload*> PayloadMap_Loaded;

#if WITH_EDITOR

	TMap<FName, FCsPayload*> PayloadMap_Added;

public:

	/**
	*
	*
	* @param PayloadName
	* @param Payload
	*/
	void AddPayload(const FName& PayloadName, const FCsPayload& Payload);

#endif // #if WITH_EDITOR

#pragma endregion Payload

public:

	/**
	*
	*/
	void GenerateMaps();

#pragma endregion Maps

// Load
#pragma region
public:

	/**
	* Load a payload by Name.
	*
	* @param PayloadName	Name of the payload to load
	*/
	void LoadPayload(const FName& PayloadName);

	// DataTable
#pragma region
public:

	/**
	* Load a DataTable by Name.
	*
	* @param TableName	Name of the DataTable to load.
	* return			DataTable that has been loaded.
	*/
	UDataTable* LoadDataTable(const FName& TableName);

	/**
	* Load a DataTable by SoftObjectPath.
	*
	* @param Path	Path of the DataTable to load.
	* return		DataTable that has been loaded.
	*/
	UDataTable* LoadDataTable(const FSoftObjectPath& Path);

	/**
	* Load the Row of a DataTable by the DataTable Name and Row Name.
	*
	* @param TableName
	* @param RowName
	* return			Pointer to the row.
	*/
	uint8* LoadDataTableRow(const FName& TableName, const FName& RowName);

	/**
	* Check whether the Row of a DataTable has been loaded.
	*
	* @param TableName
	* @param RowName
	* return			Whether the row is loaded or not.
	*/
	bool IsLoadedDataTableRow(const FName& TableName, const FName& RowName);

#pragma endregion DataTable

#pragma endregion Load

// Get
#pragma region
public:

	// DataTable
#pragma region
public:

	/**
	* Get a DataTable by Name. This assumes the DataTable is loaded.
	*
	* @param TableName
	* return			DataTable
	*/
	UDataTable* GetDataTable(const FName& TableName);

	/**
	* Get a DataTable by SoftObjectPath. This assumes the DataTable is loaded.
	*
	* @param Path
	* return		DataTable
	*/
	UDataTable* GetDataTable(const FSoftObjectPath& Path);

	/**
	* Get a DataTable by SoftObjectPtr. This assumes the DataTable is loaded.
	*
	* @param SoftObject
	* return				DataTable
	*/
	UDataTable* GetDataTable(const TSoftObjectPtr<UDataTable>& SoftObject);

	/**
	*
	*
	* @param TableName
	* @param RowName
	* return			Pointer to the row.
	*/
	uint8* GetDataTableRow(const FName& TableName, const FName& RowName);

	/**
	*
	*
	* @param Path
	* @param RowName
	* return			Pointer to the row.
	*/
	uint8* GetDataTableRow(const FSoftObjectPath& Path, const FName& RowName);

#pragma endregion DataTable

#pragma endregion Get
};