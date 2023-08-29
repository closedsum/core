// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/CsManager_Data.h"
#include "CsCore.h"

// CVar
#include "Managers/Data/CsCVars_Manager_Data.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Common
#include "Library/Load/CsLibrary_Load.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Coroutine
#include "Coroutine/CsRoutine.h"
// Data
#include "Data/CsGetDataRootSet.h"
#include "Data/CsData.h"
// Managers
#include "Managers/Load/CsManager_Load.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Data/CsGetManagerData.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerData
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, GenerateMaps);
			// Load
				// Data
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadData);
				// DataTable
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadDataTableRow);
				// Payload
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayloadByGroup);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayloadByGroup_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, Payload_GetPaths);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, Payload_GetPathCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AddDataCompositionObject_Loaded);
		}

		namespace Name
		{
			// Load
				// Payload
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Data, AsyncLoadPayloadByGroup_Internal);
		}
	}
}

#pragma endregion

// static initializations
UCsManager_Data* UCsManager_Data::s_Instance;
bool UCsManager_Data::s_bShutdown = false;

UCsManager_Data::UCsManager_Data(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	TSoftClassPtr<UObject> SoftClass = Settings->DataRootSet;
	const FSoftObjectPath& Path		 = SoftClass.ToSoftObjectPath();

	checkf(Path.IsValid(), TEXT("UCsManager_Data::Initialize: UCsDeveloperSettings.DataRootSet is NOT Valid."));

	DataRootSet.Data = SoftClass;

	UClass* Class = SoftClass.LoadSynchronous();

	checkf(Class, TEXT("UCsManager_Data::Initialize: Failed to Load DataRootSet at %s."), *(Path.ToString()));

	DataRootSet.Data_Class	  = Class;
	DataRootSet.Data_Internal = DataRootSet.Data_Class->GetDefaultObject<UObject>();

	checkf(DataRootSet.Data_Internal, TEXT("UCsManager_Data::Initialize: Failed to get DefaultObject for Class: %s at Path: %s"), *(Class->GetName()), *(Path.ToString()));

	ICsGetDataRootSet* GetDataRootSet = Cast<ICsGetDataRootSet>(DataRootSet.Data_Internal);

	checkf(GetDataRootSet, TEXT("UCsManager_Data::Initialize: Class: %s does NOT implement the interface: ICsGetDataRootSet."), *(Class->GetName()));

	DataRootSet.Interface = GetDataRootSet;

	// Manager_Payload
	{
		checkf(Settings->Manager_Data.PayloadPoolSize >= 4, TEXT("UCsManager_Data::Initialize: UCsDeveloperSettings.Manager_Data.PayloadPoolSize is NOT >= 4."));

		Manager_Payload.CreatePool(Settings->Manager_Data.PayloadPoolSize);

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
		checkf(Settings->Manager_Data.DataEntryDataPoolSize >= 4, TEXT("UCsManager_Data::Initialize: UCsDeveloperSettings.Manager_Data.DataEntryDataPoolSize is NOT >= 4."));

		Manager_DataEntry_Data.CreatePool(Settings->Manager_Data.DataEntryDataPoolSize);

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
		checkf(Settings->Manager_Data.DataEntryDataTablePoolSize >= 4, TEXT("UCsManager_Data::Initialize: UCsDeveloperSettings.Manager_Data.DataEntryDataTablePoolSize is NOT >= 4."));

		Manager_DataEntry_DataTable.CreatePool(Settings->Manager_Data.DataEntryDataTablePoolSize);

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
		DataEntryMap_Added.Reset();
		Manager_DataEntry_Data.Shutdown();
	}
	// DataTables
	{
		DataTableEntryMap_Added.Reset();
		Manager_DataEntry_DataTable.Shutdown();
	}
	// Payloads
	{
		PayloadMap_Added.Reset();
		Manager_Payload.Shutdown();
		PayloadHandleMap_Loaded.Reset();
	}
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
	checkf(RowPtr, TEXT("UCsManager_Data::UpdateDataTableRowMap: RowPtr is NULL for DataTable with EntryName: %s and Row: %s."), *(EntryName.ToString()), *(RowName.ToString()));

	FCsDataEntry_DataTable* Entry = DataTableEntryMap[EntryName];

	checkf(Entry, TEXT("UCsManager_Data::UpdateDataTableRowMap: Entry has NOT been set for DataTable with EntryName: %s in DataTableEntryMap."), *(EntryName.ToString()));

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
	checkf(PayloadName != NAME_None, TEXT("UCsManager_Data::AddPayload: PayloadName is None."));

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

#pragma endregion Payload

void UCsManager_Data::GenerateMaps() 
{
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::GenerateMaps;

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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::LoadData;

	checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::LoadData;

	checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

	if (ICsData* Data = GetData(Path))
		return Data;

	if (FCsDataEntry_Data** EntryPtr = DataEntryByPathMap.Find(Path))
	{
		FCsDataEntry_Data* Entry = *EntryPtr;

		checkf(Entry->Data.ToSoftObjectPath() == Path, TEXT("%s: Mismatch between Entry's Path != Path (%s != %s)."), *Context, *(Entry->Data.ToSoftObjectPath().ToString()), *(Path.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

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

	// DataTable
#pragma region

UDataTable* UCsManager_Data::LoadDataTable(const FName& EntryName)
{
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::LoadDataTable;

	checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::LoadDataTable;

	checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::LoadDataTableRow;

	checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."), *Context);

	checkf(RowName != NAME_None, TEXT("%s: RowName is None."), *Context);

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
	checkf(PayloadName != NAME_None, TEXT("UCsManager_Data::LoadPayload: PayloadName is None."));

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
					checkf(0, TEXT("UCsManager_Data::LoadPayload: Failed to Row: %s for DataTable with EntryName: %s."), *(RowName.ToString()), *(EntryName.ToString()));
				}
			}
		}

		PayloadMap_Loaded.Add(PayloadName, Payload);
	}
	else
	{
		checkf(0, TEXT("UCsManager_Data::LoadPayload: Failed to find Payload: %s."), *(PayloadName.ToString()));
	}
}

void UCsManager_Data::AsyncLoadPayload(const FName& PayloadName, FOnAsyncLoadPayloadComplete Delegate)
{
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::AsyncLoadPayload;

	const int32 Count = Payload_GetPathCountChecked(Context, PayloadName);
	
	if (Count <= CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString()));

		OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(false, PayloadName);
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
	
	OnAsyncLoadPayloadCompleted_Event = Delegate;
}

