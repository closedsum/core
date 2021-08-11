// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Data/CsManager_Data.h"
#include "CsCore.h"

// CVar
#include "CsCVars_Manager_Data.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Data/CsGetDataRootSet.h"
#include "Data/CsData.h"
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

namespace NCsManagerData
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, GenerateMaps);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadData);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, LoadDataTableRow);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AsyncLoadPayload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, GetPayloadSoftObjectPaths);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, GetPayloadSoftObjectPathCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Data, AddDataCompositionObject_Loaded);
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
/*static*/ UCsManager_Data* UCsManager_Data::Get(UObject* InRoot /*=nullptr*/)
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

	const int32 Count = GetPayloadSoftObjectPathCountChecked(Context, PayloadName);
	
	if (Count <= CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: No Paths found for Payload: %s."), *Context, *(PayloadName.ToString()));

		OnAsyncLoadPayloadCompleted_Event.ExecuteIfBound(false, PayloadName);
		return;
	}

	FCsManagerLoad_LoadObjectPathsPayload Payload;

	// Set ObjectPaths
	Payload.ObjectPaths.Reset(Count);

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

	// Payload
#pragma region

		// SoftObjectPath
#pragma region

void UCsManager_Data::GetPayloadSoftObjectPaths(const FName& PayloadName, TArray<FSoftObjectPath>& OutPaths)
{
	using namespace NCsManagerData::NCached;

	const FString& Context = Str::GetPayloadSoftObjectPaths;

	checkf(PayloadName != NAME_None, TEXT("%s: EntryName: None is NOT Valid."), *Context);

	FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName);

	if (!PayloadPtr)
		PayloadPtr = PayloadMap_Added.Find(PayloadName);

	if (PayloadPtr)
	{
		const FCsPayload* Payload = *PayloadPtr;

		// Datas
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			GetDataSoftObjectPathsChecked(Context, EntryName, OutPaths);
		}
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
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			GetDataSoftObjectPathsChecked(Context, EntryName, OutPaths);
		}
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
	using namespace NCsManagerData::NCached;

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
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Count += GetDataSoftObjectPathCountChecked(Context, EntryName);
		}
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
		for (const FCsPayload_Data& Payload_Data : Payload->Datas)
		{
			const FName& EntryName = Payload_Data.Name;

			Count += GetDataSoftObjectPathCountChecked(Context, EntryName);
		}
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

#pragma endregion Data

#pragma endregion Add