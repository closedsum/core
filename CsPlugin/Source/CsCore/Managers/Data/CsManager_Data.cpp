// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Data/CsManager_Data.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Managers/Data/CsDataRootSet.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Data/CsGetManagerData.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerDataCached
{
	namespace Str
	{
		const FString GenerateMaps = TEXT("UCsManager_Data::GenerateMaps");
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

	DataRootSet				  = Settings->DataRootSet;
	DataRootSet.Data_Class	  = DataRootSet.Data.LoadSynchronous();
	DataRootSet.Data_Internal = DataRootSet.Data_Class->GetDefaultObject<UCsDataRootSet>();

	// TODO: Move this to Coroutine and Async

	//UCsLibrary_Load::LoadStruct(Settings, UCsDeveloperSettings::StaticClass(), NCsLoadFlags::All, NCsLoadCodes::None);

	GenerateMaps();

	// REMOVE ME: Hack to stop GC from crashing.
	/*
	if (!GIsEditor)
	{
		if (Settings->DataRootSet.Get())
			Settings->DataRootSet.Get()->AddToRoot();

		if (Settings->Datas.Get())
			Settings->Datas.Get()->AddToRoot();

		if (Settings->DataTables.Get())
			Settings->DataTables.Get()->AddToRoot();

		if (Settings->Payloads.Get())
			Settings->Payloads.Get()->AddToRoot();

		if (Settings->Weapons.Get())
			Settings->Weapons.Get()->AddToRoot();

		if (Settings->WeaponAudio.Get())
			Settings->WeaponAudio.Get()->AddToRoot();
	}
	*/
}

void UCsManager_Data::CleanUp()
{
	// REMOVE ME: Hack to stop GC from crashing.
	/*
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();
	if (!GIsEditor && Settings)
	{
		if (Settings->DataRootSet.Get())
			Settings->DataRootSet.Get()->RemoveFromRoot();

		if (Settings->Datas.Get())
			Settings->Datas.Get()->RemoveFromRoot();

		if (Settings->DataTables.Get())
			Settings->DataTables.Get()->RemoveFromRoot();

		if (Settings->Payloads.Get())
			Settings->Payloads.Get()->RemoveFromRoot();

		if (Settings->Weapons.Get())
			Settings->Weapons.Get()->RemoveFromRoot();

		if (Settings->WeaponAudio.Get())
			Settings->WeaponAudio.Get()->RemoveFromRoot();
	}
	*/

#if WITH_EDITOR
	// Datas
	{
		for (TPair<FName, FCsDataEntry_Data*>& Pair : DataEntryMap_Added)
		{
			FCsDataEntry_Data* Entry = Pair.Value;
			delete Entry;
			Pair.Value = nullptr;
		}
		DataEntryMap_Added.Reset();
	}
	// DataTables
	{
		for (TPair<FName, FCsDataEntry_DataTable*>& Pair : DataTableEntryMap_Added)
		{
			FCsDataEntry_DataTable* Entry = Pair.Value;
			delete Entry;
			Pair.Value = nullptr;
		}
		DataTableEntryMap_Added.Reset();
	}
	// Payloads
	{
		for (TPair<FName, FCsPayload*>& Pair : PayloadMap_Added)
		{
			FCsPayload* Payload = Pair.Value;
			delete Payload;
			Pair.Value = nullptr;
		}
		PayloadMap_Added.Reset();
	}
#endif // #if WITH_EDITOR
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

void UCsManager_Data::UpdateDataTableRowMap(const FName& TableName, const FName& RowName, uint8* RowPtr)
{
	checkf(RowPtr, TEXT("UCsManager_Data::UpdateDataTableRowMap: RowPtr is NULL for DataTable: %s and Row: %s."), *(TableName.ToString()), *(RowName.ToString()));

	FCsDataEntry_DataTable* Entry = DataTableEntryMap[TableName];

	checkf(Entry, TEXT("UCsManager_Data::UpdateDataTableRowMap: Entry has NOT been set for DataTable: %s in DataTableEntryMap."), *(TableName.ToString()));

	const FSoftObjectPath& Path = Entry->DataTable.ToSoftObjectPath();

	// DataTableEntryRowMap_Loaded
	{
		TMap<FName, FCsDataEntry_DataTable*>& Map = DataTableEntryRowMap_Loaded.FindOrAdd(TableName);

		Map.Add(RowName, Entry);
	}
	// DataTableEntryRowByPathMap_Loaded
	{
		TMap<FName, FCsDataEntry_DataTable*>& Map = DataTableEntryRowByPathMap_Loaded.FindOrAdd(Path);

		Map.Add(RowName, Entry);
	}
	// DataTableRowMap_Loaded
	{
		TMap<FName, uint8*>& Map = DataTableRowMap_Loaded.FindOrAdd(TableName);

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

#if WITH_EDITOR

void UCsManager_Data::AddPayload(const FName& PayloadName, const FCsPayload& Payload)
{
	checkf(PayloadName != NAME_None, TEXT("UCsManager_Data::AddPayload: PayloadName is None."));

	if (PayloadMap_Added.Find(PayloadName))
		return;

	FCsPayload* P = new FCsPayload();
	*P = Payload;
	PayloadMap_Added.Add(PayloadName, P);

	// Datas
	for (const FCsPayload_Data& Data : Payload.Datas)
	{
		const FName& Name = Data.Name;

		if (!DataEntryMap.Find(Name) &&
			!DataEntryMap_Added.Find(Name))
		{
			FCsDataEntry_Data* Entry = new FCsDataEntry_Data();
			Entry->Name = Name;
			Entry->Data = Data.Data;
			Entry->Paths = Data.Paths;

			DataEntryMap.Add(Name, Entry);
			DataEntryByPathMap.Add(Data.Data.ToSoftObjectPath(), Entry);
			DataEntryMap_Added.Add(Name, Entry);
		}
	}
	// DataTables
	for (const FCsPayload_DataTable& DataTable : Payload.DataTables)
	{
		const FName& Name = DataTable.Name;

		if (!DataTableEntryMap.Find(Name) &&
			!DataTableEntryMap_Added.Find(Name))
		{
			FCsDataEntry_DataTable* Entry = new FCsDataEntry_DataTable();
			Entry->Name = Name;
			Entry->DataTable = DataTable.DataTable;
			Entry->Paths = DataTable.Paths;

			DataTableEntryMap.Add(Name, Entry);
			DataTableEntryByPathMap.Add(DataTable.DataTable.ToSoftObjectPath(), Entry);
			DataTableEntryMap_Added.Add(Name, Entry);
		}
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Payload

void UCsManager_Data::GenerateMaps() 
{
	// Datas
	if (UDataTable* Datas = DataRootSet.Get()->Datas)
	{
		const UScriptStruct* ScriptStruct = Datas->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_Data::StaticStruct(), TEXT("UCsManager_Data::GenerateMaps: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_Data"), *(Datas->GetName()), *(ScriptStruct->GetName()));

		DataEntryMap.Reset();

		TArray<FName> RowNames = Datas->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FCsDataEntry_Data* RowPtr = Datas->FindRow<FCsDataEntry_Data>(RowName, NCsManagerDataCached::Str::GenerateMaps);

			checkf(RowPtr->Data.ToSoftObjectPath().IsValid(), TEXT("UCsManager_Data::GenerateMaps:: Data at Row: %s for Datas: %s is NOT Valid."), *(RowName.ToString()), *(Datas->GetName()));

			DataEntryMap.Add(RowName, RowPtr);
			DataEntryByPathMap.Add(RowPtr->Data.ToSoftObjectPath(), RowPtr);
		}
	}
	// DataTables
	if (UDataTable* DataTables = DataRootSet.Get()->DataTables)
	{
		const UScriptStruct* ScriptStruct = DataTables->GetRowStruct();

		checkf(ScriptStruct == FCsDataEntry_DataTable::StaticStruct(), TEXT("UCsManager_Data::GenerateMaps: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsDataEntry_DataTable"), *(DataTables->GetName()), *(ScriptStruct->GetName()));

		DataTableEntryMap.Reset();

		TArray<FName> RowNames = DataTables->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(RowName, NCsManagerDataCached::Str::GenerateMaps);

			checkf(RowPtr->DataTable.ToSoftObjectPath().IsValid(), TEXT("UCsManager_Data::GenerateMaps:: DataTable at Row: %s for DataTables: %s is NOT Valid."), *(RowName.ToString()), *(DataTables->GetName()));

			DataTableEntryMap.Add(RowName, RowPtr);
			DataTableEntryByPathMap.Add(RowPtr->DataTable.ToSoftObjectPath(), RowPtr);
		}
	}
	// Payloads
	if (UDataTable* Payloads = DataRootSet.Get()->Payloads)
	{
		const UScriptStruct* ScriptStruct = Payloads->GetRowStruct();

		checkf(ScriptStruct == FCsPayload::StaticStruct(), TEXT("UCsManager_Data::GenerateMaps: The Row Struct for Data: %s is of incorrect type: %s. It should be FCsPayload"), *(Payloads->GetName()), *(ScriptStruct->GetName()));

		PayloadMap.Reset();

		TArray<FName> RowNames = Payloads->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FCsPayload* RowPtr = Payloads->FindRow<FCsPayload>(RowName, NCsManagerDataCached::Str::GenerateMaps);

			PayloadMap.Add(RowName, RowPtr);
		}
	}
}

#pragma endregion Maps

// Load
#pragma region

void UCsManager_Data::LoadPayload(const FName& PayloadName)
{
	checkf(PayloadName != NAME_None, TEXT("UCsManager_Data::LoadPayload: PayloadName is None."));

	// Check if the Payload has already been loaded
	if (PayloadMap_Loaded.Find(PayloadName))
		return;

	FCsPayload* Payload = nullptr;

	if (FCsPayload** PayloadPtr = PayloadMap.Find(PayloadName))
	{
		Payload = *PayloadPtr;
	}
#if WITH_EDITOR
	else
	{
		if (FCsPayload** PayloadAddedPtr = PayloadMap_Added.Find(PayloadName))
		{
			Payload = *PayloadAddedPtr;
		}
	}
#endif // #if WITH_EDITOR

	if (Payload)
	{
		// Datas
		for (FCsPayload_Data& Payload_Data : Payload->Datas)
		{

		}

		// DataTables
		for (FCsPayload_DataTable& Payload_DataTable : Payload->DataTables)
		{
			const FName& TableName = Payload_DataTable.Name;

			UDataTable* DT = LoadDataTable(TableName);

#if WITH_EDITOR
			if (!DT)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadPayload: Failed to load DataTable: %s."), *(TableName.ToString()));
				continue;
			}
#else
			checkf(DT, TEXT("UCsManager_Data::LoadPayload: Failed to load DataTable: %s."), *(TableName.ToString()));
#endif // If WITH_EDITOR

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
				RowNames = Payload_DataTable.Rows;
			}

			for (const FName& RowName : RowNames)
			{
				if (IsLoadedDataTableRow(TableName, RowName))
					continue;

				if (uint8* RowPtr = DT->FindRowUnchecked(RowName))
				{
					UCsLibrary_Load::LoadStruct(RowPtr, Struct, NCsLoadFlags::All, NCsLoadCodes::None);

					UpdateDataTableRowMap(TableName, RowName, RowPtr);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadPayload: Failed to Row: %s for DataTable: %s."), *(RowName.ToString()), *(TableName.ToString()));
				}
			}
		}

		PayloadMap_Loaded.Add(PayloadName, Payload);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadPayload: Failed to find Payload: %s."), *(PayloadName.ToString()));
	}
}

	// DataTable
