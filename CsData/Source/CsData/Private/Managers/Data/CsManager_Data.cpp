// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/CsManager_Data.h"
#include "CsData.h"

// CVar
#include "Managers/Data/CsCVars_Manager_Data.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Settings
#include "Settings/CsLibrary_DataSettings.h"
	// Common
#include "Library/Load/CsLibrary_Load.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/Data/CsSettings_Manager_Data.h"
// Coroutine
#include "Coroutine/CsRoutine.h"
// Data
#include "Data/CsGetDataRootSet.h"
#include "Data/CsScriptData.h"
// Managers
#include "Managers/Load/CsManager_Load.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Data/CsGetManagerData.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Data)

// Cached
#pragma region

namespace NCsManagerData
{
	namespace NCached
	{
		namespace Str
		{
			// Maps
				// DataTable
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, UpdateDataTableRowMap);
				// Payload
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, GenerateMaps);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AddPayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, DoesPayloadContain);
			// Load
				// Data
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadData);
				// ScriptData
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadScriptData);
				// DataTable
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadDataTableRow);
				// Payload
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadPayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadStartupPayload);
					// List
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayloads);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayloads_Internal);
					// By Group
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayloadByGroup);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayloadByGroup_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, Payload_GetPaths);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, Payload_GetPathCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, UnloadPayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AddDataCompositionObject_Loaded);
		}

		namespace Name
		{
			// Load
				// Payload
					// List
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Data, AsyncLoadPayloads_Internal);
					// By Group
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Data, AsyncLoadPayloadByGroup_Internal);
		}
	}
}

#pragma endregion

// static initializations
UCsManager_Data* UCsManager_Data::s_Instance;
bool UCsManager_Data::s_bShutdown = false;

