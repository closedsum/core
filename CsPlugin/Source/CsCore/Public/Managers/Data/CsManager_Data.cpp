// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Data/CsManager_Data.h"
#include "CsCore.h"

// CVar
#include "CsCVars_Manager_Data.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Managers
#include "Managers/Load/CsManager_Load.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Data/CsGetManagerData.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerDataCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_STRING(GenerateMaps, "UCsManager_Data::GenerateMaps");
		CS_DEFINE_CACHED_STRING(AsyncLoadPayload, "UCsManager_Data::AsyncLoadPayload");
		CS_DEFINE_CACHED_STRING(GetPayloadSoftObjectPaths, "UCsManager_Data::GetPayloadSoftObjectPaths");
		CS_DEFINE_CACHED_STRING(GetPayloadSoftObjectPathCount, "UCsManager_Data::GetPayloadSoftObjectPathCount");
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

/*static*/ UCsManager_Data* UCsManager_Data::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerData(InRoot)->GetManager_Data();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

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

/*static*/ void UCsManager_Data::Shutdown(UObject* InRoot /*=nullptr*/)
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

/*static*/ ICsGetManagerData* UCsManager_Data::Get_GetManagerData(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Data::Get_GetManagerData: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Data::Get_GetManagerData: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Data::Get_GetManagerData: Manager_Singleton is NULL."));

	ICsGetManagerData* GetManagerData = Cast<ICsGetManagerData>(Manager_Singleton);

	checkf(GetManagerData, TEXT("UCsManager_Data::Get_GetManagerData: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerData."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerData;
}

/*static*/ ICsGetManagerData* UCsManager_Data::GetSafe_GetManagerData(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerData>(Manager_Singleton);
}

/*static*/ UCsManager_Data* UCsManager_Data::GetSafe(UObject* Object)
{
	if (ICsGetManagerData* GetManagerData = GetSafe_GetManagerData(Object))
		return GetManagerData->GetManager_Data();
	return nullptr;
}

/*static*/ UCsManager_Data* UCsManager_Data::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Data* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetFromWorldContextObject: Failed to Manager Data of type UCsManager_Data from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Data::Initialize()
{
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	DataRootSet.Data		  = Settings->DataRootSet;
	DataRootSet.Data_Class	  = DataRootSet.Data.LoadSynchronous();
	DataRootSet.Data_Internal = DataRootSet.Data_Class->GetDefaultObject<UObject>();
	DataRootSet.Interface	  = Cast<ICsGetDataRootSet>(DataRootSet.Data_Internal);

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
	using namespace NCsManagerDataCached;

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

			checkf(RowPtr->Data.ToSoftObjectPath().IsValid(), TEXT("%s: Data at Row: %s for Datas: %s is NOT Valid."), *Context, *(RowName.ToString()), *(Datas->GetName()));

			DataEntryMap.Add(RowName, RowPtr);
			DataEntryByPathMap.Add(RowPtr->Data.ToSoftObjectPath(), RowPtr);
		}
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

	// DataTable
#pragma region

UDataTable* UCsManager_Data::LoadDataTable(const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::LoadDataTable: EntryName is None."));

	if (UDataTable* Table = GetDataTable(EntryName))
		return Table;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(EntryName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		checkf(Entry->Name == EntryName, TEXT("UCsManager_Data::LoadDataTable: Mismatch between Entry->Name != EntryName (%s != %s)."), *(Entry->Name.ToString()), *(EntryName.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UDataTable* DataTable = Entry->Get();

		checkf(DataTable, TEXT("UCsManager_Data::LoadDataTable: Failed to load DataTable @ Entry: %s."), *(EntryName.ToString()));

		DataTableMap_Loaded.FindOrAdd(EntryName) = DataTable;
		DataTableByPathMap_Loaded.FindOrAdd(Entry->DataTable.ToSoftObjectPath()) = DataTable;

		return Entry->Get();
	}
	checkf(0, TEXT("UCsManager_Data::LoadDataTable: Failed to find DataTable @ Entry: %s."), *(EntryName.ToString()));
	return nullptr;
}

UDataTable* UCsManager_Data::LoadDataTable(const FSoftObjectPath& Path)
{
	checkf(Path.IsValid(), TEXT("UCsManager_Data::LoadDataTable: Path is NOT Valid."));

	if (UDataTable* Table = GetDataTable(Path))
		return Table;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryByPathMap.Find(Path))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		checkf(Entry->DataTable.ToSoftObjectPath() == Path, TEXT("UCsManager_Data::LoadDataTable: Mismatch between Entry's Path != Path (%s != %s)."), *(Entry->DataTable.ToSoftObjectPath().ToString()), *(Path.ToString()));

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UDataTable* DataTable = Entry->Get();

		checkf(DataTable, TEXT("UCsManager_Data::LoadDataTable: Failed to load DataTable @ Path: %s."), *(Path.ToString()));

		DataTableMap_Loaded.FindOrAdd(Entry->Name) = DataTable;
		DataTableByPathMap_Loaded.FindOrAdd(Path) = DataTable;

		return Entry->Get();
	}
	checkf(0, TEXT("UCsManager_Data::LoadDataTable: Failed to find DataTable @ Path: %s."), *(Path.ToString()));
	return nullptr;
}

uint8* UCsManager_Data::LoadDataTableRow(const FName& EntryName, const FName& RowName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::LoadDataTableRow: EntryName is None."));

	checkf(RowName != NAME_None, TEXT("UCsManager_Data::LoadDataTableRow: RowName is None."));

	// Check if DataTable and Row are already loaded
	if (uint8* RowPtr = GetDataTableRow(EntryName, RowName))
		return RowPtr;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(EntryName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		// If DataTable is NOT loaded, load it
		if (!Entry->Get())
			LoadDataTable(EntryName);

		UDataTable* DT = Entry->Get();

		checkf(DT, TEXT("UCsManager_Data::LoadDataTableRow: Failed to find DataTable @ Entry: %s."), *(EntryName.ToString()));

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
	checkf(0, TEXT("UCsManager_Data::LoadDataTableRow: Failed to load DataTable @ Entry: %s and Row: %s."), *(EntryName.ToString()), *(RowName.ToString()));
	return nullptr;
}

bool UCsManager_Data::IsLoadedDataTableRow(const FName& EntryName, const FName& RowName)
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

		}

		// DataTables
		for (FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			// Load the DataTable
			const FName& EntryName = Payload_DataTable.Name;

			UDataTable* DT = LoadDataTable(EntryName);

			checkf(DT, TEXT("UCsManager_Data::LoadPayload: Failed to load DataTable with EntryName: %s."), *(EntryName.ToString()));

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
	using namespace NCsManagerDataCached;

	const FString& Context = Str::AsyncLoadPayload;

	const int32 Count = GetPayloadSoftObjectPathCountChecked(Context, PayloadName);
	
	if (Count <= CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString()));

		OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(false, PayloadName);
		return;
	}

	FCsManagerLoad_LoadObjectPathsPayload Payload;

	// Set ObjectPaths
	Payload.ObjectPaths.Reserve(Count);

	GetPayloadSoftObjectPathsChecked(Context, PayloadName, Payload.ObjectPaths);
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

	OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(true, PayloadName);

	InProgressAsyncLoadPayloads.Remove(Handle);

	OnAsyncLoadPayloadCompleted_Event.Unbind();
}

