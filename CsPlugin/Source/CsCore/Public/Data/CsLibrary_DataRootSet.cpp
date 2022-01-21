// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_DataRootSet.h"
#include "CsCore.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Interfaces
#include "Data/CsGetDataRootSet.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsDataRootSet
{
	UObject* FLibrary::GetSafeImpl(const FString& Context, const UObject* WorldContext)
	{
	#if WITH_EDITOR
		// Check WorldContext is Valid.
		if (!WorldContext)
		{
			UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

			return Settings->SafeLoadDataRootSet(Context);
		}
		// Check if World from WorldContext is Valid.
		UWorld* World = WorldContext->GetWorld();

		if (!World)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));
			return nullptr;
		}

		if (World->IsGameWorld())
		{
			typedef NCsData::NManager::FLibrary DataManagerLibrary;

			UCsManager_Data* Manager_Data = DataManagerLibrary::GetSafe(Context, WorldContext);

			if (!Manager_Data)
				return nullptr;

			UObject* DataRootSetImpl = Manager_Data->DataRootSet.GetObject();

			return DataRootSetImpl;
		}
		// Check if Editor World
		else
		{
			UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

			return Settings->SafeLoadDataRootSet(Context);
		}
		return nullptr;
	#else
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		UCsManager_Data* Manager_Data = DataManagerLibrary::GetSafe(Context, WorldContext);
		UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

		return DataRootSetImpl;
	#endif // #if WITH_EDITOR
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, const UGameInstance* GameInstance)
	{
		CS_IS_PTR_NULL_CHECKED(GameInstance)

		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		UCsManager_Data* Manager_Data = DataManagerLibrary::GetChecked(Context, GameInstance);
		UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

		checkf(DataRootSetImpl, TEXT("%s: DataRootSetImpl is NULL. Failed to find DataRootSet."), *Context);

		return DataRootSetImpl;
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, const UObject* WorldContext)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		UCsManager_Data* Manager_Data = DataManagerLibrary::GetChecked(Context, WorldContext);
		UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

		checkf(DataRootSetImpl, TEXT("%s: DataRootSetImpl is NULL. Failed to find DataRootSet."), *Context);

		return DataRootSetImpl;
	}

	const FCsDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
	{
		return GetSafe<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, WorldContext, &FCsLog::Warning);
	}

	const FCsDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
	{
		return GetChecked<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, GameInstance);
	}

	const FCsDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, WorldContext);
	}

	UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const FString& InterfaceGetName, TSoftObjectPtr<UDataTable> DataTableSoftObject, const FString& DataTableName)
	{
	#if WITH_EDITOR
		if (!WorldContext)
		{
			const FSoftObjectPath& Path = DataTableSoftObject.ToSoftObjectPath();

			if (!Path.IsValid())
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Path for %s.%s is NOT Valid."), *Context, *InterfaceGetName, *DataTableName);
				return nullptr;
			}

			if (UDataTable* DataTable = DataTableSoftObject.LoadSynchronous())
			{
				return DataTable;
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load %s.%s @ %s."), *Context, *InterfaceGetName, *DataTableName, *(Path.ToString()));
			}
			return nullptr;
		}

		UWorld* World = WorldContext->GetWorld();

		if (!World)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));
			return nullptr;
		}

		if (World->IsGameWorld())
		{
			typedef NCsData::NManager::FLibrary DataManagerLibrary;

			UObject* ContextRoot = DataManagerLibrary::GetSafeContextRoot(Context, WorldContext);

			if (!ContextRoot)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to get ContextRoot for UCsManager_Data."), *Context);
				return nullptr;
			}

			const FSoftObjectPath& Path = DataTableSoftObject.ToSoftObjectPath();

			if (Path.IsValid())
			{
				if (UDataTable* DataTable = UCsManager_Data::Get(ContextRoot)->GetDataTable(DataTableSoftObject))
				{
					return DataTable;
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load %s.%s @ %s."), *Context, *InterfaceGetName, *DataTableName, *(Path.ToString()));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName()), *InterfaceGetName, *DataTableName);
			}
		}
		else
		{
			const FSoftObjectPath& Path = DataTableSoftObject.ToSoftObjectPath();

			if (Path.IsValid())
			{
				if (UDataTable* DataTable = DataTableSoftObject.LoadSynchronous())
				{
					return DataTable;
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load %s.%s.%s @ %s."), *Context, *(WorldContext->GetName()), *InterfaceGetName, *DataTableName, *(Path.ToString()));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName()), *InterfaceGetName, *DataTableName);
			}
		}
		return nullptr;
	#else
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		UObject* ContextRoot		= DataManagerLibrary::GetSafeContextRoot(Context, WorldContext);
		const FSoftObjectPath& Path = DataTableSoftObject.ToSoftObjectPath();

		if (Path.IsValid())
		{
			if (UDataTable* DataTable = UCsManager_Data::Get(ContextRoot)->GetDataTable(DataTableSoftObject))
			{
				return DataTable;
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load %s.%s @ %s."), *Context, *InterfaceGetName, *DataTableName, *(Path.ToString()));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName()), *InterfaceGetName, *DataTableName);
		}
		return nullptr;
#	endif // #if WITH_EDITOR
	}

	UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetChecked(Context, WorldContext)->GetDataTableChecked(Context, DataTableSoftObject);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const FName& RowName)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetChecked(Context, WorldContext)->GetDataTableRowChecked(Context, DataTableSoftObject, RowName);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const UScriptStruct* RowStruct, const FName& RowName)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetChecked(Context, WorldContext)->GetDataTableRowChecked(Context, DataTableSoftObject, RowStruct, RowName);
	}

	#define MemberType FCsDataRootSet::EMember

	UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member)
	{
		if (const FCsDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
			return DataRootSet->GetSafeDataTable(Context, WorldContext, Member);
		return nullptr;
	}

	UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
	{
		const FCsDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableChecked(Context, WorldContext, Member);
	}

	const TSoftObjectPtr<UDataTable>& FLibrary::GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
	{
		const FCsDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableSoftObjectChecked(Context, Member);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
	{
		const FCsDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowName);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName)
	{
		const FCsDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowStruct, RowName);
	}

	#undef MemberType
}