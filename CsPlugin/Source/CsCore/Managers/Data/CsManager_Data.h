// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Managers/Load/CsTypes_Streaming.h"

#include "CsManager_Data.generated.h"

// Structs
#pragma region

	// FCsPayload

struct CSCORE_API FCsResource_Payload : public TCsResourceContainer<FCsPayload>
{
};

struct CSCORE_API FCsManager_Payload: public TCsManager_ResourceValueType_Fixed<FCsPayload, FCsResource_Payload, 0>
{
};

	// FCsDataEntry_Data

struct CSCORE_API FCsResource_DataEntry_Data : public TCsResourceContainer<FCsDataEntry_Data>
{
};

struct CSCORE_API FCsManager_DataEntry_Data : public TCsManager_ResourceValueType_Fixed<FCsDataEntry_Data, FCsResource_DataEntry_Data, 0>
{
};

	// FCsDataEntry_DataTable

struct CSCORE_API FCsResource_DataEntry_DataTable : public TCsResourceContainer<FCsDataEntry_DataTable>
{
};

struct CSCORE_API FCsManager_DataEntry_DataTable : public TCsManager_ResourceValueType_Fixed<FCsDataEntry_DataTable, FCsResource_DataEntry_DataTable, 0>
{
};

#pragma endregion Structs

class ICsGetManagerData;
class UDataTable;
class ICsData;

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

	FCsManager_DataEntry_Data Manager_DataEntry_Data;

	TMap<FName, FCsDataEntry_Data*> DataEntryMap;
	TMap<FSoftObjectPath, FCsDataEntry_Data*> DataEntryByPathMap;

	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Added;

	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Loaded;
	TMap<FSoftObjectPath, FCsDataEntry_Data*> DataEntryByPathMap_Loaded;

	TMap<FName, ICsData*> DataMap_Loaded;
	TMap<FSoftObjectPath, ICsData*> DataByPathMap_Loaded;

#pragma endregion Data

	// DataTable
#pragma region
protected:

	FCsManager_DataEntry_DataTable Manager_DataEntry_DataTable;

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_DataTable*> DataTableEntryMap;
	/** <Path, Entry> */
	TMap<FSoftObjectPath, FCsDataEntry_DataTable*> DataTableEntryByPathMap;

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_DataTable*> DataTableEntryMap_Added;

	// Loaded

	/** <EntryName, <RowName, Entry>> */
	TMap<FName, TMap<FName, FCsDataEntry_DataTable*>> DataTableEntryRowMap_Loaded;
	/** <Path, <RowName, Entry>> */
	TMap<FSoftObjectPath, TMap<FName, FCsDataEntry_DataTable*>> DataTableEntryRowByPathMap_Loaded;

	/** <EntryName, DataTable> */
	TMap<FName, UDataTable*> DataTableMap_Loaded;
	/** <Path, DataTable> */
	TMap<FSoftObjectPath, UDataTable*> DataTableByPathMap_Loaded;
	/** <EntryName, <RowName, RowPtr>> */
	TMap<FName, TMap<FName, uint8*>> DataTableRowMap_Loaded;
	/** <Path, <RowName, RowPtr>> */
	TMap<FSoftObjectPath, TMap<FName, uint8*>> DataTableRowByPathMap_Loaded;

	/** <EntryName, Handles> */
	TMap<FName, TSet<FCsStreamableHandle>> DataTableHandleMap_Loaded;
	/** <EntryName, <RowName, Handles>> */
	TMap<FName, TMap<FName, TSet<FCsStreamableHandle>>> DataTableRowHandleMap_Loaded;

	void UpdateDataTableRowMap(const FName& TableName, const FName& RowName, uint8* RowPtr);

#pragma endregion DataTable

	// Payload
#pragma region
protected:

	FCsManager_Payload Manager_Payload;

	/** <PayloadName, Payload> */
	TMap<FName, FCsPayload*> PayloadMap;

	/** <PayloadName, Payload> */
	TMap<FName, FCsPayload*> PayloadMap_Added;

	/** <PayloadName, Payload> */
	TMap<FName, FCsPayload*> PayloadMap_Loaded;

	/** <PayloadName, Handles> */
	TMap<FName, TArray<FCsStreamableHandle>> PayloadHandleMap_Loaded;

public:

	/**
	* Add a Payload. This is for any payload that have not been 
	* recorded or cached before. The primarily use is for any payload
	* that is dynamically created or coming from a source that can't be 
	* cached.
	*
	* @param PayloadName
	* @param Payload
	*/
	void AddPayload(const FName& PayloadName, const FCsPayload& Payload);

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

	// DataTable
#pragma region
public:

	/**
	* Load a DataTable by Entry Name. This the Row Name
	* in the master DataTable List
	*
	* @param EntryName	Row Name in the master DataTable list.
	* return			DataTable that has been loaded.
	*/
	UDataTable* LoadDataTable(const FName& EntryName);

	/**
	* Load a DataTable by SoftObjectPath.
	*
	* @param Path	Path of the DataTable to load.
	* return		DataTable that has been loaded.
	*/
	UDataTable* LoadDataTable(const FSoftObjectPath& Path);

	/**
	* Load the Row of a DataTable by the DataTable's Entry Name
	* (Row Name in the master DataTable list) and Row Name.
	*
	* @param EntryName	Row Name in the master DataTable list.
	* @param RowName
	* return			Pointer to the row.
	*/
	uint8* LoadDataTableRow(const FName& EntryName, const FName& RowName);

	/**
	* Check whether the Row of a DataTable has been loaded.
	*
	* @param TableName	Row Name in the master DataTable list.
	* @param RowName
	* return			Whether the row is loaded or not.
	*/
	bool IsLoadedDataTableRow(const FName& TableName, const FName& RowName);