UCsManager_Data::UCsManager_Data(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Singleton
		// Root
	MyRoot(nullptr),
	// Root Set
	DataRootSet(),
	// Maps
		// Data
	Manager_DataEntry_Data(),
	DataEntryMap(),
	DataEntryByPathMap(),
	DataEntryMap_Added(),
	DataEntryMap_Loaded(),
	DataEntryByPathMap_Loaded(),
	DataMap_Loaded(),
	DataByPathMap_Loaded(),
	DataObjectMap_Loaded(),
	DataObjectByPathMap_Loaded(),
		// ScriptData
	Manager_DataEntry_ScriptData(),
	ScriptDataEntryMap(),
	ScriptDataEntryByPathMap(),
	ScriptDataEntryMap_Loaded(),
	ScriptDataEntryByPathMap_Loaded(),
	ScriptDataMap_Loaded(),
	ScriptDataByPathMap_Loaded(),
	ScriptDataObjectMap_Loaded(),
	ScriptDataObjectByPathMap_Loaded(),
		// DataTable
	Manager_DataEntry_DataTable(),
	DataTableEntryMap(),
	DataTableEntryByPathMap(),
	DataTableEntryMap_Added(),
	DataTableEntryRowMap_Loaded(),
	DataTableEntryRowByPathMap_Loaded(),
	DataTableMap_Loaded(),
	DataTableByPathMap_Loaded(),
	DataTableRowMap_Loaded(),
	DataTableRowByPathMap_Loaded(),
	DataTableHandleMap_Loaded(),
	DataTableRowHandleMap_Loaded(),
		// Payload
	Manager_Payload(),
	PayloadMap(),
	PayloadMap_Added(),
	PayloadMap_Loaded(),
	PayloadHandleMap_Loaded(),
	// Load
		// Payload
	OnAsyncLoadPayloadCompleted_Once_Event(),
	OnAsyncLoadPayloadsCompleted_Once_Event(),
	OnAsyncLoadPayloadCompleted_Persistent_Event(),
	InProgressAsyncLoadPayloads(),
			// List
	AsyncLoadPayloadsInfo(),
	AsyncLoadPayloadsHandle(),
			// By Group
	AsyncLoadPayloadByGroupInfo(),
	AsyncLoadPayloadByGroupHandle(),
	// Add
	DataObjectsAdded_Loaded(),
	DataCompositionObjectsAdded_Loaded()
{
}

#define USING_NS_CACHED using namespace NCsManagerData::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerData::NCached; \
	const FString& Context = Str::__FunctionName
#define CoroutineSchedulerLibrary NCsCoroutine::NScheduler::FLibrary

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Data* UCsManager_Data::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerData(InRoot)->GetManager_Data();
}
#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Data::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerData* GetManagerData = Get_GetManagerData(InRoot);

	UCsManager_Data* Manager_Data = GetManagerData->GetManager_Data();

	if (!Manager_Data)
	{
		Manager_Data = NewObject<UCsManager_Data>(InRoot, UCsManager_Data::StaticClass(), TEXT("Manager_Data_Singleton"), RF_Transient | RF_Public);

		GetManagerData->SetManager_Data(Manager_Data);

		Manager_Data->SetMyRoot(InRoot);
		Manager_Data->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Data>(GetTransientPackage(), UCsManager_Data::StaticClass(), TEXT("Manager_Data_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Data::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerData* GetManagerData = Get_GetManagerData(InRoot);
	UCsManager_Data* Manager_Data     = GetManagerData->GetManager_Data();
	Manager_Data->CleanUp();
	Manager_Data->SetMyRoot(nullptr);

	GetManagerData->SetManager_Data(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->SetMyRoot(nullptr);
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Data::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerData(InRoot)->GetManager_Data() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Data::SafeHasShutdown(const FString& Context, const UObject* InRoot /*=nullptr*/, void(*Log)(const FString&) /*=nullptr*/)
{
#if WITH_EDITOR
	if (ICsGetManagerData* GetManager_Data = GetSafe_GetManagerData(Context, InRoot, Log))
		return GetManager_Data->GetManager_Data() == nullptr;
	return true;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerData* UCsManager_Data::Get_GetManagerData(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Data::Get_GetManagerData: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Data::Get_GetManagerData: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Data::Get_GetManagerData: Manager_Singleton is NULL."));

	ICsGetManagerData* GetManagerData = Cast<ICsGetManagerData>(Manager_Singleton);

	checkf(GetManagerData, TEXT("UCsManager_Data::Get_GetManagerData: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerData."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerData;
}

/*static*/ ICsGetManagerData* UCsManager_Data::GetSafe_GetManagerData(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetManagerData>(Manager_Singleton);
}

/*static*/ UCsManager_Data* UCsManager_Data::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerData* GetManagerData = GetSafe_GetManagerData(Context, InRoot, Log))
		return GetManagerData->GetManager_Data();
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Data::Initialize()
{
	// Get DataRootSet
	typedef NCsData::NSettings::FLibrary SettingsLibrary;

	TSoftClassPtr<UObject> SoftClass = SettingsLibrary::GetDataRootSet();
	const FSoftObjectPath& Path		 = SoftClass.ToSoftObjectPath();

	checkf(Path.IsValid(), TEXT("UCsManager_Data::Initialize: UCsDataSettings.DataRootSet is NOT Valid."));

	DataRootSet.Data = SoftClass;

	UClass* Class = SoftClass.LoadSynchronous();

	checkf(Class, TEXT("UCsManager_Data::Initialize: Failed to Load DataRootSet at %s."), *(Path.ToString()));

	DataRootSet.Data_Class	  = Class;
	DataRootSet.Data_Internal = DataRootSet.Data_Class->GetDefaultObject<UObject>();

	checkf(DataRootSet.Data_Internal, TEXT("UCsManager_Data::Initialize: Failed to get DefaultObject for Class: %s at Path: %s"), *(Class->GetName()), *(Path.ToString()));

	ICsGetDataRootSet* GetDataRootSet = Cast<ICsGetDataRootSet>(DataRootSet.Data_Internal);

	checkf(GetDataRootSet, TEXT("UCsManager_Data::Initialize: Class: %s does NOT implement the interface: ICsGetDataRootSet."), *(Class->GetName()));

	DataRootSet.Interface = GetDataRootSet;

	const FCsSettings_Manager_Data& Settings = FCsSettings_Manager_Data::Get();

	// Manager_Payload
	{
		checkf(Settings.PayloadPoolSize >= 4, TEXT("UCsManager_Data::Initialize: UCsDataSettings.Manager_Data.PayloadPoolSize is NOT >= 4."));

		Manager_Payload.CreatePool(Settings.PayloadPoolSize);

		const TArray<FCsResource_Payload*>& Pool = Manager_Payload.GetPool();

		for (FCsResource_Payload* Container : Pool)
		{
			FCsPayload* R	   = Container->Get();
			const int32& Index = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
	// Manager_DataEntry_Data
	{
		checkf(Settings.DataEntryDataPoolSize >= 4, TEXT("UCsManager_Data::Initialize: UCsDataSettings.Manager_Data.DataEntryDataPoolSize is NOT >= 4."));

		Manager_DataEntry_Data.CreatePool(Settings.DataEntryDataPoolSize);

		const TArray<FCsResource_DataEntry_Data*>& Pool = Manager_DataEntry_Data.GetPool();

		for (FCsResource_DataEntry_Data* Container : Pool)
		{
			FCsDataEntry_Data* R = Container->Get();
			const int32& Index   = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
	// Manager_DataEntry_DataTable
	{
		checkf(Settings.DataEntryDataTablePoolSize >= 4, TEXT("UCsManager_Data::Initialize: UCsDataSettings.Manager_Data.DataEntryDataTablePoolSize is NOT >= 4."));

		Manager_DataEntry_DataTable.CreatePool(Settings.DataEntryDataTablePoolSize);

		const TArray<FCsResource_DataEntry_DataTable*>& Pool = Manager_DataEntry_DataTable.GetPool();

		for (FCsResource_DataEntry_DataTable* Container : Pool)
		{
			FCsDataEntry_DataTable* R = Container->Get();
			const int32& Index		  = Container->GetIndex();
			R->SetIndex(Index);
		}
	}

	// TODO: Move this to Coroutine and Async

	GenerateMaps();
}

void UCsManager_Data::CleanUp()
{
	// Datas
	{
		for (TPair<FName, FCsDataEntry_Data*>& Pair : DataEntryMap)
		{
			Pair.Value->Unload();
		}

		Manager_DataEntry_Data.Shutdown();
		DataEntryMap.Reset();
		DataEntryByPathMap.Reset();
		DataEntryMap_Added.Reset();
		DataEntryMap_Loaded.Reset();
		DataEntryByPathMap_Loaded.Reset();
		DataMap_Loaded.Reset();
		DataByPathMap_Loaded.Reset();
		DataObjectMap_Loaded.Reset();
		DataObjectByPathMap_Loaded.Reset();
	}
	// ScriptDatas
	{
		for (TPair<FName, FCsDataEntry_ScriptData*>& Pair : ScriptDataEntryMap)
		{
			Pair.Value->Unload();
		}

		Manager_DataEntry_ScriptData.Shutdown();
		ScriptDataEntryMap.Reset();
		ScriptDataEntryByPathMap.Reset();
		ScriptDataEntryMap_Loaded.Reset();
		ScriptDataEntryByPathMap_Loaded.Reset();
		ScriptDataMap_Loaded.Reset();
		ScriptDataByPathMap_Loaded.Reset();
		ScriptDataObjectMap_Loaded.Reset();
		ScriptDataObjectByPathMap_Loaded.Reset();
	}
	// DataTables
	{
		for (TPair<FName, FCsDataEntry_DataTable*>& Pair : DataTableEntryMap)
		{
			Pair.Value->Unload();
		}

		Manager_DataEntry_DataTable.Shutdown();
		DataTableEntryMap.Reset();
		DataTableEntryByPathMap.Reset();
		DataTableEntryMap_Added.Reset();
		DataTableEntryRowMap_Loaded.Reset();
		DataTableEntryRowByPathMap_Loaded.Reset();
		DataTableMap_Loaded.Reset();
		DataTableByPathMap_Loaded.Reset();
		DataTableRowMap_Loaded.Reset();
		DataTableRowByPathMap_Loaded.Reset();
		DataTableHandleMap_Loaded.Reset();
		DataTableRowHandleMap_Loaded.Reset();
	}
	// Payloads
	{
		Manager_Payload.Shutdown();
		PayloadMap.Reset();
		PayloadMap_Added.Reset();
		PayloadMap_Loaded.Reset();
		PayloadHandleMap_Loaded.Reset();
	}

	DataObjectsAdded_Loaded.Reset();
	DataCompositionObjectsAdded_Loaded.Reset();

}

	// Root
#pragma region

void UCsManager_Data::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Maps
#pragma region

	// DataTable
#pragma region

void UCsManager_Data::UpdateDataTableRowMap(const FName& EntryName, const FName& RowName, uint8* RowPtr)
{
	SET_CONTEXT(UpdateDataTableRowMap);

	checkf(RowPtr, TEXT("%s: RowPtr is NULL for DataTable with EntryName: %s and Row: %s."), *Context, *(EntryName.ToString()), *(RowName.ToString()));

	FCsDataEntry_DataTable* Entry = DataTableEntryMap[EntryName];

	checkf(Entry, TEXT("%s: Entry has NOT been set for DataTable with EntryName: %s in DataTableEntryMap."), *Context, *(EntryName.ToString()));

	const FSoftObjectPath& Path = Entry->DataTable.ToSoftObjectPath();

	// DataTableEntryRowMap_Loaded
	{
		TMap<FName, FCsDataEntry_DataTable*>& Map = DataTableEntryRowMap_Loaded.FindOrAdd(EntryName);

		Map.Add(RowName, Entry);
	}
	// DataTableEntryRowByPathMap_Loaded
	{
		TMap<FName, FCsDataEntry_DataTable*>& Map = DataTableEntryRowByPathMap_Loaded.FindOrAdd(Path);

		Map.Add(RowName, Entry);
	}
	// DataTableRowMap_Loaded
	{
		TMap<FName, uint8*>& Map = DataTableRowMap_Loaded.FindOrAdd(EntryName);

		Map.Add(RowName, RowPtr);
	}
	// DataTableRowByPathMap_Loaded
	{
		TMap<FName, uint8*>& Map = DataTableRowByPathMap_Loaded.FindOrAdd(Path);

		Map.Add(RowName, RowPtr);
	}
}

#pragma endregion DataTable

	// Payload
#pragma region

void UCsManager_Data::AddPayload(const FName& PayloadName, const FCsPayload& Payload)
{
	SET_CONTEXT(AddPayload);

	CS_IS_NAME_NONE_CHECKED(PayloadName)

	if (PayloadMap_Added.Find(PayloadName))
		return;

	FCsPayload* P = Manager_Payload.AllocateResource();
	*P			  = Payload;

	PayloadMap_Added.Add(PayloadName, P);

	// TODO: Add checks

	// Datas
	for (FCsPayload_Data& Data : P->Datas)
	{
		const FName& Name = Data.Name;

		if (!DataEntryMap.Find(Name) &&
			!DataEntryMap_Added.Find(Name))
		{
		}
	}
	// DataTables
	for (const FCsPayload_DataTable& DataTable : Payload.DataTables)
	{
		const FName& Name = DataTable.Name;

		if (!DataTableEntryMap.Find(Name) &&
			!DataTableEntryMap_Added.Find(Name))
		{
		}
	}
}

bool UCsManager_Data::DoesPayloadContain(const FName& PayloadName, const TSoftObjectPtr<UDataTable>& DataTable)
{
	SET_CONTEXT(DoesPayloadContain);

	CS_IS_NAME_NONE_CHECKED(PayloadName)
	CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(DataTable, UDataTable)

	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
	{
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

		if (!PayloadPtr)
			return false;
	}

	const FCsPayload& Payload = **PayloadPtr;

	for (const FCsPayload_DataTable& DT : Payload.DataTables)
	{
		const FCsDataEntry_DataTable* const* EntryPtr = DataTableEntryMap.Find(DT.Name);

		if (EntryPtr)
		{
			const FCsDataEntry_DataTable& Entry = **EntryPtr;
			
			if (DataTable == Entry.DataTable)
				return true;
		}
	}
	return false;
}

#pragma endregion Payload

void UCsManager_Data::GenerateMaps() 
{
	SET_CONTEXT(GenerateMaps);

	// Datas
	if (UDataTable* Datas = DataRootSet.Get()->GetCsDataRootSet().Datas)
	{
		const UScriptStruct* ScriptStruct = Datas->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_Data::StaticStruct(), TEXT("%s: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_Data"), *Context, *(Datas->GetName()), *(ScriptStruct->GetName()));

		DataEntryMap.Reset();

		const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

		for (const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& RowName	  = Pair.Key;
			FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

			const FSoftObjectPath& Path = RowPtr->Data.ToSoftObjectPath();

			checkf(Path.IsValid(), TEXT("%s: Data at Row: %s for Datas: %s is NOT Valid."), *Context, *(RowName.ToString()), *(Datas->GetName()));

			RowPtr->BuildFromPaths();

			DataEntryMap.Add(RowName, RowPtr);
			DataEntryByPathMap.Add(Path, RowPtr);
		}
		NCsDataEntryData::PopulateEnumMapFromSettings(Context, MyRoot);
	}
//#if !UE_BUILD_SHIPPING
	// ScriptDatas
	if (UDataTable* ScriptDatas = DataRootSet.Get()->GetCsDataRootSet().ScriptDatas)
	{
		const UScriptStruct* ScriptStruct = ScriptDatas->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_ScriptData::StaticStruct(), TEXT("%s: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_ScriptData"), *Context, *(ScriptDatas->GetName()), *(ScriptStruct->GetName()));

		ScriptDataEntryMap.Reset();

		const TMap<FName, uint8*>& RowMap = ScriptDatas->GetRowMap();

		for (const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& RowName		    = Pair.Key;
			FCsDataEntry_ScriptData* RowPtr = reinterpret_cast<FCsDataEntry_ScriptData*>(Pair.Value);

			const FSoftObjectPath& Path = RowPtr->Data.ToSoftObjectPath();

			checkf(Path.IsValid(), TEXT("%s: Data at Row: %s for Datas: %s is NOT Valid."), *Context, *(RowName.ToString()), *(ScriptDatas->GetName()));

			RowPtr->BuildFromPaths();

			ScriptDataEntryMap.Add(RowName, RowPtr);
			ScriptDataEntryByPathMap.Add(Path, RowPtr);
		}
	}
//#endif // #if !UE_BUILD_SHIPPING
	// DataTables
	if (UDataTable* DataTables = DataRootSet.Get()->GetCsDataRootSet().DataTables)
	{
		const UScriptStruct* ScriptStruct = DataTables->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_DataTable::StaticStruct(), TEXT("%s: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_DataTable"), *Context, *(DataTables->GetName()), *(ScriptStruct->GetName()));

		DataTableEntryMap.Reset();

		const TMap<FName, uint8*>& RowMap = DataTables->GetRowMap();

		for(const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& RowName	       = Pair.Key;
			FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

			RowPtr->Name = RowName;

			const FSoftObjectPath& Path = RowPtr->DataTable.ToSoftObjectPath();

			checkf(Path.IsValid(), TEXT("%s: DataTable at Row: %s for DataTables: %s is NOT Valid."), *Context, *(RowName.ToString()), *(DataTables->GetName()));

			RowPtr->BuildFromPaths();

			DataTableEntryMap.Add(RowName, RowPtr);
			DataTableEntryByPathMap.Add(Path, RowPtr);
		}
	}
	// Payloads
	if (UDataTable* Payloads = DataRootSet.Get()->GetCsDataRootSet().Payloads)
	{
		const UScriptStruct* ScriptStruct = Payloads->GetRowStruct();

		checkf(ScriptStruct == FCsPayload::StaticStruct(), TEXT("%s: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsPayload"), *Context, *(Payloads->GetName()), *(ScriptStruct->GetName()));

		PayloadMap.Reset();

		const TMap<FName, uint8*>& RowMap = Payloads->GetRowMap();

		for (const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& RowName = Pair.Key;
			FCsPayload* RowPtr	 = reinterpret_cast<FCsPayload*>(Pair.Value);

			PayloadMap.Add(RowName, RowPtr);
		}
	}
}

#pragma endregion Maps

// Load
#pragma region

	// Data
#pragma region

ICsData* UCsManager_Data::LoadData(const FName& EntryName)
{
	SET_CONTEXT(LoadData);

	CS_IS_NAME_NONE_CHECKED(EntryName)

	if (ICsData* Data = GetData(EntryName))
		return Data;

	if (FCsDataEntry_Data** EntryPtr = DataEntryMap.Find(EntryName))
	{
		FCsDataEntry_Data* Entry = *EntryPtr;
	
		checkf(Entry->Name == EntryName, TEXT("%s: Mismatch between Entry->Name != EntryName (%s != %s)."), *Context, *(Entry->Name.ToString()), *(EntryName.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_Data::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UObject* O	  = Entry->GetChecked(Context);
		ICsData* Data = Entry->GetInterfaceChecked<ICsData>(Context);

		DataMap_Loaded.FindOrAdd(EntryName) = Data;
		DataByPathMap_Loaded.FindOrAdd(Entry->Data.ToSoftObjectPath()) = Data;
		DataObjectMap_Loaded.FindOrAdd(EntryName) = O;
		DataObjectByPathMap_Loaded.FindOrAdd(Entry->Data.ToSoftObjectPath()) = O;

		return Entry->Get<ICsData>();
	}
	checkf(0, TEXT("%s: Failed to find Data @ Entry: %s."), *Context, *(EntryName.ToString()));
	return nullptr;
}

ICsData* UCsManager_Data::LoadData(const FSoftObjectPath& Path)
{
	SET_CONTEXT(LoadData);

	CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Path)

	if (ICsData* Data = GetData(Path))
		return Data;

	if (FCsDataEntry_Data** EntryPtr = DataEntryByPathMap.Find(Path))
	{
		FCsDataEntry_Data* Entry = *EntryPtr;

		checkf(Entry->Data.ToSoftObjectPath() == Path, TEXT("%s: Mismatch between Entry's Path != Path (%s != %s)."), *Context, *(Entry->Data.ToSoftObjectPath().ToString()), *(Path.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_Data::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UObject* O	  = Entry->GetChecked(Context);
		ICsData* Data = Entry->GetInterfaceChecked<ICsData>(Context);

		DataMap_Loaded.FindOrAdd(Entry->Name) = Data;
		DataByPathMap_Loaded.FindOrAdd(Path) = Data;
		DataObjectMap_Loaded.FindOrAdd(Entry->Name) = O;
		DataObjectByPathMap_Loaded.FindOrAdd(Path) = O;

		return Entry->Get<ICsData>();
	}
	checkf(0, TEXT("%s: Failed to find Data @ Path: %s."), *Context, *(Path.ToString()));
	return nullptr;
}

#pragma endregion Data

	// ScriptData
#pragma region

UObject* UCsManager_Data::LoadScriptData(const FName& EntryName)
{
	SET_CONTEXT(LoadScriptData);

	CS_IS_NAME_NONE_CHECKED(EntryName)

	if (UObject* Data = GetScriptDataObject(EntryName))
		return Data;

	if (FCsDataEntry_ScriptData** EntryPtr = ScriptDataEntryMap.Find(EntryName))
	{
		FCsDataEntry_ScriptData* Entry = *EntryPtr;
	
		checkf(Entry->Name == EntryName, TEXT("%s: Mismatch between Entry->Name != EntryName (%s != %s)."), *Context, *(Entry->Name.ToString()), *(EntryName.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_ScriptData::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UObject* O = Entry->GetChecked(Context);

		ScriptDataMap_Loaded.FindOrAdd(EntryName) = O;
		ScriptDataByPathMap_Loaded.FindOrAdd(Entry->Data.ToSoftObjectPath()) = O;
		ScriptDataObjectMap_Loaded.FindOrAdd(EntryName) = O;
		ScriptDataObjectByPathMap_Loaded.FindOrAdd(Entry->Data.ToSoftObjectPath()) = O;

		return O;
	}
	checkf(0, TEXT("%s: Failed to find Script Data @ Entry: %s."), *Context, *(EntryName.ToString()));
	return nullptr;
}

UObject* UCsManager_Data::LoadScriptData(const FSoftObjectPath& Path)
{
	SET_CONTEXT(LoadScriptData);

	CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Path)

	if (UObject* Data = GetScriptDataObject(Path))
		return Data;

	if (FCsDataEntry_ScriptData** EntryPtr = ScriptDataEntryByPathMap.Find(Path))
	{
		FCsDataEntry_ScriptData* Entry = *EntryPtr;

		checkf(Entry->Data.ToSoftObjectPath() == Path, TEXT("%s: Mismatch between Entry's Path != Path (%s != %s)."), *Context, *(Entry->Data.ToSoftObjectPath().ToString()), *(Path.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_ScriptData::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UObject* O = Entry->GetChecked(Context);

		ScriptDataMap_Loaded.FindOrAdd(Entry->Name) = O;
		ScriptDataByPathMap_Loaded.FindOrAdd(Path) = O;
		ScriptDataObjectMap_Loaded.FindOrAdd(Entry->Name) = O;
		ScriptDataObjectByPathMap_Loaded.FindOrAdd(Path) = O;

		return O;
	}
	checkf(0, TEXT("%s: Failed to find Script Data @ Path: %s."), *Context, *(Path.ToString()));
	return nullptr;
}

#pragma endregion ScriptData

	// DataTable
#pragma region

UDataTable* UCsManager_Data::LoadDataTable(const FName& EntryName)
{
	SET_CONTEXT(LoadDataTable);

	CS_IS_NAME_NONE_CHECKED(EntryName)

	if (UDataTable* Table = GetDataTable(EntryName))
		return Table;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(EntryName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		checkf(Entry->Name == EntryName, TEXT("%s: Mismatch between Entry->Name != EntryName (%s != %s)."), *Context, *(Entry->Name.ToString()), *(EntryName.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UDataTable* DataTable = Entry->GetChecked(Context);

		DataTableMap_Loaded.FindOrAdd(EntryName) = DataTable;
		DataTableByPathMap_Loaded.FindOrAdd(Entry->DataTable.ToSoftObjectPath()) = DataTable;

		return Entry->Get();
	}
	checkf(0, TEXT("%s: Failed to find DataTable @ Entry: %s."), *Context, *(EntryName.ToString()));
	return nullptr;
}

UDataTable* UCsManager_Data::LoadDataTable(const FSoftObjectPath& Path)
{
	SET_CONTEXT(LoadDataTable);

	CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Path)

	if (UDataTable* Table = GetDataTable(Path))
		return Table;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryByPathMap.Find(Path))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		checkf(Entry->DataTable.ToSoftObjectPath() == Path, TEXT("%s: Mismatch between Entry's Path != Path (%s != %s)."), *Context, *(Entry->DataTable.ToSoftObjectPath().ToString()), *(Path.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UDataTable* DataTable = Entry->GetChecked(Context);

		DataTableMap_Loaded.FindOrAdd(Entry->Name) = DataTable;
		DataTableByPathMap_Loaded.FindOrAdd(Path) = DataTable;

		return Entry->Get();
	}
	checkf(0, TEXT("%s: Failed to find DataTable @ Path: %s."), *Context, *(Path.ToString()));
	return nullptr;
}

uint8* UCsManager_Data::LoadDataTableRow(const FName& EntryName, const FName& RowName)
{
	SET_CONTEXT(LoadDataTableRow);

	CS_IS_NAME_NONE_CHECKED(EntryName)
	CS_IS_NAME_NONE_CHECKED(RowName)

	// Check if DataTable and Row are already loaded
	if (uint8* RowPtr = GetDataTableRow(EntryName, RowName))
		return RowPtr;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(EntryName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		// If DataTable is NOT loaded, load it
		if (!Entry->Get())
			LoadDataTable(EntryName);

		UDataTable* DT = Entry->GetChecked(Context);

		const UScriptStruct* ScriptStruct = DT->GetRowStruct();
		UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
		UStruct* const Struct			  = Temp;

		if (uint8* RowPtr = DT->FindRowUnchecked(RowName))
		{
			UCsLibrary_Load::LoadStruct(RowPtr, Struct, NCsLoadFlags::All, NCsLoadCodes::None);
			UpdateDataTableRowMap(EntryName, RowName, RowPtr);

			return RowPtr;
		}
	}
	checkf(0, TEXT("%s: Failed to load DataTable @ Entry: %s and Row: %s."), *Context, *(EntryName.ToString()), *(RowName.ToString()));
	return nullptr;
}

#pragma endregion DataTable

	// Payload
#pragma region

void UCsManager_Data::LoadPayload(const FName& PayloadName)
{
	SET_CONTEXT(LoadPayload);

	CS_IS_NAME_NONE_CHECKED(PayloadName)

	// Check if the Payload has already been loaded
	if (PayloadMap_Loaded.Find(PayloadName))
		return;

	// Find the Payload by PayloadName
	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);
	
	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	FCsPayload* Payload = PayloadPtr ? *PayloadPtr : nullptr;

	if (Payload)
	{
		// Datas
		for (FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			// Load the Data
			const FName& EntryName = Payload_Data.Name;

			ICsData* Data = LoadData(EntryName);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			// Load the Script Data
			const FName& EntryName = Payload_ScriptData.Name;

			UObject* Data = LoadScriptData(EntryName);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			// Load the DataTable
			const FName& EntryName = Payload_DataTable.Name;

			UDataTable* DT = LoadDataTable(EntryName);

			// Load the appropriate Rows from the DataTable
			const UScriptStruct* ScriptStruct = DT->GetRowStruct();
			UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
			UStruct* const Struct			  = Temp;

			TArray<FName> RowNames;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				RowNames = DT->GetRowNames();
			}
			// Specified Rows
			else
			{
				RowNames = Payload_DataTable.Rows.Array();
			}

			for (const FName& RowName : RowNames)
			{
				if (IsLoadedDataTableRow(EntryName, RowName))
					continue;

				if (uint8* RowPtr = DT->FindRowUnchecked(RowName))
				{
					UCsLibrary_Load::LoadStruct(RowPtr, Struct, NCsLoadFlags::All, NCsLoadCodes::None);

					UpdateDataTableRowMap(EntryName, RowName, RowPtr);
				}
				else
				{
					checkf(0, TEXT("%s: Failed to Row: %s for DataTable with EntryName: %s."), *Context, *(RowName.ToString()), *(EntryName.ToString()));
				}
			}
		}

		PayloadMap_Loaded.Add(PayloadName, Payload);
	}
	else
	{
		checkf(0, TEXT("%s: Failed to find Payload: %s."), *Context, *(PayloadName.ToString()));
	}
}

#define OnAsyncLoadPayloadCompleteOnceType NCsData::NManager::NOnce::FOnAsyncLoadPayloadComplete

void UCsManager_Data::AsyncLoadPayload(const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate)
{
	SET_CONTEXT(AsyncLoadPayload);

	const FCsSettings_Manager_Data& Settings = FCsSettings_Manager_Data::Get();

	if (Settings.bLoadbyDependencyGroup)
	{
		AsyncLoadPayloadByGroup(PayloadName, Delegate);
	}
	else
	{
		const int32 Count = Payload_GetPathCountChecked(Context, PayloadName);
	
		if (Count <= CS_EMPTY)
		{
			UE_LOG(LogCsData, Warning, TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString()));

			OnAsyncLoadPayloadCompleted_Once_Event.ExecuteIfBound(false, PayloadName);
			OnAsyncLoadPayloadCompleted_Once_Event.Unbind();
			return;
		}

		TArray<FCsStreamableHandle>& Handles = PayloadHandleMap_Loaded.FindOrAdd(PayloadName);
		Handles.Reset(Handles.Max());

		typedef NCsLoad::NManager::NLoadObjectPaths::FPayload PayloadType;

		PayloadType Payload;

		// Set ObjectPaths
		Payload.ObjectPaths.Reset(Count);

		Payload_GetPathsChecked(Context, PayloadName, Payload.ObjectPaths);
		// Set Async Order
		Payload.AsyncOrder = EMCsLoadAsyncOrder::Get().GetEnumAt(CsCVarManagerDataLoadAsyncOrder->GetInt());
		// Set callback On Finish
		Payload.OnFinishLoadObjectPaths.BindUObject(this, &UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayload);

		FCsLoadHandle Handle = UCsManager_Load::Get(MyRoot)->LoadObjectPaths(Payload);

		InProgressAsyncLoadPayloads.Add(Handle, PayloadName);
	
		OnAsyncLoadPayloadCompleted_Once_Event = Delegate;
	}
}

void UCsManager_Data::SafeAsyncLoadPaylod(const FString& Context, const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate, void(*Log)(const FString&) /*= &NCsData::FLog::Warning*/)
{
	const int32 Count = Payload_GetSafePathCount(Context, PayloadName, Log);

	if (Count <= CS_EMPTY)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString())));

		OnAsyncLoadPayloadCompleted_Once_Event.ExecuteIfBound(false, PayloadName);
		OnAsyncLoadPayloadCompleted_Once_Event.Unbind();
		return;
	}

	// TODO: Add bSafe to Payload
	typedef NCsLoad::NManager::NLoadObjectPaths::FPayload PayloadType;

	PayloadType Payload;

	// Set ObjectPaths
	Payload.ObjectPaths.Reset(Count);

	Payload_GetSafePaths(Context, PayloadName, Payload.ObjectPaths, Log);

	if (Payload.ObjectPaths.Num() == CS_EMPTY)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString())));

		OnAsyncLoadPayloadCompleted_Once_Event.ExecuteIfBound(false, PayloadName);
		OnAsyncLoadPayloadCompleted_Once_Event.Unbind();
		return;
	}
	// Set Async Order
	Payload.AsyncOrder = EMCsLoadAsyncOrder::Get().GetEnumAt(CsCVarManagerDataLoadAsyncOrder->GetInt());
	// Set callback On Finish
	Payload.OnFinishLoadObjectPaths.BindUObject(this, &UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayload);

	FCsLoadHandle Handle = UCsManager_Load::Get(MyRoot)->LoadObjectPaths(Payload);

	InProgressAsyncLoadPayloads.Add(Handle, PayloadName);

	OnAsyncLoadPayloadCompleted_Once_Event = Delegate;
}

void UCsManager_Data::AsyncLoadStartupPayload(OnAsyncLoadPayloadCompleteOnceType Delegate)
{
	SET_CONTEXT(AsyncLoadStartupPayload);

	UObject* DataRootSetObject	      = DataRootSet.GetObjectChecked(Context);
	ICsGetDataRootSet* GetDataRootSet = DataRootSet.GetChecked(Context);
	const FCsDataRootSet& RootSet	  = GetDataRootSet->GetCsDataRootSet();
	const FName& PayloadName		  = RootSet.StartupPayload;

	checkf(PayloadName != NAME_None, TEXT("%s: %s->GetCsDataRootSet().StartupPayload: None is NOT Valid."), *Context, *(DataRootSetObject->GetName()));

	AsyncLoadPayload(PayloadName, Delegate);
}

bool UCsManager_Data::SafeAsyncLoadStartupPaylod(const FString& Context, OnAsyncLoadPayloadCompleteOnceType Delegate, void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/)
{
	UObject* DataRootSetObject = DataRootSet.GetSafeObject(Context, Log);

	if (!DataRootSetObject)
		return false;

	ICsGetDataRootSet* GetDataRootSet = DataRootSet.GetSafe(Context, Log);

	if (!GetDataRootSet)
		return false;

	const FCsDataRootSet& RootSet = GetDataRootSet->GetCsDataRootSet();

	const FName& PayloadName = RootSet.StartupPayload;

	if (PayloadName == NAME_None)
	{
		UE_LOG(LogCsData, Warning, TEXT("%s: %s->GetCsDataRootSet().StartupPayload: None is NOT Valid."), *Context, *(DataRootSetObject->GetName()));
		return false;
	}

	AsyncLoadPayload(PayloadName, Delegate);
	return true;
}

void UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayload(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime)
{
	const FName& PayloadName = InProgressAsyncLoadPayloads[Handle];

	// TODO: Add option to make this Async
	LoadPayload(PayloadName);

	for (const TSharedPtr<FStreamableHandle>& H : Handles)
	{
		PayloadHandleMap_Loaded[PayloadName].AddDefaulted_GetRef().Init(H);
	}

	OnAsyncLoadPayloadCompleted_Once_Event.ExecuteIfBound(true, PayloadName);
	OnAsyncLoadPayloadCompleted_Persistent_Event.Broadcast(true, PayloadName);

	InProgressAsyncLoadPayloads.Remove(Handle);

	OnAsyncLoadPayloadCompleted_Once_Event.Unbind();
}

		// List
#pragma region

#define OnAsyncLoadPayloadsCompleteOnceType NCsData::NManager::NOnce::FOnAsyncLoadPayloadsComplete

void UCsManager_Data::AsyncLoadPayloads(const TArray<FName>& PayloadNames, OnAsyncLoadPayloadsCompleteOnceType Delegate)
{
	SET_CONTEXT(AsyncLoadPayloads);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	PayloadType* Payload			   = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, this, UpdateGroup);

	typedef UCsManager_Data ClassType;
	#define COROUTINE AsyncLoadPayloads_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, this, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	for (const FName& PayloadName : PayloadNames)
	{
		TArray<FCsStreamableHandle>& Handles = PayloadHandleMap_Loaded.FindOrAdd(PayloadName);
		Handles.Reset(Handles.Max());
	}

	AsyncLoadPayloadsInfo.PayloadNames.Reset(FMath::Max(AsyncLoadPayloadsInfo.PayloadNames.Max(), PayloadNames.Num()));
	AsyncLoadPayloadsInfo.PayloadNames.Append(PayloadNames);
	AsyncLoadPayloadsInfo.Index	    = CS_FIRST;

	OnAsyncLoadPayloadsCompleted_Once_Event = Delegate;

	CoroutineSchedulerLibrary::StartChecked(Context, this, Payload);
}

char UCsManager_Data::AsyncLoadPayloads_Internal(FCsRoutine* R)
{
	SET_CONTEXT(AsyncLoadPayloads_Internal);

	CS_COROUTINE_READ_INT_START

	CS_COROUTINE_READ_INT_REF(R, PayloadIndex);

	const int32 PayloadCount = AsyncLoadPayloadsInfo.PayloadNames.Num();
	const FName& PayloadName = AsyncLoadPayloadsInfo.PayloadNames[PayloadIndex];

	CS_COROUTINE_BEGIN(R);

	do 
	{
		{
			{
				typedef NCsLoad::NManager::NLoadObjectPaths::FPayload PayloadType;

				const int32 PathCount = Payload_GetPathCountChecked(Context, PayloadName);
	
				/*if (Count <= CS_EMPTY)
				{
					UE_LOG(LogCsData, Warning, TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString()));

					OnAsyncLoadPayloadCompleted_Once_Event.ExecuteIfBound(false, PayloadName);
					OnAsyncLoadPayloadCompleted_Once_Event.Unbind();
					return;
				}*/

				PayloadType Payload;

				// Set ObjectPaths
				Payload.ObjectPaths.Reset(PathCount);

				Payload_GetPathsChecked(Context, PayloadName, Payload.ObjectPaths);

				if (Payload.ObjectPaths.Num() > CS_EMPTY)
				{
					// Set Async Order
					Payload.AsyncOrder = EMCsLoadAsyncOrder::Get().GetEnumAt(CsCVarManagerDataLoadAsyncOrder->GetInt());
					// Set callback On Finish
					Payload.OnFinishLoadObjectPaths.BindUObject(this, &UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayloads);

					FCsLoadHandle Handle = UCsManager_Load::Get(MyRoot)->LoadObjectPaths(Payload);

					InProgressAsyncLoadPayloads.Add(Handle, PayloadName);
				}
				else
				{
					++AsyncLoadPayloadsInfo.Index;
				}
			}
			CS_COROUTINE_WAIT_UNTIL(R, AsyncLoadPayloadsInfo.Index > PayloadIndex);

			++PayloadIndex;
		}
	} while (PayloadIndex < PayloadCount);

	{
		for (const FName& Name : AsyncLoadPayloadsInfo.PayloadNames)
		{
			LoadPayload(Name);
		}
	}
	
	OnAsyncLoadPayloadsCompleted_Once_Event.ExecuteIfBound(true, AsyncLoadPayloadsInfo.PayloadNames);
	OnAsyncLoadPayloadsCompleted_Once_Event.Unbind();

	CS_COROUTINE_END(R);
}

void UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayloads(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime)
{
	const int32& Index		 = AsyncLoadPayloadsInfo.Index;
	const FName& PayloadName = AsyncLoadPayloadsInfo.PayloadNames[Index];

	for (const TSharedPtr<FStreamableHandle>& H : Handles)
	{
		PayloadHandleMap_Loaded[PayloadName].AddDefaulted_GetRef().Init(H);
	}
	
	InProgressAsyncLoadPayloads.Remove(Handle);

	++AsyncLoadPayloadsInfo.Index;
}

#pragma endregion List

		// Group
#pragma region

void UCsManager_Data::AsyncLoadPayloadByGroup(const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate)
{
	SET_CONTEXT(AsyncLoadPayloadByGroup);

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Data, AsyncLoadPayloadByGroup_Internal, NCsUpdateGroup::GameInstance, this, this);

	TArray<FCsStreamableHandle>& Handles = PayloadHandleMap_Loaded.FindOrAdd(PayloadName);
	Handles.Reset(Handles.Max());

	AsyncLoadPayloadByGroupInfo.PayloadName = PayloadName;
	AsyncLoadPayloadByGroupInfo.Index	    = CS_FIRST;

	OnAsyncLoadPayloadCompleted_Once_Event = Delegate;

	CS_COROUTINE_PAYLOAD_PASS_NAME_START

	CS_COROUTINE_PAYLOAD_PASS_NAME(PayloadName);

	CS_COROUTINE_START(this);
}

char UCsManager_Data::AsyncLoadPayloadByGroup_Internal(FCsRoutine* R)
{
	SET_CONTEXT(AsyncLoadPayloadByGroup_Internal);

	CS_COROUTINE_READ_INT_START
	CS_COROUTINE_READ_NAME_START

	CS_COROUTINE_READ_INT_REF(R, GroupIndex);

	typedef ECsObjectPathDependencyGroup GroupType;

	GroupType Group		   = (GroupType)GroupIndex;
	const int32 GroupCount = (int32)GroupType::ECsObjectPathDependencyGroup_MAX;

	CS_COROUTINE_READ_NAME_CONST_REF(R, PayloadName);

	CS_COROUTINE_BEGIN(R);

	do 
	{
		{
			{
				typedef NCsLoad::NManager::NLoadObjectPaths::FPayload PayloadType;

				PayloadType Payload;

				// Set ObjectPaths
				Payload_GetPathsByGroupChecked(Context, PayloadName, Group, Payload.ObjectPaths);

				if (Payload.ObjectPaths.Num() > CS_EMPTY)
				{
					// Set Async Order
					Payload.AsyncOrder = EMCsLoadAsyncOrder::Get().GetEnumAt(CsCVarManagerDataLoadAsyncOrder->GetInt());
					// Set callback On Finish
					Payload.OnFinishLoadObjectPaths.BindUObject(this, &UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayloadByGroup);

					FCsLoadHandle Handle = UCsManager_Load::Get(MyRoot)->LoadObjectPaths(Payload);

					InProgressAsyncLoadPayloads.Add(Handle, PayloadName);
				}
				else
				{
					++AsyncLoadPayloadByGroupInfo.Index;
				}
			}
			CS_COROUTINE_WAIT_UNTIL(R, AsyncLoadPayloadByGroupInfo.Index > GroupIndex);

			++GroupIndex;
			Group = (GroupType)GroupIndex;
		}
	} while (GroupIndex < GroupCount);

	LoadPayload(PayloadName);

	OnAsyncLoadPayloadCompleted_Once_Event.ExecuteIfBound(true, PayloadName);
	OnAsyncLoadPayloadCompleted_Once_Event.Unbind();

	OnAsyncLoadPayloadCompleted_Persistent_Event.Broadcast(true, PayloadName);

	CS_COROUTINE_END(R);
}

void UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayloadByGroup(const FCsLoadHandle& Handle, const TArray<TSharedPtr<FStreamableHandle>>& Handles, const TArray<FSoftObjectPath>& LoadedPaths, const TArray<UObject*>& LoadedObjects, const float& LoadTime)
{
	const FName& PayloadName = AsyncLoadPayloadByGroupInfo.PayloadName;

	for (const TSharedPtr<FStreamableHandle>& H : Handles)
	{
		PayloadHandleMap_Loaded[PayloadName].AddDefaulted_GetRef().Init(H);
	}
	
	InProgressAsyncLoadPayloads.Remove(Handle);

	++AsyncLoadPayloadByGroupInfo.Index;
}

#pragma endregion Group

#undef OnAsyncLoadPayloadCompleteOnceType

void UCsManager_Data::UnloadPayload(const FName& PayloadName)
{
	SET_CONTEXT(UnloadPayload);

	CS_IS_NAME_NONE_CHECKED(PayloadName)

	if (FCsPayload** PayloadPtr = PayloadMap_Added.Find(PayloadName))
	{
		FCsPayload& Payload = **PayloadPtr;

		Payload.Reset();
		Manager_Payload.DeallocateAt(Payload.GetIndex());
	}

	PayloadMap_Added.Remove(PayloadName);
	PayloadMap_Loaded.Remove(PayloadName);
	PayloadHandleMap_Loaded.Remove(PayloadName);
}

#pragma endregion Payload

#pragma endregion Load

// Get
#pragma region

	// Payload
#pragma region

		// SoftObjectPath
#pragma region

void UCsManager_Data::Payload_GetPaths(const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths) const
{
	SET_CONTEXT(Payload_GetPaths);
	
	CS_IS_NAME_NONE_CHECKED(PayloadName)

	FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Data_GetPathsChecked(Context, EntryName, OutPaths);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			ScriptData_GetPathsChecked(Context, EntryName, OutPaths);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				DataTable_GetPathsChecked(Context, EntryName, OutPaths);
			}
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					OutPaths.Add(DataTable_GetPathChecked(Context, EntryName));

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					DataTable_Row_GetPathsChecked(Context, EntryName, RowName, OutPaths);
				}
			}
		}
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCsData, Warning, TEXT("%s: Failed to find Payload: %s."), *Context, *(PayloadName.ToString()));
	}
