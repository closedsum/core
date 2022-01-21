// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Managers/Load/CsTypes_Streaming.h"
#include "Types/CsTypes_Map.h"
// Log
#include "Utility/CsLog.h"

#include "CsManager_Data.generated.h"

// Structs
#pragma region

	// FCsPayload

struct CSCORE_API FCsResource_Payload : public TCsResourceContainer<FCsPayload>
{
};

struct CSCORE_API FCsManager_Payload: public NCsResource::NManager::NValue::TFixed<FCsPayload, FCsResource_Payload, 0>
{
};

	// FCsDataEntry_Data

struct CSCORE_API FCsResource_DataEntry_Data : public TCsResourceContainer<FCsDataEntry_Data>
{
};

struct CSCORE_API FCsManager_DataEntry_Data : public NCsResource::NManager::NValue::TFixed<FCsDataEntry_Data, FCsResource_DataEntry_Data, 0>
{
};

	// FCsDataEntry_DataTable

struct CSCORE_API FCsResource_DataEntry_DataTable : public TCsResourceContainer<FCsDataEntry_DataTable>
{
};

struct CSCORE_API FCsManager_DataEntry_DataTable : public NCsResource::NManager::NValue::TFixed<FCsDataEntry_DataTable, FCsResource_DataEntry_DataTable, 0>
{
};

#pragma endregion Structs

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