#pragma endregion Payload

#pragma endregion Load

// Get
#pragma region

	// DataTable
#pragma region

UDataTable* UCsManager_Data::GetDataTable(const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTable: EntryName: None is NOT Valid."));

	if (UDataTable** TablePtr = DataTableMap_Loaded.Find(EntryName))
		return *TablePtr;
	return nullptr;
}

UDataTable* UCsManager_Data::GetDataTableChecked(const FString& Context, const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("%s: EntryName is None."));

	if (UDataTable** TablePtr = DataTableMap_Loaded.Find(EntryName))
		return *TablePtr;

	checkf(0, TEXT("%s: Failed to find DataTable with EntryName; %s."), *Context, *(EntryName.ToString()));
	return nullptr;
}


UDataTable* UCsManager_Data::GetDataTable(const FSoftObjectPath& Path)
{
	checkf(Path.IsValid(), TEXT("UCsManager_Data::GetDataTable: Path is NOT Valid."));

	if (UDataTable** TablePtr = DataTableByPathMap_Loaded.Find(Path))
		return *TablePtr;
	return nullptr;
}

UDataTable* UCsManager_Data::GetDataTableChecked(const FString& Context, const FSoftObjectPath& Path)
{
	checkf(Path.IsValid(), TEXT("%s: Path is NOT Valid."), *Context);

	if (UDataTable** TablePtr = DataTableByPathMap_Loaded.Find(Path))
		return *TablePtr;

	checkf(0, TEXT("%s: Failed to find DataTable @ %s."), *(Path.ToString()));
	return nullptr;
}