#endif // #if WITH_EDITOR
}

void UCsManager_Data::Payload_GetPathsChecked(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths) const
{
	CS_IS_NAME_NONE_CHECKED(PayloadName)

	 FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Data_GetPathsChecked(Context, EntryName, OutPaths);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			ScriptData_GetPathsChecked(Context, EntryName, OutPaths);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				DataTable_GetPathsChecked(Context, EntryName, OutPaths);
			}
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					OutPaths.Add(DataTable_GetPathChecked(Context, EntryName));

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					DataTable_Row_GetPathsChecked(Context, EntryName, RowName, OutPaths);
				}
			}
		}
	}
#if !UE_BUILD_SHIPPING
	else
	{
		checkf(0, TEXT("%s: Failed to find Payload: %s."), *Context, *(PayloadName.ToString()));
	}
#endif // #if UE_BUILD_SHIPPING
}

void UCsManager_Data::Payload_GetSafePaths(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths, void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/) const
{
	CS_IS_NAME_NONE_EXIT(PayloadName)

	FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Data_GetPathsChecked(Context, EntryName, OutPaths);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			ScriptData_GetPathsChecked(Context, EntryName, OutPaths);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				DataTable_GetPathsChecked(Context, EntryName, OutPaths);
			}
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					OutPaths.Add(DataTable_GetPathChecked(Context, EntryName));

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					DataTable_Row_GetPathsChecked(Context, EntryName, RowName, OutPaths);
				}
			}
		}
	}