#if WITH_EDITOR
	static UCsManager_Data* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Data* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);
	static void Shutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerData* Get_GetManagerData(const UObject* InRoot);
	static ICsGetManagerData* GetSafe_GetManagerData(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

	static UCsManager_Data* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

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

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_Data*> DataEntryMap;
	/** <Path, Entry> */
	TMap<FSoftObjectPath, FCsDataEntry_Data*> DataEntryByPathMap;

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Added;

	// Loaded

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Loaded;
	/** <Path, Entry> */
	TMap<FSoftObjectPath, FCsDataEntry_Data*> DataEntryByPathMap_Loaded;

	/** <EntryName, Data> */
	TMap<FName, ICsData*> DataMap_Loaded;
	/** <Path, Data> */
	TMap<FSoftObjectPath, ICsData*> DataByPathMap_Loaded;
	/** <EntryName, Data> */
	TMap<FName, UObject*> DataObjectMap_Loaded;
	/** <Path, Data> */
	TMap<FSoftObjectPath, UObject*> DataObjectByPathMap_Loaded;

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

	void UpdateDataTableRowMap(const FName& EntryName, const FName& RowName, uint8* RowPtr);

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

	// Data
#pragma region
public:

	/**
	*
	*
	* @param EntryName
	* return			
	*/
	ICsData* LoadData(const FName& EntryName);

	ICsData* LoadData(const FSoftObjectPath& Path);

	/**
	*
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE bool IsLoadedData(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::IsLoadedData: EntryName is None."));

		if (ICsData* Data = GetData(EntryName))
			return true;
		return false;
	}

#pragma endregion Data

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
	* @param EntryName	Row Name in the master DataTable list.
	* @param RowName
	* return			Whether the row is loaded or not.
	*/
	FORCEINLINE bool IsLoadedDataTableRow(const FName& EntryName, const FName& RowName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::IsLoadedDataTableRow: EntryName is None."));

		checkf(RowName != NAME_None, TEXT("UCsManager_Data::IsLoadedDataTableRow: RowName is None."));

		if (uint8* RowPtr = GetDataTableRow(EntryName, RowName))
			return true;
		return false;
	}

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
	* Delegate type
	*  This is a synchronous event (fired on the Game Thread).
	*
	* @param WasSuccessful
	* @param PayloadName
	*/
	DECLARE_DELEGATE_TwoParams(FOnAsyncLoadPayloadComplete, bool /*WasSuccessful*/, const FName& /*PayloadName*/);

	/** */
	FOnAsyncLoadPayloadComplete OnAsyncLoadPayloadCompleted_Event;

	/**
	*
	*
	* @param PayloadName
	* @param Delegate
	*/
	void AsyncLoadPayload(const FName& PayloadName, FOnAsyncLoadPayloadComplete Delegate);

	void SafeAsyncLoadPaylod(const FString& Context, const FName& PayloadName, FOnAsyncLoadPayloadComplete Delegate, void(*Log)(const FString&) = &FCsLog::Warning);

private:

	TMap<FCsLoadHandle, FName> InProgressAsyncLoadPayloads;

	void OnFinishLoadObjectPaths_AsyncLoadPayload(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime);

#pragma endregion Payload

#pragma endregion Load

// Get
#pragma region
public:

	// Data
#pragma region
public:

	/**
	* Get Data by the Data's Entry Name
    * (Row Name in the master Data list).
	*
	* @param EntryName	Row Name in the master Data list.
	* return			Data
	*/
	FORCEINLINE ICsData* GetData(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetData: EntryName: None is NOT Valid."));

		if (ICsData** DataPtr = DataMap_Loaded.Find(EntryName))
			return *DataPtr;
		return nullptr;
	}

	/**
	* Get Data by the Data's Entry Name
	* (Row Name in the master Data list).
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Data list.
	* return			Data
	*/
	FORCEINLINE ICsData* GetDataChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

		if (ICsData** DataPtr = DataMap_Loaded.Find(EntryName))
			return *DataPtr;

		checkf(0, TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString()));
		return nullptr;
	}

	/**
	* Safely get Data by the Data's Entry Name
	* (Row Name in the master Data list).
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Data list.
	* @param Log		(optional)
	* return			Data
	*/
	FORCEINLINE ICsData* GetSafeData(const FString& Context, const FName& EntryName, void(*Log)(const FString&) = &FCsLog::Warning)
	{
		if (EntryName == NAME_None)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: EntryName: None is NOT Valid."), *Context));
			return nullptr;
		}

		if (ICsData** DataPtr = DataMap_Loaded.Find(EntryName))
			return *DataPtr;

		if (Log)
			Log(FString::Printf(TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString())));
		return nullptr;
	}

	/**
	* Safely get Data by SoftObjectPath
	* (Row Name in the master Data list).
	*
	* @param Path	Soft path to a data.
	* return		Data
	*/
	FORCEINLINE ICsData* GetData(const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("UCsManager_Data::GetData: Path is NOT Valid."));

		if (ICsData** DataPtr = DataByPathMap_Loaded.Find(Path))
			return *DataPtr;
		return nullptr;
	}

	/**
	* Get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a data.
	* return			Data
	*/
	FORCEINLINE ICsData* GetDataChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

		if (ICsData** DataPtr = DataByPathMap_Loaded.Find(Path))
			return *DataPtr;

		checkf(0, TEXT("%s: Failed to find Data at Path: %s."), *Context, *(Path.ToString()));
		return nullptr;
	}

	/**
	* Safely get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a data.
	* @param Log		(optional)
	* return			Data
	*/
	FORCEINLINE ICsData* GetSafeData(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning)
	{
		if (!Path.IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (ICsData** DataPtr = DataByPathMap_Loaded.Find(Path))
			return *DataPtr;

		if (Log)
			Log(FString::Printf(TEXT("%s: Failed to find Data at Path: %s."), *Context, *(Path.ToString())));
		return nullptr;
	}

	/**
	* Get Data by the Data's Entry Name
	* (Row Name in the master Data list).
	*
	* @param EntryName	Row Name in the master Data list.
	* return			Data as UObject.
	*/
	FORCEINLINE UObject* GetDataObject(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataObject: EntryName: None is NOT Valid."));

		if (UObject** DataPtr = DataObjectMap_Loaded.Find(EntryName))
			return *DataPtr;
		return nullptr;
	}

	/**
	* Get Data by the Data's Entry Name
	* (Row Name in the master Data list).
	*
	* @param EntryName	Row Name in the master Data list.
	* return			Data
	*/
	template<typename T>
	FORCEINLINE T* GetDataObject(const FName& EntryName)
	{
		return Cast<T>(GetDataObject(EntryName));
	}

	/**
	* Get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Data list.
	* return			Data as UObject.
	*/
	FORCEINLINE UObject* GetDataObjectChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

		if (UObject** DataPtr = DataObjectMap_Loaded.Find(EntryName))
			return *DataPtr;

		checkf(0, TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString()));
		return nullptr;
	}

	/**
	* Get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Data list.
	* return			Data as UObject.
	*/
	template<typename T>
	FORCEINLINE T* GetDataObjectChecked(const FString& Context, const FName& EntryName)
	{
		checkf(GetDataObjectChecked(Context, EntryName), TEXT("%s: Failed to cast Object to type: T."), *Context);

		return Cast<T>(GetDataObjectChecked(Context, EntryName));
	}

	/**
	* Safely get a Data by SoftObjectPath.
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Data list.
	* @param Log		(optional)
	* return			Data as UObject.
	*/
	FORCEINLINE UObject* GetSafeDataObject(const FString& Context, const FName& EntryName, void(*Log)(const FString&) = &FCsLog::Warning)
	{
		if (EntryName == NAME_None)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: EntryName is None."), *Context));
			return nullptr;
		}

		if (UObject** DataPtr = DataObjectMap_Loaded.Find(EntryName))
			return *DataPtr;

		if (Log)
			Log(FString::Printf(TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString())));
		return nullptr;
	}

	/**
	* Get a Data by SoftObjectPath.
	*
	* @param Path	Soft path to a data.
	* return		Data
	*/
	FORCEINLINE UObject* GetDataObject(const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("UCsManager_Data::GetData: Path is NOT Valid."));

		if (UObject** DataPtr = DataObjectByPathMap_Loaded.Find(Path))
			return *DataPtr;
		return nullptr;
	}

	/**
	* Get a Data by SoftObjectPath.
	*
	* @param Path	Soft path to a data.
	* return		Data
	*/
	template<typename T>
	FORCEINLINE T* GetDataObject(const FSoftObjectPath& Path)
	{
		return Cast<T>(GetDataObject(Path));
	}

	/**
	* Get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a data.
	* return
	*/
	FORCEINLINE UObject* GetDataObjectChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

		if (UObject** DataPtr = DataObjectByPathMap_Loaded.Find(Path))
			return *DataPtr;

		checkf(0, TEXT("%s: Failed to find Data at Path: %s."), *Context, *(Path.ToString()));
		return nullptr;
	}

	/**
	* Get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a data.
	* return
	*/
	template<typename T>
	FORCEINLINE T* GetDataObjectChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		return Cast<T>(GetDataObjectChecked(Context, Path));
	}

	/**
	* Get a Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a data.
	* @param Log		(optional)
	* return
	*/
	FORCEINLINE UObject* GetSafeDataObject(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning)
	{
		if (!Path.IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (UObject** DataPtr = DataObjectByPathMap_Loaded.Find(Path))
			return *DataPtr;

		if (Log)
			Log(FString::Printf(TEXT("%s: Failed to find Data at Path: %s."), *Context, *(Path.ToString())));
		return nullptr;
	}

	// Entry
#pragma region
public:

	/**
	*
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE const FCsDataEntry_Data* GetDataEntry(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataEntry: EntryName: None is NOT Valid."));

		if (FCsDataEntry_Data** EntryPtr = DataEntryMap.Find(EntryName))
			return *EntryPtr;
		return nullptr;
	}

#pragma endregion Entry

	// SoftObjectPath
#pragma region
public:

	/**
	*
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE FSoftObjectPath GetDataSoftObjectPath(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPath: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
			return Entry->DataTable.ToSoftObjectPath();
		CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableSoftObjectPath: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return FSoftObjectPath();
	}

	/**
	*
	*
	* @param Context
	* @param EntryName
	* return
	*/
	FORCEINLINE FSoftObjectPath GetDataSoftObjectPathChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_Data* Entry = GetDataEntry(EntryName))
			return Entry->Data.ToSoftObjectPath();
		checkf(0, TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString()));
		return FSoftObjectPath();
	}

	/**
	*
	*
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void GetDataSoftObjectPaths(const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataSoftObjectPaths: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_Data* Entry = GetDataEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
#if !UE_BUILD_SHIPPING
		else
		{
			CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataSoftObjectPaths: Failed to find Data with EntryName: %s."), *(EntryName.ToString())));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	*
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void GetDataSoftObjectPathsChecked(const FString& Context, const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_Data* Entry = GetDataEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
#if !UE_BUILD_SHIPPING
		else
		{
			checkf(0, TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	*
	*
	* @param EntryName
	* return			Number of SoftObjectPaths for the Data.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 GetDataSoftObjectPathCount(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataSoftObjectPathCount: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_Data* Entry = GetDataEntry(EntryName))
			return Entry->Paths.Internal.Num();
		CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataSoftObjectPathCount: Failed to find Data with EntryName: %s."), *(EntryName.ToString())));
		return 0;
	}

	/**
	*
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Number of SoftObjectPaths for the Data.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 GetDataSoftObjectPathCountChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_Data* Entry = GetDataEntry(EntryName))
			return Entry->Paths.Internal.Num();
		checkf(0, TEXT("%s: Failed to find Data with EntryName: %s."), *Context, *(EntryName.ToString()));
		return 0;
	}

#pragma endregion SoftObjectPath

#pragma endregion Data

	// DataTable
#pragma region
public:

	/**
	* Get a DataTable by the DataTable's Entry Name
	* (Row Name in the master DataTable list).
	*
	* @param EntryName	Row Name in the master DataTable list.
	* return			DataTable
	*/
	FORCEINLINE UDataTable* GetDataTable(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTable: EntryName: None is NOT Valid."));

		if (UDataTable** TablePtr = DataTableMap_Loaded.Find(EntryName))
			return *TablePtr;
		return nullptr;
	}

	/**
	* Get a DataTable by the DataTable's Entry Name
	* (Row Name in the master DataTable list).
	* Check against the current loaded data tables.
	*
	* @param Context	Calling context.
	* @param EntryName	Row Name in the master DataTable list.
	* return			DataTable
	*/
	FORCEINLINE UDataTable* GetDataTableChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

		if (UDataTable** TablePtr = DataTableMap_Loaded.Find(EntryName))
			return *TablePtr;

		checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return nullptr;
	}

	/**
	* Get a DataTable by SoftObjectPath. 
	*
	* @param Path	Soft path to a data table.
	* return		DataTable
	*/
	FORCEINLINE UDataTable* GetDataTable(const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("UCsManager_Data::GetDataTable: Path is NOT Valid."));

		if (UDataTable** TablePtr = DataTableByPathMap_Loaded.Find(Path))
			return *TablePtr;
		return nullptr;
	}

	/**
	* Get a DataTable by SoftObjectPath.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a data table.
	* return			DataTable
	*/
	FORCEINLINE UDataTable* GetDataTableChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

		if (UDataTable** TablePtr = DataTableByPathMap_Loaded.Find(Path))
			return *TablePtr;

		checkf(0, TEXT("%s: Failed to find DataTable @ %s."), *(Path.ToString()));
		return nullptr;
	}

	/**
	* Get a DataTable by SoftObjectPtr.
	*
	* @param SoftObject
	* return				DataTable
	*/
	FORCEINLINE UDataTable* GetDataTable(const TSoftObjectPtr<UDataTable>& SoftObject)
	{
		return GetDataTable(SoftObject.ToSoftObjectPath());
	}

	/**
	* Get a DataTable by SoftObjectPtr.
	* Check against the current loaded data tables.
	*
	* @param Context		The calling context.
	* @param SoftObject		Soft Reference to a data table.
	* return				DataTable.
	*/
	FORCEINLINE UDataTable* GetDataTableChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject)
	{
		return GetDataTableChecked(Context, SoftObject.ToSoftObjectPath());
	}

	/**
	* Get a pointer to the row map for a data table by the data table's Path
	*
	* @param Path		Soft Path to the data table.
	* return			Pointer to the row map.
	*/
	FORCEINLINE const TMap<FName, uint8*>* GetDataTableRowMap(const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("UCsManager_Data::GetDataTableRow: Path is NOT Valid."));

		return DataTableRowByPathMap_Loaded.Find(Path);
	}

	/**
	* Get a pointer to the row map for a data table by the data table's Path
	*
	* @param SoftObject	Soft Reference to the data table.
	* return			Pointer to the row map.
	*/
	FORCEINLINE const TMap<FName, uint8*>* GetDataTableRowMap(const TSoftObjectPtr<UDataTable>& SoftObject)
	{
		return GetDataTableRowMap(SoftObject.ToSoftObjectPath());
	}

	/**
	* Get a pointer to the row in a data table by the data table's Entry Name
	* (Row Name in the master DataTable list) and Row Name.
	*
	* @param EntryName	Row Name in the master DataTable list.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRow(const FName& EntryName, const FName& RowName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableRow: EntryName: None is NOT Valid."));

		checkf(RowName != NAME_None, TEXT("UCsManager_Data::GetDataTableRow: RowName: None is NOT Valid."));

		if (TMap<FName, uint8*>* RowMapPtr = DataTableRowMap_Loaded.Find(EntryName))
		{
			if (uint8** RowPtr = RowMapPtr->Find(RowName))
			{
				return *RowPtr;
			}
		}
		return nullptr;
	}

	/**
	* Get a pointer to the row in a data table by the data table's Entry Name
	* (Row Name in the master DataTable list) and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master DataTable list.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRowChecked(const FString& Context, const FName& EntryName, const FName& RowName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);

		if (TMap<FName, uint8*>* RowMapPtr = DataTableRowMap_Loaded.Find(EntryName))
		{
			if (uint8** RowPtr = RowMapPtr->Find(RowName))
			{
				return *RowPtr;
			}
			checkf(0, TEXT("%s: Failed to find Row with RowName: %s from DataTable with EntryName: %s."), *Context, *(RowName.ToString()), *(EntryName.ToString()));
		}
		checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return nullptr;
	}

	template<typename RowStructType>
	FORCEINLINE RowStructType* GetDataTableRow(const FName& EntryName, const FName& RowName)
	{
		return reinterpret_cast<RowStructType*>(GetDataTableRow(EntryName, RowName));
	}

	/**
	* Get a pointer to the row in a data table by the data table's Path
	* and Row Name.
	*
	* @param Path		Soft Path to the data table.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRow(const FSoftObjectPath& Path, const FName& RowName)
	{
		checkf(Path.IsValid(), TEXT("UCsManager_Data::GetDataTableRow: Path is NOT Valid."));

		checkf(RowName != NAME_None, TEXT("UCsManager_Data::GetDataTableRow: RowName: None is NOT Valid."));

		if (TMap<FName, uint8*>* RowMapPtr = DataTableRowByPathMap_Loaded.Find(Path))
		{
			if (uint8** RowPtr = RowMapPtr->Find(RowName))
			{
				return *RowPtr;
			}
		}
		return nullptr;
	}

	/**
	* Get a pointer to the row in a data table by the data table's Path
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param Path		Soft Path to the data table.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRowChecked(const FString& Context, const FSoftObjectPath& Path, const FName& RowName)
	{
		checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);

		if (TMap<FName, uint8*>* RowMapPtr = DataTableRowByPathMap_Loaded.Find(Path))
		{
			if (uint8** RowPtr = RowMapPtr->Find(RowName))
			{
				return *RowPtr;
			}
			checkf(0, TEXT("%s: Failed to find Row with RowName: %s from DataTable @ Path: %s."), *Context, *(RowName.ToString()), *(Path.ToString()));
		}
		checkf(0, TEXT("%s: Failed to find DataTable with Path: %s."), *Context, *(Path.ToString()));
		return nullptr;
	}

	/**
	* Get a pointer to the row in a data table by the data table's Path
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param Path		Soft Path to the data table.
	* @param RowStruct	ScriptStruct associated with the row.
	* @param RowName	Row Name in the retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRowChecked(const FString& Context, const FSoftObjectPath& Path, const UScriptStruct* RowStruct, const FName& RowName)
	{
		checkf(RowStruct, TEXT("%s: RowStruct is NULL."), *Context);

	#if !UE_BUILD_SHIPPING
		UDataTable* DT = GetDataTableChecked(Context, Path);

		checkf(DT->GetRowStruct() == RowStruct, TEXT("%s: DataTable: %s Row Struct: %s != %s."), *Context, *(DT->GetRowStruct()->GetName()), *(RowStruct->GetName()));
	#endif // #if !UE_BUILD_SHIPPING

		return GetDataTableRowChecked(Context, Path, RowName);
	}

	/**
	* Get a pointer to the row in a data table by the data table's Soft Object
	* and Row Name.
	*
	* @param SoftObject	Soft Object to the data table.
	* @param RowName	Row Name is retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRow(const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName)
	{
		return GetDataTableRow(SoftObject.ToSoftObjectPath(), RowName);
	}

	/**
	* Get a pointer to the row in a data table by the data table's Soft Object
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param SoftObject	Soft Object to the data table.
	* @param RowName	Row Name is retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRowChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName)
	{
		return GetDataTableRowChecked(Context, SoftObject.ToSoftObjectPath(), RowName);
	}

	/**
	* Get a pointer to the row in a data table by the data table's Soft Object
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param SoftObject	Soft Object to the data table.
	* @param RowStruct	ScriptStruct associated with the row.
	* @param RowName	Row Name is retrieved data table.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetDataTableRowChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject, const UScriptStruct* RowStruct, const FName& RowName)
	{
		return GetDataTableRowChecked(Context, SoftObject.ToSoftObjectPath(), RowStruct, RowName);
	}

	/**
	* Get a pointer to the row in a data table by the data table's Soft Object
	* and Row Name.
	* Check against the current loaded data tables.
	*
	* @param Context	The calling context.
	* @param SoftObject	Soft Object to the data table.
	* @param RowName	Row Name is retrieved data table.
	* return			Pointer to the row.
	*/
	template<typename RowStructType>
	FORCEINLINE RowStructType* GetDataTableRowChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName)
	{
		RowStructType* Row = reinterpret_cast<RowStructType>(GetDataTableRowChecked(Context, SoftObject, RowStructType::StaticStruct(), RowName));

		checkf(Row, TEXT("%s: Failed in casting Row Pointer to RowStructType."), *Context);

		return Row;
	}

		// Entry