UDataTable* UCsManager_Data::GetDataTable(const TSoftObjectPtr<UDataTable>& SoftObject)
{
	return GetDataTable(SoftObject.ToSoftObjectPath());
}

UDataTable* UCsManager_Data::GetDataTableChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject)
{
	return GetDataTableChecked(Context, SoftObject.ToSoftObjectPath());
}

uint8* UCsManager_Data::GetDataTableRow(const FName& EntryName, const FName& RowName)
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

uint8* UCsManager_Data::GetDataTableRowChecked(const FString& Context, const FName& EntryName, const FName& RowName)
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

uint8* UCsManager_Data::GetDataTableRow(const FSoftObjectPath& Path, const FName& RowName)
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

uint8* UCsManager_Data::GetDataTableRowChecked(const FString& Context, const FSoftObjectPath& Path, const FName& RowName)
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

uint8* UCsManager_Data::GetDataTableRow(const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName)
{
	return GetDataTableRow(SoftObject.ToSoftObjectPath(), RowName);
}

uint8* UCsManager_Data::GetDataTableRowChecked(const FString& Context, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName)
{
	return GetDataTableRowChecked(Context, SoftObject.ToSoftObjectPath(), RowName);
}

		// Entry
#pragma region

const FCsDataEntry_DataTable* UCsManager_Data::GetDataTableEntry(const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableEntry: EntryName: None is NOT Valid."));

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(EntryName))
		return *EntryPtr;
	return nullptr;
}

#pragma endregion Entry

		// SoftObjectPath
#pragma region

FSoftObjectPath UCsManager_Data::GetDataTableSoftObjectPath(const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPath: EntryName: None is NOT Valid."));

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		return Entry->DataTable.ToSoftObjectPath();
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableSoftObjectPath: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString()));
	return FSoftObjectPath();
}

FSoftObjectPath UCsManager_Data::GetDataTableSoftObjectPathChecked(const FString& Context, const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		return Entry->DataTable.ToSoftObjectPath();
	checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
	return FSoftObjectPath();
} 

void UCsManager_Data::GetDataTableSoftObjectPaths(const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPaths: EntryName: None is NOT Valid."));

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
	{
		OutPaths.Append(Entry->Paths.Internal);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableSoftObjectPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString()));
	}
}

void UCsManager_Data::GetDataTableSoftObjectPathsChecked(const FString& Context, const FName& EntryName, TArray<FSoftObjectPath>& OutPaths)
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

int32 UCsManager_Data::GetDataTableSoftObjectPathCount(const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableSoftObjectPathCount: EntryName: None is NOT Valid."));

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		return Entry->Paths.Internal.Num();
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableSoftObjectPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString()));
	return 0;
}

int32 UCsManager_Data::GetDataTableSoftObjectPathCountChecked(const FString& Context, const FName& EntryName)
{
	checkf(EntryName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
		return Entry->Paths.Internal.Num();
	checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), *Context, *(EntryName.ToString()));
	return 0;
}

void UCsManager_Data::GetDataTableRowSoftObjectPaths(const FName& EntryName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: EntryName: None is NOT Valid."));

	checkf(RowName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: RowName: None is NOT Valid."));

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
	{
		if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
		{
			OutPaths.Append(Paths->Internal);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *(EntryName.ToString()), *(RowName.ToString()));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPaths: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString()));
	}
}

