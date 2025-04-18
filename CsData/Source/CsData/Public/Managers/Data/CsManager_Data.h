// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Cached.h"
#include "Data/CsTypes_DataEntry.h"
#include "Data/CsTypes_Payload.h"
#include "Load/CsStreamableHandle.h"
#include "Types/CsTypes_Map.h"
#include "Load/CsObjectPathDependencyGroup.h"
#include "Managers/Data/CsManager_Data_Delegates.h"
// Container
#include "Data/CsDataRootSetContainer.h"
// Routine
#include "Coroutine/CsRoutineHandle.h"
// Load
#include "Load/CsLoadHandle.h"
// Log
#include "Utility/CsDataLog.h"

#include "CsManager_Data.generated.h"

// Structs
#pragma region

	// FCsPayload

struct CSDATA_API FCsResource_Payload : public TCsResourceContainer<FCsPayload>
{
	~FCsResource_Payload(){}
};

struct CSDATA_API FCsManager_Payload: public NCsResource::NManager::NValue::TFixed<FCsPayload, FCsResource_Payload, 0>
{
	~FCsManager_Payload(){}
};

	// FCsDataEntry_Data

struct CSDATA_API FCsResource_DataEntry_Data : public TCsResourceContainer<FCsDataEntry_Data>
{
	~FCsResource_DataEntry_Data(){}
};

struct CSDATA_API FCsManager_DataEntry_Data : public NCsResource::NManager::NValue::TFixed<FCsDataEntry_Data, FCsResource_DataEntry_Data, 0>
{
	~FCsManager_DataEntry_Data(){}
};

	// FCsDataEntry_ScriptData

struct CSDATA_API FCsResource_DataEntry_ScriptData : public TCsResourceContainer<FCsDataEntry_ScriptData>
{
	~FCsResource_DataEntry_ScriptData(){}
};

struct CSDATA_API FCsManager_DataEntry_ScriptData : public NCsResource::NManager::NValue::TFixed<FCsDataEntry_ScriptData, FCsResource_DataEntry_ScriptData, 0>
{
	~FCsManager_DataEntry_ScriptData(){}
};

	// FCsDataEntry_DataTable

struct CSDATA_API FCsResource_DataEntry_DataTable : public TCsResourceContainer<FCsDataEntry_DataTable>
{
	~FCsResource_DataEntry_DataTable(){}
};

struct CSDATA_API FCsManager_DataEntry_DataTable : public NCsResource::NManager::NValue::TFixed<FCsDataEntry_DataTable, FCsResource_DataEntry_DataTable, 0>
{
	~FCsManager_DataEntry_DataTable(){}
};

#pragma endregion Structs

class ICsGetManagerData;
class UDataTable;
class ICsData;
class UScriptStruct;

struct FCsRoutine;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsManager_Data)

UCLASS(transient)
class CSDATA_API UCsManager_Data : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsManager_Data);

	using OnAsyncLoadPayloadCompleteOnceType = NCsData::NManager::NOnce::FOnAsyncLoadPayloadComplete;
	using OnAsyncLoadPayloadsCompleteOnceType = NCsData::NManager::NOnce::FOnAsyncLoadPayloadsComplete;
	using OnAsyncLoadPayloadCompletePersistentType = NCsData::NManager::NPersistent::FOnAsyncLoadPayloadComplete;

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
	static bool HasShutdown(const UObject* InRoot = nullptr);
	static bool SafeHasShutdown(const FString& Context, const UObject* InRoot = nullptr, void(*Log)(const FString&) = nullptr);

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

	FORCEINLINE UObject* GetDataRootSetImplChecked(const FString& Context) const { return DataRootSet.GetObjectChecked(Context); }
	FORCEINLINE UObject* GetSafeDataRootSetImpl(const FString& Context, void(*Log)(const FString&) = &NCsData::FLog::Warning) const { return DataRootSet.GetSafeObject(Context, Log); }
	FORCEINLINE UObject* GetDataRootSetImpl() const { return DataRootSet.GetObject(); }

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

	// ScriptData
#pragma region
protected:

	FCsManager_DataEntry_ScriptData Manager_DataEntry_ScriptData;

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_ScriptData*> ScriptDataEntryMap;
	/** <Path, Entry> */
	TMap<FSoftObjectPath, FCsDataEntry_ScriptData*> ScriptDataEntryByPathMap;

	// Loaded

	/** <EntryName, Entry> */
	TMap<FName, FCsDataEntry_ScriptData*> ScriptDataEntryMap_Loaded;
	/** <Path, Entry> */
	TMap<FSoftObjectPath, FCsDataEntry_ScriptData*> ScriptDataEntryByPathMap_Loaded;

	/** <EntryName, Data> */
	TMap<FName, UObject*> ScriptDataMap_Loaded;
	/** <Path, Data> */
	TMap<FSoftObjectPath, UObject*> ScriptDataByPathMap_Loaded;
	/** <EntryName, Data> */
	TMap<FName, UObject*> ScriptDataObjectMap_Loaded;
	/** <Path, Data> */
	TMap<FSoftObjectPath, UObject*> ScriptDataObjectByPathMap_Loaded;