#if !UE_BUILD_SHIPPING
	else
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Payload: %s."), *Context, *(PayloadName.ToString())));
	}
#endif // #if UE_BUILD_SHIPPING
}

int32 UCsManager_Data::Payload_GetPathCount(const FName& PayloadName) const
{
	SET_CONTEXT(Payload_GetPathCount);

	CS_IS_NAME_NONE_CHECKED(PayloadName)

	int32 Count = 0;

	FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Count += Data_GetPathCountChecked(Context, EntryName);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			Count += ScriptData_GetPathCountChecked(Context, EntryName);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				Count += DataTable_GetPathCountChecked(Context, EntryName);
			}
			// Specified Rows
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					++Count;

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					Count += DataTable_Row_GetPathCountChecked(Context, EntryName, RowName);
				}
			}
		}
		return Count;
	}

	return Count;
}

int32 UCsManager_Data::Payload_GetPathCountChecked(const FString& Context, const FName& PayloadName) const
{
	CS_IS_NAME_NONE_CHECKED(PayloadName)

	int32 Count = 0;

	FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Count += Data_GetPathCountChecked(Context, EntryName);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			Count += ScriptData_GetPathCountChecked(Context, EntryName);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				Count += DataTable_GetPathCountChecked(Context, EntryName);
			}
			// Specified Rows
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					++Count;

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					Count += DataTable_Row_GetPathCountChecked(Context, EntryName, RowName);
				}
			}
		}
		return Count;
	}

	checkf(0, TEXT("%s: Failed to find Payload with PayloadName: %s."), *Context, *(PayloadName.ToString()));
	return Count;
}