void UCsManager_Data::SafeAsyncLoadPaylod(const FString& Context, const FName& PayloadName, FOnAsyncLoadPayloadComplete Delegate, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
{
	const int32 Count = Payload_GetSafePathCount(Context, PayloadName, Log);

	if (Count <= CS_EMPTY)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString())));

		OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(false, PayloadName);
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

		OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(false, PayloadName);
		return;
	}
	// Set Async Order
	Payload.AsyncOrder = EMCsLoadAsyncOrder::Get().GetEnumAt(CsCVarManagerDataLoadAsyncOrder->GetInt());
	// Set callback On Finish
	Payload.OnFinishLoadObjectPaths.BindUObject(this, &UCsManager_Data::OnFinishLoadObjectPaths_AsyncLoadPayload);

	FCsLoadHandle Handle = UCsManager_Load::Get(MyRoot)->LoadObjectPaths(Payload);

	InProgressAsyncLoadPayloads.Add(Handle, PayloadName);

	OnAsyncLoadPayloadCompleted_Event = Delegate;
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

	OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(true, PayloadName);

	InProgressAsyncLoadPayloads.Remove(Handle);

	OnAsyncLoadPayloadCompleted_Event.Unbind();
}

void UCsManager_Data::AsyncLoadPayloadByGroup(const FName& PayloadName, FOnAsyncLoadPayloadComplete Delegate)
{
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::AsyncLoadPayloadByGroup;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;
	PayloadType* Payload			   = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, this, UpdateGroup);

	typedef UCsManager_Data ClassType;
	#define COROUTINE AsyncLoadPayloadByGroup_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, this, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	TArray<FCsStreamableHandle>& Handles = PayloadHandleMap_Loaded.FindOrAdd(PayloadName);
	Handles.Reset(Handles.Max());

	AsyncLoadPayloadByGroupInfo.PayloadName = PayloadName;
	AsyncLoadPayloadByGroupInfo.Index	    = CS_FIRST;

	CS_COROUTINE_PAYLOAD_PASS_NAME_START

	CS_COROUTINE_PAYLOAD_PASS_NAME(Payload, PayloadName);

	CoroutineSchedulerLibrary::StartChecked(Context, this, Payload);
}

char UCsManager_Data::AsyncLoadPayloadByGroup_Internal(FCsRoutine* R)
{
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::AsyncLoadPayloadByGroup_Internal;

	CS_COROUTINE_READ_INT_START
	CS_COROUTINE_READ_NAME_START

	CS_COROUTINE_READ_INT_REF(R, GroupIndex);

	typedef ECsObjectPathDependencyGroup GroupType;

	const GroupType Group  = (GroupType)GroupIndex;
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
		}
	} while (GroupIndex < GroupCount);

	LoadPayload(PayloadName);

	OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(true, PayloadName);
	OnAsyncLoadPayloadCompleted_Event.Unbind();

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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::Payload_GetPaths;

	checkf(PayloadName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

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
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to find Payload: %s."), *Context, *(PayloadName.ToString()));
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

void UCsManager_Data::Payload_GetSafePaths(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::Payload_GetPathCount;

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

int32 UCsManager_Data::Payload_GetSafePathCount(const FString& Context, const FName& PayloadName, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
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

bool UCsManager_Data::SafeAddData_Loaded(const FString& Context, const FName& EntryName, ICsData* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

bool UCsManager_Data::SafeAddDataObject_Loaded(const FString& Context, const FName& EntryName, UObject* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::AddDataCompositionObject_Loaded;

	CS_IS_NAME_NONE_CHECKED(DataName)

	CS_IS_PTR_NULL_CHECKED(Data)
	
	CS_IS_NAME_NONE_CHECKED(SliceName)

	FCsMap_ObjectByName& Map = DataCompositionObjectsAdded_Loaded.FindOrAdd(DataName);

	checkf(Map.Map.Find(SliceName) == nullptr, TEXT("%s: Data: %s with Slice: %s has ALREADY been added."), *(DataName.ToString()), *(SliceName.ToString()));

	Map.Map.Add(SliceName, Data);
}

bool UCsManager_Data::SafeRemoveDataCompositionObject_Loaded(const FString& Context, const FName& DataName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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