#pragma endregion ScriptData

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

	/** <PayloadName, Handle> */
	//TMap<FName, FCsRoutineHandle> AsyncLoadPayloadHandleByNameMap;

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

	bool DoesPayloadContain(const FName& PayloadName, const TSoftObjectPtr<UDataTable>& DataTable);

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

	// ScriptData
#pragma region
public:

	/**
	*
	*
	* @param EntryName
	* return			
	*/
	UObject* LoadScriptData(const FName& EntryName);

	UObject* LoadScriptData(const FSoftObjectPath& Path);

	/**
	*
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE bool IsLoadedScriptData(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::IsLoadedScriptData: EntryName is None."));

		if (UObject* Data = GetScriptDataObject(EntryName))
			return true;
		return false;
	}

#pragma endregion ScriptData

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
	* Load a Payload by Payload Name.
	*
	* @param PayloadName	Name of the payload to load
	*/
	void LoadPayload(const FName& PayloadName);

private:

	/** Event when a Payload loaded asynchronously completes.
		 This is a synchronous event (fired on the Game Thread). */
	OnAsyncLoadPayloadCompleteOnceType OnAsyncLoadPayloadCompleted_Once_Event;

	OnAsyncLoadPayloadsCompleteOnceType OnAsyncLoadPayloadsCompleted_Once_Event;

	OnAsyncLoadPayloadCompletePersistentType OnAsyncLoadPayloadCompleted_Persistent_Event;

public:

	FORCEINLINE OnAsyncLoadPayloadCompletePersistentType& GetOnAsyncLoadPayloadCompleted_Persistent_Event() { return OnAsyncLoadPayloadCompleted_Persistent_Event; }

	/**
	* Asynchronous load a Payload by Payload Name.
	*
	* @param PayloadName	Name of the Payload to async load.
	* @param Delegate		Delegate called synchronously (on the Game Thread) 
	*						when the async load completes.
	*/
	void AsyncLoadPayload(const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate);

	void SafeAsyncLoadPaylod(const FString& Context, const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate, void(*Log)(const FString&) = &NCsData::FLog::Warning);

	void AsyncLoadStartupPayload(OnAsyncLoadPayloadCompleteOnceType Delegate);

	bool SafeAsyncLoadStartupPaylod(const FString& Context, OnAsyncLoadPayloadCompleteOnceType Delegate, void(*Log)(const FString&) = &NCsData::FLog::Warning);

private:

	TMap<FCsLoadHandle, FName> InProgressAsyncLoadPayloads;

	void OnFinishLoadObjectPaths_AsyncLoadPayload(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime);

	// TODO: NOTE: This process can only be kicked off ONCE at a time.
	//			   Add checks.

	// List

	struct FAsyncLoadPayloads
	{
		friend class UCsManager_Data;

	public:

		struct FInfo
		{
		public:

			TArray<FName> PayloadNames;

			int32 Index;

			FInfo() :
				PayloadNames(),
				Index(INDEX_NONE)
			{
			}
		};
	};

	FAsyncLoadPayloads::FInfo AsyncLoadPayloadsInfo;

public:
	void AsyncLoadPayloads(const TArray<FName>& PayloadNames, OnAsyncLoadPayloadsCompleteOnceType Delegate);
private:
	char AsyncLoadPayloads_Internal(FCsRoutine* R);

	FCsRoutineHandle AsyncLoadPayloadsHandle;

	void OnFinishLoadObjectPaths_AsyncLoadPayloads(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime);

	// By Group

	struct FAsyncLoadPayloadByGroup
	{
		friend class UCsManager_Data;

	public:

		struct FInfo
		{
		public:

			FName PayloadName;

			int32 Index;

			FInfo() :
				PayloadName(NAME_None),
				Index(INDEX_NONE)
			{
			}
		};
	};

	FAsyncLoadPayloadByGroup::FInfo AsyncLoadPayloadByGroupInfo;

	void AsyncLoadPayloadByGroup(const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate);
	char AsyncLoadPayloadByGroup_Internal(FCsRoutine* R);

	FCsRoutineHandle AsyncLoadPayloadByGroupHandle;

	void OnFinishLoadObjectPaths_AsyncLoadPayloadByGroup(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime);