int32 UCsManager_Data::Payload_GetSafePathCount(const FString& Context, const FName& PayloadName, void(*Log)(const FString&) /*= &NCsData::FLog::Warning*/)
{
	CS_IS_NAME_NONE_RET_VALUE(PayloadName, 0)

	int32 Count = 0;

	FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Count += Data_GetPathCountChecked(Context, EntryName);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			Count += ScriptData_GetPathCountChecked(Context, EntryName);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				Count += DataTable_GetPathCountChecked(Context, EntryName);
			}
			// Specified Rows
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					++Count;

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					Count += DataTable_Row_GetPathCountChecked(Context, EntryName, RowName);
				}
			}
		}
		return Count;
	}

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Payload with PayloadName: %s."), *Context, *(PayloadName.ToString())));
	return Count;
}

void UCsManager_Data::Payload_GetPathsByGroupChecked(const FString& Context, const FName& PayloadName, const ECsObjectPathDependencyGroup& Group, TArray<FSoftObjectPath>& OutPaths) const
{
	CS_IS_NAME_NONE_CHECKED(PayloadName)

	 FCsPayload* const* PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		TSet<FSoftObjectPath> Paths;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Data_GetPathsByGroupChecked(Context, EntryName, Group, Paths);
		}
	//#if !UE_BUILD_SHIPPING
		// ScriptDatas
		for (const FCsPayload_ScriptData& Payload_ScriptData : Payload->ScriptDatas)
		{
			const FName& EntryName = Payload_ScriptData.Name;

			ScriptData_GetPathsByGroupChecked(Context, EntryName, Group, Paths);
		}
	//#endif // #if !UE_BUILD_SHIPPING
		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				DataTable_GetPathsByGroupChecked(Context, EntryName, Group, Paths);
			}
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					Paths.Add(DataTable_GetPathChecked(Context, EntryName));

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					DataTable_Row_GetPathsByGroupChecked(Context, EntryName, RowName, Group, Paths);
				}
			}
		}
		OutPaths.Append(Paths.Array());
	}