#pragma region

UDataTable* UCsManager_Data::LoadDataTable(const FName& TableName)
{
	checkf(TableName != NAME_None, TEXT("UCsManager_Data::LoadDataTable: TableName is None."));

	if (UDataTable* Table = GetDataTable(TableName))
		return Table;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(TableName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		UCsLibrary_Load::LoadStruct(Entry, FCsDataEntry_DataTable::StaticStruct(), NCsLoadFlags::All, NCsLoadCodes::None);

		UDataTable* DataTable = Entry->Get();

#if WITH_EDITOR
		if (!DataTable)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadDataTable: Failed to load DataTable: %s."), *(TableName.ToString()));
			return nullptr;
		}
#else
		checkf(DataTable, TEXT("UCsManager_Data::LoadDataTable: Failed to load DataTable: %s."), *(TableName.ToString()));
#endif // If WITH_EDITOR

		DataTableMap_Loaded.FindOrAdd(TableName) = DataTable;
		DataTableByPathMap_Loaded.FindOrAdd(Entry->DataTable.ToSoftObjectPath()) = DataTable;

		return Entry->Get();
	}
#if WITH_EDITOR
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadDataTable: Failed to find DataTable: %s."), *(TableName.ToString()));
#else
	checkf(0, TEXT("UCsManager_Data::LoadDataTable: Failed to find DataTable: %s."), *(TableName.ToString()));