public:

	void UnloadPayload(const FName& PayloadName);

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
	FORCEINLINE ICsData* GetSafeData(const FString& Context, const FName& EntryName, void(*Log)(const FString&) = &NCsData::FLog::Warning)
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
	FORCEINLINE ICsData* GetSafeData(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &NCsData::FLog::Warning)
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
	FORCEINLINE UObject* GetSafeDataObject(const FString& Context, const FName& EntryName, void(*Log)(const FString&) = &NCsData::FLog::Warning)
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
	FORCEINLINE UObject* GetSafeDataObject(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &NCsData::FLog::Warning)
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
	* Get the Entry for the Data associated with EntryName.
	*
	* @param EntryName
	* return			Entry
	*/
	FORCEINLINE const FCsDataEntry_Data* Data_GetEntry(const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::Data_GetEntry: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_Data* const* EntryPtr = DataEntryMap.Find(EntryName))
			return *EntryPtr;
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::Data_GetEntry: Failed to find Data with EntryName: %s."), *(EntryName.ToString())));
		return nullptr;
	}

	/**
	* Get the Entry for the Data associated with EntryName.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Entry
	*/
	FORCEINLINE const FCsDataEntry_Data* Data_GetEntryChecked(const FString& Context, const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	#if !UE_BUILD_SHIPPING
		const FCsDataEntry_Data* Entry = DataEntryMap[EntryName];

		checkf(Entry, TEXT("%s: Failed find Data associated with EntryName: %s."), *Context, *(EntryName.ToString()));
		return Entry;
	#else
		return DataEntryMap[EntryName];
	#endif // #if !UE_BUILD_SHIPPING
	}

#pragma endregion Entry

	// SoftObjectPath