#pragma region
public:

	/**
	*
	*
	* @param TableName
	* return
	*/
	FORCEINLINE const FCsDataEntry_DataTable* GetDataTableEntry(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableEntry: EntryName: None is NOT Valid."));

		if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(EntryName))
			return *EntryPtr;
		return nullptr;
	}

#pragma endregion Entry

		// SoftObjectPath
#pragma region
public:

	/**
	*
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE FSoftObjectPath GetDataTableSoftObjectPath(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPath: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
			return Entry->DataTable.ToSoftObjectPath();
		CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableSoftObjectPath: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return FSoftObjectPath();
	}

	/**
	*
	*
	* @param Context
	* @param EntryName
	* return
	*/
	FORCEINLINE FSoftObjectPath GetDataTableSoftObjectPathChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
			return Entry->DataTable.ToSoftObjectPath();
		checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return FSoftObjectPath();
	}

	/**
	*
	*
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void GetDataTableSoftObjectPaths(const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPaths: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
#if !UE_BUILD_SHIPPING
		else
		{
			CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableSoftObjectPaths: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	*
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void GetDataTableSoftObjectPathsChecked(const FString& Context, const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
		else
		{
			checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		}
	}

	/**
	*
	*
	* @param EntryName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 GetDataTableSoftObjectPathCount(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPathCount: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
			return Entry->Paths.Internal.Num();
		CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableSoftObjectPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return 0;
	}

	/**
	*
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 GetDataTableSoftObjectPathCountChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
			return Entry->Paths.Internal.Num();
		checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return 0;
	}

	/**
	*
	*
	* @param EntryName
	* @param RowName
	* @param OutPaths
	*/
	FORCEINLINE void GetDataTableRowSoftObjectPaths(const FName& EntryName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: EntryName: None is NOT Valid."));

		checkf(RowName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: RowName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		{
			if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
			{
				OutPaths.Append(Paths->Internal);
			}
#if !UE_BUILD_SHIPPING
			else
			{
				CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *(EntryName.ToString()), *(RowName.ToString())));
			}
#endif // #if !UE_BUILD_SHIPPING
		}