void UCsManager_Data::GetDataTableRowSoftObjectPathsChecked(const FString& Context, const FName& EntryName, const FName& RowName, TArray<FSoftObjectPath>& OutPaths)
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
		checkf(0, TEXT("%s: Failed to find DataTable with EntryName: %s."), * Context, *(EntryName.ToString()));
	}
}

int32 UCsManager_Data::GetDataTableRowSoftObjectPathCount(const FName& EntryName, const FName& RowName)
{
	checkf(EntryName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: EntryName: None is NOT Valid."));

	checkf(RowName != NAME_None, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: RowName: None is NOT Valid."));

	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(EntryName))
	{
		if (const FCsTArraySoftObjectPath* Paths = Entry->PathsByRowMap.Find(RowName))
		{
			return Paths->Internal.Num();
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: DataTable with EntryName: %s does NOT have Row: %s as an entry."), *(EntryName.ToString()), *(RowName.ToString()));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRowSoftObjectPathCount: Failed to find DataTable with EntryName: %s."), *(EntryName.ToString()));
	}
	return 0;
}

int32 UCsManager_Data::GetDataTableRowSoftObjectPathCountChecked(const FString& Context, const FName& EntryName, const FName& RowName)
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

		// SoftObjectPath
#pragma region

void UCsManager_Data::GetPayloadSoftObjectPaths(const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths)
{
	using namespace NCsManagerDataCached;

	const FString& Context = Str::GetPayloadSoftObjectPaths;

	checkf(PayloadName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas

		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				GetDataTableSoftObjectPathsChecked(Context, EntryName, OutPaths);
			}
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					OutPaths.Add(GetDataTableSoftObjectPathChecked(Context, EntryName));

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					GetDataTableRowSoftObjectPathsChecked(Context, EntryName, RowName, OutPaths);
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

void UCsManager_Data::GetPayloadSoftObjectPathsChecked(const FString& Context, const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths)
{
	checkf(PayloadName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas

		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				GetDataTableSoftObjectPathsChecked(Context, EntryName, OutPaths);
			}
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					OutPaths.Add(GetDataTableSoftObjectPathChecked(Context, EntryName));

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					GetDataTableRowSoftObjectPathsChecked(Context, EntryName, RowName, OutPaths);
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

int32 UCsManager_Data::GetPayloadSoftObjectPathCount(const FName& PayloadName)
{
	using namespace NCsManagerDataCached;

	const FString& Context = Str::GetPayloadSoftObjectPathCount;

	checkf(PayloadName != NAME_None, TEXT("%s: PayloadName: None is NOT Valid."), *Context);

	int32 Count = 0;

	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas

		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				Count += GetDataTableSoftObjectPathCountChecked(Context, EntryName);
			}
			// Specified Rows
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					++Count;

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					Count += GetDataTableRowSoftObjectPathCountChecked(Context, EntryName, RowName);
				}
			}
		}
		return Count;
	}

	return Count;
}

int32 UCsManager_Data::GetPayloadSoftObjectPathCountChecked(const FString& Context, const FName& PayloadName)
{
	checkf(PayloadName != NAME_None, TEXT("%s: PayloadName: None is NOT Valid."), *Context);

	int32 Count = 0;

	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas

		// DataTables
		for (const FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& EntryName = Payload_DataTable.Name;

			// All Rows
			if (Payload_DataTable.bAllRows)
			{
				Count += GetDataTableSoftObjectPathCountChecked(Context, EntryName);
			}
			// Specified Rows
			else
			{
				if (Payload_DataTable.Rows.Num() == CS_EMPTY)
					++Count;

				for (const FName& RowName : Payload_DataTable.Rows)
				{
					Count += GetDataTableRowSoftObjectPathCountChecked(Context, EntryName, RowName);
				}
			}
		}
		return Count;
	}

	checkf(0, TEXT("%s: Failed to find Payload with PayloadName: %s."), *Context, *(PayloadName.ToString()));
	return Count;
}

#pragma endregion SoftObjectPath

#pragma endregion Payload

#pragma endregion Get