#pragma endregion DataTable

	// Payload
#pragma region
public:

	/**
	* Load a payload by Name.
	*
	* @param PayloadName	Name of the payload to load
	*/
	void LoadPayload(const FName& PayloadName);

	/**
	*  Delegate type
	*
	* @param WasSuccessful
	* @param PayloadName
	*/
	DECLARE_DELEGATE_TwoParams(FOnAsyncLoadPayloadComplete, bool /*WasSuccessful*/, const FName& /*PayloadName*/);

	FOnAsyncLoadPayloadComplete OnAsyncLoadPayloadCompleted_Event;

	/**
	*
	*
	* @param PayloadName
	* @param Delegate
	*/
	void AsyncLoadPayload(const FName& PayloadName, FOnAsyncLoadPayloadComplete Delegate);

private:

	TMap<FCsLoadHandle, FName> InProgressAsyncLoadPayloads;

	void OnFinishLoadObjectPaths_AsyncLoadPayload(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime);

#pragma endregion Payload

#pragma endregion Load

// Get
#pragma region
public:

	// DataTable
#pragma region
public:

	/**
	* Get a DataTable by the DataTable's Entry Name
	* (Row Name in the master DataTable list).
	* Check against the current loaded data tables.
	*
	* @param EntryName	Row Name in the master DataTable list.
	* return			DataTable
	*/
	UDataTable* GetDataTable(const FName& EntryName);

	/**
	* Get a DataTable by SoftObjectPath. 
	* Check against the current loaded data tables.
	*
	* @param Path
	* return		DataTable
	*/
	UDataTable* GetDataTable(const FSoftObjectPath& Path);

	/**
	* Get a DataTable by SoftObjectPtr.
	* Check against the current loaded data tables.
	*
	* @param SoftObject
	* return				DataTable
	*/
	UDataTable* GetDataTable(const TSoftObjectPtr<UDataTable>& SoftObject);

	/**
	* Get a DataTable by the DataTable's Entry Name
	* (Row Name in the master DataTable list).
	* Check against the current loaded data tables.
	*
	* @param Context	Calling context.
	* @param EntryName	Row Name in the master DataTable list.
	* return			DataTable
	*/
	UDataTable* GetDataTableChecked(const FString& Context, const FName& EntryName);

	/**
	* Get a pointer to the row in a data table by the data table's Entry Name
	* (Row Name in the master DataTable list) and Row Name.
	* Check against the current loaded data tables.
	*
	* @param EntryName	Row Name in the master DataTable list.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	uint8* GetDataTableRow(const FName& EntryName, const FName& RowName);

	template<typename RowStructType>
	RowStructType* GetDataTableRow(const FName& EntryName, const FName& RowName)
	{
		return reinterpret_cast<RowStructType*>(GetDataTableRow(EntryName, RowName));
	}

	/**
	* Get a pointer to the row in a data table by the data table's Path
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Path		Soft Path to the data table.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	uint8* GetDataTableRow(const FSoftObjectPath& Path, const FName& RowName);

	/**
	* Get a pointer to the row in a data table by the data table's Soft Object
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param SoftObject	Soft Object to the data table.
	* @param RowName	Row Name is retrieved data table.
	* return			Pointer to the row.
	*/
	uint8* GetDataTableRow(const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName);

		// Entry
#pragma region
public:

	/**
	*
	*
	* @param TableName
	* return
	*/
	const FCsDataEntry_DataTable* GetDataTableEntry(const FName& TableName);

#pragma endregion Entry

		// SoftObjectPath
#pragma region
public:

	/**
	*
	*
	* @param TableName
	* @param OutPaths
	*/
	void GetDataTableSoftObjectPaths(const FName& TableName, TArray<FSoftObjectPath>& OutPaths);

	/**
	*
	*
	* @param TableName
	* return			Number of SoftObjectPaths for the DataTable.
	*					INDEX_NONE for an invalid TableName
	*/
	int32 GetDataTableSoftObjectPathCount(const FName& TableName);

	/**
	*
	*
	* @param TableName
	* @param RowName
	* @param OutPaths
	*/
	void GetDataTableRowSoftObjectPaths(const FName& TableName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths);

	/**
	*
	*
	* @param TableName
	* @param RowName
	* return			Number of SoftObjectPaths for the DataTable.
	*					INDEX_NONE for an invalid TableName or RowName
	*/
	int32 GetDataTableRowSoftObjectPathCount(const FName& TableName, const FName& RowName);

#pragma endregion SoftObjectPath

#pragma endregion DataTable

	// Payload
#pragma region
public:

		// SoftObjectPath
#pragma region
public:

	/**
	*
	*
	* @param PayloadName
	* @param OutPaths
	*/
	void GetPayloadSoftObjectPaths(const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths);


	/**
	*
	*
	* @param PayloadName
	* return			Number of SoftObjectPaths for the PayloadName.
	*					INDEX_NONE for an invalid PayloadName.
	*/
	int32 GetPayloadSoftObjectPathCount(const FName& PayloadName);

#pragma endregion SoftObjectPath

#pragma endregion Payload

#pragma endregion Get
};