#if !UE_BUILD_SHIPPING
	else
	{
		checkf(0, TEXT("%s: Failed to find Payload: %s."), *Context, *(PayloadName.ToString()));
	}
#endif // #if UE_BUILD_SHIPPING
}

#pragma endregion SoftObjectPath

#pragma endregion Payload

#pragma endregion Get

// Add
#pragma region

	// Data
#pragma region

bool UCsManager_Data::SafeAddData_Loaded(const FString& Context, const FName& EntryName, ICsData* Data, void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/)
{
	CS_IS_NAME_NONE(EntryName)
	CS_IS_PTR_NULL(Data)

	if (ICsData** DataPtr = DataMap_Loaded.Find(EntryName))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data already exists for EntryName: %s."), *Context, *(EntryName.ToString())));
		return false;
	}

	typedef NCsData::IData DataType;

	DataType* IData = Data->_getIData();

	if (!IData)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data->_getIData() is NULL (returns DataType (NCsData::IData))."), *Context));
		return false;
	}

	if (UObject* UData = Data->_getUObject())
	{
		DataObjectMap_Loaded.Add(EntryName, UData);
		DataObjectsAdded_Loaded.Add(UData);
	}
	DataMap_Loaded.Add(EntryName, Data);
	return true;
}

bool UCsManager_Data::SafeAddDataObject_Loaded(const FString& Context, const FName& EntryName, UObject* Data, void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/)
{
	CS_IS_NAME_NONE(EntryName)
	CS_IS_PTR_NULL(Data)

	ICsData* InterfaceData = Cast<ICsData>(Data);

	if (!InterfaceData)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsData."), *Context, *(ObjectLibrary::PrintObjectAndClass(Data))));
		return false;
	}
	
	typedef NCsData::IData DataType;

	DataType* IData = InterfaceData->_getIData();

	if (!IData)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s->_getIData() is NULL (returns DataType (NCsData::IData))."), *(Data->GetName()), *Context));
		return false;
	}

	if (UObject** DataPtr = DataObjectMap_Loaded.Find(EntryName))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data already exists for EntryName: %s."), *Context, *(EntryName.ToString())));
		return false;
	}
	DataObjectMap_Loaded.Add(EntryName, Data);
	DataMap_Loaded.Add(EntryName, InterfaceData);
	DataObjectsAdded_Loaded.Add(Data);
	return true;
}