#endif // #if WITH_EDITOR
	return nullptr;
}

UDataTable* UCsManager_Data::LoadDataTable(const FSoftObjectPath& Path)
{
	checkf(Path.IsValid(), TEXT("UCsManager_Data::LoadDataTable: Path is NOT Valid."));

	return nullptr;
}

uint8* UCsManager_Data::LoadDataTableRow(const FName& TableName, const FName& RowName)
{
	checkf(TableName != NAME_None, TEXT("UCsManager_Data::LoadDataTableRow: TableName is None."));

	checkf(RowName != NAME_None, TEXT("UCsManager_Data::LoadDataTableRow:: RowName is None."));

	// Check if DataTable and Row are already loaded
	if (uint8* RowPtr = GetDataTableRow(TableName, RowName))
		return RowPtr;

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(TableName))
	{
		FCsDataEntry_DataTable* Entry = *EntryPtr;

		// If DataTable is NOT loaded, load it
		if (!Entry->Get())
			LoadDataTable(TableName);

		UDataTable* DT = Entry->Get();

#if WITH_EDITOR
		if (!DT)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadDataTableRow: Failed to find DataTable: %s."), *(TableName.ToString()));
			return nullptr;
		}
#else
		checkf(DT, TEXT("UCsManager_Data::LoadDataTableRow: Failed to find DataTable: %s."), *(TableName.ToString()));