#pragma region
public:

	/**
	* Get the SoftObjectPath for the Data associated with Entry Name.
	*
	* @param EntryName
	* return			SoftObjectPath
	*/
	FORCEINLINE FSoftObjectPath Data_GetPath(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPath: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntry(EntryName))
			return Entry->DataTable.ToSoftObjectPath();
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::GetDataTableSoftObjectPath: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return FSoftObjectPath();
	}

	/**
	* Get the SoftObjectPath for the Data associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			SoftObjectPath
	*/
	FORCEINLINE const FSoftObjectPath& Data_GetPathChecked(const FString& Context, const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	#if !UE_BUILD_SHIPPING
		const FCsDataEntry_Data* Entry = Data_GetEntryChecked(Context, EntryName);

		checkf(Entry->Data.ToSoftObjectPath().IsValid(), TEXT("%s: Entry->Data is NOT Valid"), *Context);
		return Entry->Data.ToSoftObjectPath();
	#else
		return Data_GetEntryChecked(Context, EntryName)->Data.ToSoftObjectPath();
	#endif // !UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for Data associated with Entry Name.
	*
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void Data_GetPaths(const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::Data_GetPaths: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_Data* Entry = Data_GetEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
#if !UE_BUILD_SHIPPING
		else
		{
			NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::Data_GetPaths: Failed to find Data with EntryName: %s."), *(EntryName.ToString())));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for Data associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void Data_GetPathsChecked(const FString& Context, const FName& EntryName, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		OutPaths.Append(Data_GetEntryChecked(Context, EntryName)->Paths.Internal);
	}

	/**
	* Get the number of SoftObjectPaths for Data associated with Entry Name.
	*
	* @param EntryName
	* return			Number of SoftObjectPaths for the Data.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 Data_GetPathCount(const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::Data_GetPathCount: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_Data* Entry = Data_GetEntry(EntryName))
			return Entry->Paths.Internal.Num();
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::Data_GetPathCount: Failed to find Data with EntryName: %s."), *(EntryName.ToString())));
		return 0;
	}

	/**
	* Get the number of SoftObjectPaths for Data associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Number of SoftObjectPaths for the Data.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 Data_GetPathCountChecked(const FString& Context, const FName& EntryName) const
	{
		return Data_GetEntryChecked(Context, EntryName)->Paths.Internal.Num();
	}

	/**
	* Get the SoftObjectPaths for Data associated with Entry Name and dependency Group.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void Data_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const ECsObjectPathDependencyGroup& Group, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		OutPaths.Append(Data_GetEntryChecked(Context, EntryName)->PathsByGroup[(uint8)Group].Internal);
	}

	/**
	* Get the SoftObjectPaths for Data associated with Entry Name and dependency Group.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void Data_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const ECsObjectPathDependencyGroup& Group, TSet<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		OutPaths.Append(Data_GetEntryChecked(Context, EntryName)->PathsByGroup[(uint8)Group].InternalSet);
	}

#pragma endregion SoftObjectPath

#pragma endregion Data

	// ScriptData
#pragma region
public:

	/**
	* Get Script Data by the Data's Entry Name
	* (Row Name in the master Data list).
	*
	* @param EntryName	Row Name in the master Script Data list.
	* return			Script Data as UObject.
	*/
	FORCEINLINE UObject* GetScriptDataObject(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetScriptDataObject: EntryName: None is NOT Valid."));

		if (UObject** DataPtr = ScriptDataObjectMap_Loaded.Find(EntryName))
			return *DataPtr;
		return nullptr;
	}

	/**
	* Get a Script Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Script Data list.
	* return			Script Data as UObject.
	*/
	FORCEINLINE UObject* GetScriptDataObjectChecked(const FString& Context, const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

		if (UObject** DataPtr = ScriptDataObjectMap_Loaded.Find(EntryName))
			return *DataPtr;

		checkf(0, TEXT("%s: Failed to find Script Data with EntryName: %s."), *Context, *(EntryName.ToString()));
		return nullptr;
	}

	/**
	* Safely get a Script Data by SoftObjectPath.
	*
	* @param Context	The calling context.
	* @param EntryName	Row Name in the master Script Data list.
	* @param Log		(optional)
	* return			Script Data as UObject.
	*/
	FORCEINLINE UObject* GetSafeScriptDataObject(const FString& Context, const FName& EntryName, void(*Log)(const FString&) = &NCsData::FLog::Warning)
	{
		if (EntryName == NAME_None)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: EntryName is None."), *Context));
			return nullptr;
		}

		if (UObject** DataPtr = ScriptDataObjectMap_Loaded.Find(EntryName))
			return *DataPtr;

		if (Log)
			Log(FString::Printf(TEXT("%s: Failed to find Script Data with EntryName: %s."), *Context, *(EntryName.ToString())));
		return nullptr;
	}

	/**
	* Get a Script Data by SoftObjectPath.
	*
	* @param Path	Soft path to a Script Data.
	* return		Script Data
	*/
	FORCEINLINE UObject* GetScriptDataObject(const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("UCsManager_Data::GetScriptDataObject: Path is NOT Valid."));

		if (UObject** DataPtr = ScriptDataObjectByPathMap_Loaded.Find(Path))
			return *DataPtr;
		return nullptr;
	}

	/**
	* Get a Script Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a Script Data.
	* return
	*/
	FORCEINLINE UObject* GetScriptDataObjectChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

		if (UObject** DataPtr = ScriptDataObjectByPathMap_Loaded.Find(Path))
			return *DataPtr;

		checkf(0, TEXT("%s: Failed to find Script Data at Path: %s."), *Context, *(Path.ToString()));
		return nullptr;
	}

	/**
	* Get a Script Data by SoftObjectPath.
	* Check against the current loaded datas.
	*
	* @param Context	The calling context.
	* @param Path		Soft path to a Script Data.
	* @param Log		(optional)
	* return
	*/
	FORCEINLINE UObject* GetSafeScriptDataObject(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &NCsData::FLog::Warning)
	{
		if (!Path.IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (UObject** DataPtr = ScriptDataObjectByPathMap_Loaded.Find(Path))
			return *DataPtr;

		if (Log)
			Log(FString::Printf(TEXT("%s: Failed to find Script Data at Path: %s."), *Context, *(Path.ToString())));
		return nullptr;
	}

	// Entry
#pragma region
public:

	/**
	* Get the Entry for the Script Data associated with EntryName.
	*
	* @param EntryName
	* return			Entry
	*/
	FORCEINLINE const FCsDataEntry_ScriptData* ScriptData_GetEntry(const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::ScriptData_GetEntry: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_ScriptData* const* EntryPtr = ScriptDataEntryMap.Find(EntryName))
			return *EntryPtr;
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::ScriptData_GetEntry: Failed to find Script Data with EntryName: %s."), *(EntryName.ToString())));
		return nullptr;
	}

	/**
	* Get the Entry for the Script Data associated with EntryName.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Entry
	*/
	FORCEINLINE const FCsDataEntry_ScriptData* ScriptData_GetEntryChecked(const FString& Context, const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	#if !UE_BUILD_SHIPPING
		const FCsDataEntry_ScriptData* Entry = ScriptDataEntryMap[EntryName];

		checkf(Entry, TEXT("%s: Failed find Script Data associated with EntryName: %s."), *Context, *(EntryName.ToString()));
		return Entry;
	#else
		return ScriptDataEntryMap[EntryName];
	#endif // #if !UE_BUILD_SHIPPING
	}

#pragma endregion Entry

	// SoftObjectPath