void UCsManager_Data::AddDataCompositionObject_Loaded(const FName& DataName, UObject* Data, const FName& SliceName)
{
	SET_CONTEXT(AddDataCompositionObject_Loaded);

	CS_IS_NAME_NONE_CHECKED(DataName)
	CS_IS_PTR_NULL_CHECKED(Data)
	CS_IS_NAME_NONE_CHECKED(SliceName)

	FCsMap_ObjectByName& Map = DataCompositionObjectsAdded_Loaded.FindOrAdd(DataName);

	checkf(Map.Map.Find(SliceName) == nullptr, TEXT("%s: Data: %s with Slice: %s has ALREADY been added."), *Context, *(DataName.ToString()), *(SliceName.ToString()));

	Map.Map.Add(SliceName, Data);
}

bool UCsManager_Data::SafeRemoveDataCompositionObject_Loaded(const FString& Context, const FName& DataName, void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/)
{
	CS_IS_NAME_NONE(DataName)

	const int32 Count = DataCompositionObjectsAdded_Loaded.Remove(DataName);

	if (Count == 0)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Data associated with DataName: %s."), *Context, *(DataName.ToString())));
	}
	return Count > 0;
}

#pragma endregion Data

#pragma endregion Add

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef CoroutineSchedulerLibrary