#if !UE_BUILD_SHIPPING
		else
		{
			CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	*
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param RowName
	* @param OutPaths
	*/
	FORCEINLINE void GetDataTableRowSoftObjectPathsChecked(const FString& Context, const FName& EntryName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		{
			if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
			{
				OutPaths.Append(Paths->Internal);
			}
			else
			{
				checkf(0, TEXT("%s: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *Context, *(EntryName.ToString()), *(RowName.ToString()));
			}
		}
		else
		{
			checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		}
	}

	/**
	*
	*
	* @param EntryName
	* @param RowName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName or RowName
	*/
	FORCEINLINE int32 GetDataTableRowSoftObjectPathCount(const FName& EntryName, const FName& RowName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: EntryName: None is NOT Valid."));

		checkf(RowName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: RowName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		{
			if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
			{
				return Paths->Internal.Num();
			}
#if !UE_BUILD_SHIPPING
			else
			{
				CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *(EntryName.ToString()), *(RowName.ToString())));
			}
#endif // #if !UE_BUILD_SHIPPING
		}
#if !UE_BUILD_SHIPPING
		else
		{
			CS_LOG_WARNING(FString::Printf(TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		}
#endif // #if !UE_BUILD_SHIPPING
		return 0;
	}

	/**
	*
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param RowName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName or RowName
	*/
	FORCEINLINE int32 GetDataTableRowSoftObjectPathCountChecked(const FString& Context, const FName& EntryName, const FName& RowName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);

		if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		{
			if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
			{
				return Paths->Internal.Num();
			}
			else
			{
				checkf(0, TEXT("%s: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *Context, *(EntryName.ToString()), *(RowName.ToString()));
			}
		}
		else
		{
			checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		}
		return 0;
	}

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
	* @param Context		The calling context.
	* @param PayloadName
	* @param OutPaths
	*/
	void GetPayloadSoftObjectPathsChecked(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths);

	/**
	*
	*
	* @param Context		The calling context.
	* @param PayloadName
	* @param OutPaths
	* @param Log			(optional)
	*/
	void GetSafePayloadSoftObjectPaths(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths, void(*Log)(const FString&) = &FCsLog::Warning);

	/**
	*
	*
	* @param PayloadName
	* return			Number of SoftObjectPaths for the PayloadName.
	*					0 for an invalid PayloadName.
	*/
	int32 GetPayloadSoftObjectPathCount(const FName& PayloadName);

	/**
	*
	*
	* @param Context		The calling context.
	* @param PayloadName
	* return				Number of SoftObjectPaths for the PayloadName.
	*						0 for an invalid PayloadName.
	*/
	int32 GetPayloadSoftObjectPathCountChecked(const FString& Context, const FName& PayloadName);

	/**
	*
	*
	* @param Context		The calling context.
	* @param PayloadName
	* @param Log			(optional)
	* return				Number of SoftObjectPaths for the PayloadName.
	*						0 for an invalid PayloadName.
	*/
	int32 GetSafePayloadSoftObjectPathCount(const FString& Context, const FName& PayloadName, void(*Log)(const FString&) = &FCsLog::Warning);

#pragma endregion SoftObjectPath

#pragma endregion Payload

#pragma endregion Get

// Add
#pragma region
public:

	// TOOD: A bit of a HACK to keep Data UObject's constructed in script from being garbage collected

	UPROPERTY()
	TArray<UObject*> DataObjectsAdded_Loaded;

	UPROPERTY()
	TMap<FName, FCsMap_ObjectByName> DataCompositionObjectsAdded_Loaded;

	// Data
#pragma region
public:

	bool SafeAddData_Loaded(const FString& Context, const FName& EntryName, ICsData* Data, void(*Log)(const FString&) = &FCsLog::Warning);

	bool SafeAddDataObject_Loaded(const FString& Context, const FName& EntryName, UObject* Data, void(*Log)(const FString&) = &FCsLog::Warning);

	void AddDataCompositionObject_Loaded(const FName& DataName, UObject* Data, const FName& SliceName);

	bool SafeRemoveDataCompositionObject_Loaded(const FString& Context, const FName& DataName, void(*Log)(const FString&) = &FCsLog::Warning);

#pragma endregion Data

#pragma endregion Add
};