#pragma region
public:

	/**
	* Get the SoftObjectPath for the Script Data associated with Entry Name.
	*
	* @param EntryName
	* return			SoftObjectPath
	*/
	FORCEINLINE FSoftObjectPath ScriptData_GetPath(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::ScriptData_GetPath: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_ScriptData* Entry = ScriptData_GetEntry(EntryName))
			return Entry->Data.ToSoftObjectPath();
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::ScriptData_GetPath: Failed to find Script Data with EntryName: %s."), *(EntryName.ToString())));
		return FSoftObjectPath();
	}

	/**
	* Get the SoftObjectPath for the Script Data associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			SoftObjectPath
	*/
	FORCEINLINE const FSoftObjectPath& ScriptData_GetPathChecked(const FString& Context, const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	#if !UE_BUILD_SHIPPING
		const FCsDataEntry_ScriptData* Entry = ScriptData_GetEntryChecked(Context, EntryName);

		checkf(Entry->Data.ToSoftObjectPath().IsValid(), TEXT("%s: Entry->Data is NOT Valid"), *Context);
		return Entry->Data.ToSoftObjectPath();
	#else
		return ScriptData_GetEntryChecked(Context, EntryName)->Data.ToSoftObjectPath();
	#endif // !UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for Script Data associated with Entry Name.
	*
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void ScriptData_GetPaths(const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::ScriptData_GetPaths: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_ScriptData* Entry = ScriptData_GetEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
	#if !UE_BUILD_SHIPPING
		else
		{
			NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::ScriptData_GetPaths: Failed to find Script Data with EntryName: %s."), *(EntryName.ToString())));
		}
	#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for Script Data associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void ScriptData_GetPathsChecked(const FString& Context, const FName& EntryName, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		OutPaths.Append(ScriptData_GetEntryChecked(Context, EntryName)->Paths.Internal);
	}

	/**
	* Get the number of SoftObjectPaths for Script Data associated with Entry Name.
	*
	* @param EntryName
	* return			Number of SoftObjectPaths for the Script Data.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 ScriptData_GetPathCount(const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::ScriptData_GetPathCount: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_ScriptData* Entry = ScriptData_GetEntry(EntryName))
			return Entry->Paths.Internal.Num();
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::ScriptData_GetPathCount: Failed to find Script Data with EntryName: %s."), *(EntryName.ToString())));
		return 0;
	}

	/**
	* Get the number of SoftObjectPaths for Data associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Number of SoftObjectPaths for the Data.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 ScriptData_GetPathCountChecked(const FString& Context, const FName& EntryName) const
	{
		return ScriptData_GetEntryChecked(Context, EntryName)->Paths.Internal.Num();
	}

	/**
	* Get the SoftObjectPaths for Script Data associated with Entry Name and dependency Group.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void ScriptData_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const ECsObjectPathDependencyGroup& Group, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		OutPaths.Append(ScriptData_GetEntryChecked(Context, EntryName)->PathsByGroup[(uint8)Group].Internal);
	}

	/**
	* Get the SoftObjectPaths for Script Data associated with Entry Name and dependency Group.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void ScriptData_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const ECsObjectPathDependencyGroup& Group, TSet<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

		OutPaths.Append(ScriptData_GetEntryChecked(Context, EntryName)->PathsByGroup[(uint8)Group].InternalSet);
	}

#pragma endregion SoftObjectPath

#pragma endregion ScriptData

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

	#if UE_BUILD_SHIPPING
		return DataTableMap_Loaded[EntryName];
	#else
		if (UDataTable** TablePtr = DataTableMap_Loaded.Find(EntryName))
			return *TablePtr;

		checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return nullptr;
	#endif // #if UE_BUILD_SHIPPING
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

	#if UE_BUILD_SHIPPING
		return DataTableByPathMap_Loaded[Path];
	#else
		if (UDataTable** TablePtr = DataTableByPathMap_Loaded.Find(Path))
			return *TablePtr;

		checkf(0, TEXT("%s: Failed to find DataTable @ %s."), *Context, *(Path.ToString()));
		return nullptr;
	#endif // #if UE_BUILD_SHIPPING
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

	#if UE_BUILD_SHIPPING
		return DataTableRowMap_Loaded[EntryName][RowName];
	#else
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
	#endif // #if UE_BUILD_SHIPPING
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

	#if UE_BUILD_SHIPPING
		return DataTableRowByPathMap_Loaded[Path][RowName];
	#else
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
	#endif // #if UE_BUILD_SHIPPING
	}

	/**
	* Safely get a pointer to the Row with name: Row Name in a DataTable associated with Path.
	*
	* @param Context	The calling context.
	* @param Path		Soft Path to the DataTable.
	* @param RowName	Row Name in the retrieved DataTable.
	* @param Log		(optional)
	* return			Pointer to the Row.
	*/
	FORCEINLINE uint8* GetSafeDataTableRow(const FString& Context, const FSoftObjectPath& Path, const FName& RowName, void(*Log)(const FString&) = &NCsData::FLog::Warning)
	{
		if (!Path.IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (RowName == NAME_None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: RowName: None is NOT Valid."), *Context));
			return nullptr;
		}

		if (TMap<FName, uint8*>* RowMapPtr = DataTableRowByPathMap_Loaded.Find(Path))
		{
			if (uint8** RowPtr = RowMapPtr->Find(RowName))
			{
				return *RowPtr;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Row for Path.RowName: %s.%s."), *Context, *(Path.ToString()), *(RowName.ToString())));
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

		checkf(DT->GetRowStruct() == RowStruct, TEXT("%s: DataTable: %s Row Struct: %s != %s."), *Context, *(DT->GetRowStruct()->GetName()), *(DT->GetRowStruct()->GetName()), *(RowStruct->GetName()));
	#endif // #if !UE_BUILD_SHIPPING
		return GetDataTableRowChecked(Context, Path, RowName);
	}

	/**
	* Get a pointer to the Row with name: Row Name in a DataTable associated with SoftObject.
	*
	* @param SoftObject	Soft Object to the DataTable.
	* @param RowName	Row Name is retrieved DataTable.
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
	* Safely get a pointer to the Row with name: Row Name in a DataTable associated with SoftObject.
	*
	* @param SoftObject	Soft Object to the DataTable.
	* @param RowName	Row Name is retrieved DataTable.
	* return			Pointer to the row.
	*/
	FORCEINLINE uint8* GetSafeDataTableRow(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName, void(*Log)(const FString&) = &NCsData::FLog::Warning)
	{
		return GetSafeDataTableRow(Context, SoftObject.ToSoftObjectPath(), RowName, Log);
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
	* Get the Entry for DataTable associated with EntryName.
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE const FCsDataEntry_DataTable* DataTable_GetEntry(const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::DataTable_GetEntry: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* const* EntryPtr = DataTableEntryMap.Find(EntryName))
			return *EntryPtr;
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_GetEntry: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return nullptr;
	}

	/**
	* Get the Entry for DataTable associated with EntryName.
	*
	* @param EntryName
	* return
	*/
	FORCEINLINE const FCsDataEntry_DataTable* DataTable_GetEntryChecked(const FString& Context, const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	#if UE_BUILD_SHIPPING
		return DataTableEntryMap[EntryName];
	#else
		const FCsDataEntry_DataTable* const* EntryPtr = DataTableEntryMap.Find(EntryName);

		checkf(EntryPtr, TEXT("%s: Failed find DataTable associated with EntryName: %s."), *Context, *(EntryName.ToString()));

		const FCsDataEntry_DataTable* Entry = *EntryPtr;

		checkf(Entry, TEXT("%s: Failed find DataTable associated with EntryName: %s."), *Context, *(EntryName.ToString()));
		return Entry;
	#endif // #if UE_BUILD_SHIPPING
	}

	FORCEINLINE FName DataTable_GetEntryNameChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject) const
	{
		const FSoftObjectPath& Path = SoftObject.ToSoftObjectPath();

		checkf(Path.IsValid(), TEXT("%s: SoftObject is NOT Valid."), *Context);

	#if WITH_EDITOR
		if (const FCsDataEntry_DataTable* const* EntryPtr = DataTableEntryByPathMap.Find(Path))
			return (*EntryPtr)->Name;
		checkf(0, TEXT("%s: Failed to find Entry Name associated with DataTable at Path: %s."), *Context, *(Path.ToString()));
		return NAME_None;
	#else
		return DataTableEntryByPathMap[Path]->Name;
	#endif // #if WITH_EDITOR
	}

#pragma endregion Entry

		// SoftObjectPath
#pragma region
public:

	/**
	* Get the SoftObjectPath for DataTable associated with Entry Name
	*
	* @param EntryName
	* return			SoftObjectPath
	*/
	FORCEINLINE FSoftObjectPath GetDataTableSoftObjectPath(const FName& EntryName)
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPath: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntry(EntryName))
			return Entry->DataTable.ToSoftObjectPath();
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::GetDataTableSoftObjectPath: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return FSoftObjectPath();
	}

	/**
	* Get the SoftObjectPath for DataTable associated with Entry Name
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			SoftObjectPath
	*/
	FORCEINLINE const FSoftObjectPath& DataTable_GetPathChecked(const FString& Context, const FName& EntryName) const
	{
	#if UE_BUILD_SHIPPING
		return DataTable_GetEntryChecked(Context, EntryName)->DataTable.ToSoftObjectPath();
	#else
		const FCsDataEntry_DataTable* Entry = DataTable_GetEntryChecked(Context, EntryName);
		const FSoftObjectPath& Path			= Entry->DataTable.ToSoftObjectPath();

		checkf(Path.IsValid(), TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return Path;
	#endif // #if UE_BUILD_SHIPPING
	}

	/**
	*
	*
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_GetPaths(const FName& EntryName, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::DataTable_GetPaths: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntry(EntryName))
		{
			OutPaths.Append(Entry->Paths.Internal);
		}
#if !UE_BUILD_SHIPPING
		else
		{
			NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_GetPaths: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for DataTable associated with Entry Name
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_GetPathsChecked(const FString& Context, const FName& EntryName, TArray<FSoftObjectPath>& OutPaths) const
	{
		OutPaths.Append(DataTable_GetEntryChecked(Context, EntryName)->Paths.Internal);
	}

	/**
	* Get the number of SoftObjectPaths for DataTable associated with Entry Name.
	*
	* @param EntryName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 DataTable_GetPathCount(const FName& EntryName) const
	{
		checkf(EntryName != NAME_None, TEXT("UCsManager_Data::DataTable_GetPathCount: EntryName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntry(EntryName))
			return Entry->Paths.Internal.Num();
		NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_GetPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		return 0;
	}

	/**
	* Get the number of SoftObjectPaths for DataTable associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName.
	*/
	FORCEINLINE int32 DataTable_GetPathCountChecked(const FString& Context, const FName& EntryName) const
	{
		int32 Count = DataTable_GetEntryChecked(Context, EntryName)->Paths.Internal.Num();
		checkf(Count > 0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
		return Count;
	}

	/**
	* Get the SoftObjectPaths for DataTable associated with Entry Name
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const ECsObjectPathDependencyGroup& Group, TArray<FSoftObjectPath>& OutPaths) const
	{
		OutPaths.Append(DataTable_GetEntryChecked(Context, EntryName)->PathsByGroup[(uint8)Group].Internal);
	}

	/**
	* Get the SoftObjectPaths for DataTable associated with Entry Name
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const ECsObjectPathDependencyGroup& Group, TSet<FSoftObjectPath>& OutPaths) const
	{
		OutPaths.Append(DataTable_GetEntryChecked(Context, EntryName)->PathsByGroup[(uint8)Group].InternalSet);
	}

	/**
	* Get the SoftObjectPaths for the DataTable Row associated with Entry Name and Row Name.
	*
	* @param EntryName
	* @param RowName
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_Row_GetPaths(const FName& EntryName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(RowName != NAME_None, TEXT("UCsManager_Data::DataTable_Row_GetPaths: RowName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntry(EntryName))
		{
			if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
			{
				OutPaths.Append(Paths->Internal);
			}
	#if !UE_BUILD_SHIPPING
			else
			{
				NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_Row_GetPaths: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *(EntryName.ToString()), *(RowName.ToString())));
			}
	#endif // #if !UE_BUILD_SHIPPING
		}
	#if !UE_BUILD_SHIPPING
		else
		{
			NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_Row_GetPaths: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		}
	#endif // #if !UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for the DataTable Row associated with Entry Name and Row Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param RowName
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_Row_GetPathsChecked(const FString& Context, const FName& EntryName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);

	#if UE_BUILD_SHIPPING
		OutPaths.Append(DataTable_GetEntryChecked(Context, EntryName)->PathsByRowMap[RowName].Internal);
	#else
		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntryChecked(Context, EntryName))
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
	#endif // #if UE_BUILD_SHIPPING
	}

	/**
	* Get the number of SoftObjectPaths for DataTable associated with Entry Name.
	*
	* @param EntryName
	* @param RowName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName or RowName
	*/
	FORCEINLINE int32 DataTable_Row_GetPathCount(const FName& EntryName, const FName& RowName) const
	{
		checkf(RowName != NAME_None, TEXT("UCsManager_Data::DataTable_Row_GetPathCount: RowName: None is NOT Valid."));

		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntry(EntryName))
		{
			if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
			{
				return Paths->Internal.Num();
			}
	#if !UE_BUILD_SHIPPING
			else
			{
				NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_Row_GetPathCount: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *(EntryName.ToString()), *(RowName.ToString())));
			}
	#endif // #if !UE_BUILD_SHIPPING
		}
	#if !UE_BUILD_SHIPPING
		else
		{
			NCsData::FLog::Warning(FString::Printf(TEXT("UCsManager_Data::DataTable_Row_GetPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString())));
		}
	#endif // #if !UE_BUILD_SHIPPING
		return 0;
	}

	/**
	* Get the number of SoftObjectPaths for DataTable associated with Entry Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param RowName
	* return			Number of SoftObjectPaths for the DataTable.
	*					0 for an invalid EntryName or RowName
	*/
	FORCEINLINE int32 DataTable_Row_GetPathCountChecked(const FString& Context, const FName& EntryName, const FName& RowName) const
	{
		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);

	#if UE_BUILD_SHIPPING
		return DataTable_GetEntryChecked(Context, EntryName)->PathsByRowMap[RowName].Internal.Num();
	#else
		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntryChecked(Context, EntryName))
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
	#endif // #if UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for the DataTable Row associated with Entry Name and Row Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param RowName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_Row_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const FName& RowName, const ECsObjectPathDependencyGroup& Group, TArray<FSoftObjectPath>& OutPaths) const
	{
		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);
		check(EMCsObjectPathDependencyGroup::Get().IsValidEnumChecked(Context, Group));

	#if UE_BUILD_SHIPPING
		OutPaths.Append(DataTable_GetEntryChecked(Context, EntryName)->PathsByGroupByRowMap[RowName].PathsByGroup[(uint8)Group].Internal);
	#else
		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntryChecked(Context, EntryName))
		{
			if (const FCsTArraySoftObjectPathByGroup* PathsByGroup = Entry->PathsByGroupByRowMap.Find(RowName))
			{
				OutPaths.Append(PathsByGroup->PathsByGroup[(uint8)Group].Internal);
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
	#endif // #if UE_BUILD_SHIPPING
	}

	/**
	* Get the SoftObjectPaths for the DataTable Row associated with Entry Name and Row Name.
	*
	* @param Context	The calling context.
	* @param EntryName
	* @param RowName
	* @param Group
	* @param OutPaths
	*/
	FORCEINLINE void DataTable_Row_GetPathsByGroupChecked(const FString& Context, const FName& EntryName, const FName& RowName, const ECsObjectPathDependencyGroup& Group, TSet<FSoftObjectPath>& OutPaths) const
	{
		checkf(RowName != NAME_None, TEXT("%s: RowName: None is NOT Valid."), *Context);
		check(EMCsObjectPathDependencyGroup::Get().IsValidEnumChecked(Context, Group));

	#if UE_BUILD_SHIPPING
		OutPaths.Append(DataTable_GetEntryChecked(Context, EntryName)->PathsByGroupByRowMap[RowName].PathsByGroup[(uint8)Group].InternalSet);
	#else
		if (const FCsDataEntry_DataTable* Entry = DataTable_GetEntryChecked(Context, EntryName))
		{
			if (const FCsTArraySoftObjectPathByGroup* PathsByGroup = Entry->PathsByGroupByRowMap.Find(RowName))
			{
				OutPaths.Append(PathsByGroup->PathsByGroup[(uint8)Group].InternalSet);
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
	#endif // #if UE_BUILD_SHIPPING
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
	* Get the SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param PayloadName
	* @param OutPaths
	*/
	void Payload_GetPaths(const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths) const;

	/**
	* Get the SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param Context		The calling context.
	* @param PayloadName
	* @param OutPaths
	*/
	void Payload_GetPathsChecked(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths) const;

	/**
	* Safely get the SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param Context		The calling context.
	* @param PayloadName
	* @param OutPaths
	* @param Log			(optional)
	*/
	void Payload_GetSafePaths(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths, void(*Log)(const FString&) = &NCsData::FLog::Warning) const;

	/**
	* Get the number of SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param PayloadName
	* return			Number of SoftObjectPaths for the PayloadName.
	*					0 for an invalid PayloadName.
	*/
	int32 Payload_GetPathCount(const FName& PayloadName) const;

	/**
	* Get the number of SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param Context		The calling context.
	* @param PayloadName
	* return				Number of SoftObjectPaths for the PayloadName.
	*						0 for an invalid PayloadName.
	*/
	int32 Payload_GetPathCountChecked(const FString& Context, const FName& PayloadName) const;

	/**
	* Safely get the number of SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param Context		The calling context.
	* @param PayloadName
	* @param Log			(optional)
	* return				Number of SoftObjectPaths for the PayloadName.
	*						0 for an invalid PayloadName.
	*/
	int32 Payload_GetSafePathCount(const FString& Context, const FName& PayloadName, void(*Log)(const FString&) = &NCsData::FLog::Warning);

	/**
	* Get the SoftObjectPaths for Payload associated with Payload Name.
	*
	* @param Context		The calling context.
	* @param PayloadName
	* @param Group
	* @param OutPaths
	*/
	void Payload_GetPathsByGroupChecked(const FString& Context, const FName& PayloadName, const ECsObjectPathDependencyGroup& Group, TArray<FSoftObjectPath>& OutPaths) const;

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

	bool SafeAddData_Loaded(const FString& Context, const FName& EntryName, ICsData* Data, void(*Log)(const FString&) = &NCsData::FLog::Warning);

	bool SafeAddDataObject_Loaded(const FString& Context, const FName& EntryName, UObject* Data, void(*Log)(const FString&) = &NCsData::FLog::Warning);

	void AddDataCompositionObject_Loaded(const FName& DataName, UObject* Data, const FName& SliceName);

	bool SafeRemoveDataCompositionObject_Loaded(const FString& Context, const FName& DataName, void(*Log)(const FString&) = &NCsData::FLog::Warning);

#pragma endregion Data

#pragma endregion Add
};