#endif // If WITH_EDITOR

		const UScriptStruct* ScriptStruct = DT->GetRowStruct();
		UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
		UStruct* const Struct			  = Temp;

		if (uint8* RowPtr = DT->FindRowUnchecked(RowName))
		{
			UCsLibrary_Load::LoadStruct(RowPtr, Struct, NCsLoadFlags::All, NCsLoadCodes::None);
			UpdateDataTableRowMap(TableName, RowName, RowPtr);

			return RowPtr;
		}
	}
#if WITH_EDITOR
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::LoadDataTableRow: Failed to load DataTable: %s and Row: %s."), *(TableName.ToString()), *(RowName.ToString()));
#else
	checkf(0, TEXT("UCsManager_Data::LoadDataTableRow: Failed to load DataTable: %s and Row: %s."), *(TableName.ToString()), *(RowName.ToString()));
#endif // #if WITH_EDITOR
	return nullptr;
}

bool UCsManager_Data::IsLoadedDataTableRow(const FName& TableName, const FName& RowName)
{
#if WITH_EDITOR
	if (TableName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::IsLoadedDataTableRow: TableName is None."));
		return false;
	}

	if (RowName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::IsLoadedDataTableRow: RowName is None."));
		return false;
	}
#endif // #if WITH_EDITOR

	if (uint8* RowPtr = GetDataTableRow(TableName, RowName))
		return true;
	return false;
}

#pragma endregion DataTable

#pragma endregion Load

// Get
#pragma region

	// DataTable
#pragma region

UDataTable* UCsManager_Data::GetDataTable(const FName& TableName)
{
#if WITH_EDITOR
	if (TableName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTable: TableName is None."));
		return false;
	}
#endif // #if WITH_EDITOR

	if (UDataTable** TablePtr = DataTableMap_Loaded.Find(TableName))
		return *TablePtr;
	return nullptr;
}

UDataTable* UCsManager_Data::GetDataTable(const FSoftObjectPath& Path)
{
#if WITH_EDITOR
	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTable: Path is NOT Valid."));
		return false;
	}
#endif // #if WITH_EDITOR

	if (UDataTable** TablePtr = DataTableByPathMap_Loaded.Find(Path))
		return *TablePtr;
	return nullptr;
}

UDataTable* UCsManager_Data::GetDataTable(const TSoftObjectPtr<UDataTable>& SoftObject)
{
	return GetDataTable(SoftObject.ToSoftObjectPath());
}

uint8* UCsManager_Data::GetDataTableRow(const FName& TableName, const FName& RowName)
{
#if WITH_EDITOR
	if (TableName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRow: TableName is None."));
		return false;
	}

	if (RowName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRow: RowName is None."));
		return false;
	}
#endif // #if WITH_EDITOR

	if (TMap<FName, uint8*>* TablePtr = DataTableRowMap_Loaded.Find(TableName))
	{
		if (uint8** RowPtr = TablePtr->Find(RowName))
		{
			return *RowPtr;
		}
	}
	return nullptr;
}

uint8* UCsManager_Data::GetDataTableRow(const FSoftObjectPath& Path, const FName& RowName)
{
#if WITH_EDITOR
	if (!Path.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRow: Path is NOT Valid."));
		return false;
	}

	if (RowName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableRow: RowName is None."));
		return false;
	}
#endif // #if WITH_EDITOR

	if (TMap<FName, uint8*>* TablePtr = DataTableRowByPathMap_Loaded.Find(Path))
	{
		if (uint8** RowPtr = TablePtr->Find(RowName))
		{
			return *RowPtr;
		}
	}
	return nullptr;
}

		// Entry
#pragma region

const FCsDataEntry_DataTable* UCsManager_Data::GetDataTableEntry(const FName& TableName)
{
#if WITH_EDITOR
	if (TableName == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Data::GetDataTableEntry: TableName is None."));
		return nullptr;
	}
#endif // #if WITH_EDITOR

	if (FCsDataEntry_DataTable** EntryPtr = DataTableEntryMap.Find(TableName))
		return *EntryPtr;
	return nullptr;
}

#pragma endregion Entry

		// SoftObjectPath
#pragma region

void UCsManager_Data::GetDataTableSoftObjectPaths(const FName& TableName, TArray<FSoftObjectPath>& OutPaths)
{
	if (const FCsDataEntry_DataTable* Entry = GetDataTableEntry(TableName))
		OutPaths.Append(Entry->Paths.Internal);
}

#pragma endregion SoftObjectPath

#pragma endregion DataTable

#pragma endregion Get