// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsLibrary_DataRootSet.h"
#include "CsCore.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
	// Common
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Interfaces
#include "Data/CsGetDataRootSet.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsDataRootSet
{
	UObject* FLibrary::GetSafeImpl(const FString& Context, const UObject* WorldContext)
	{
	#if WITH_EDITOR
		// Check WorldContext is Valid.
		if (!WorldContext)
		{
			typedef NCsCore::NSettings::FLibrary SettingsLibrary;

			return SettingsLibrary::SafeLoadDataRootSet(Context);
		}
		// Check if World from WorldContext is Valid.
		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (WorldLibrary::IsGameWorld(World))
		{
			typedef NCsData::NManager::FLibrary DataManagerLibrary;

			return DataManagerLibrary::GetSafeDataRootSetImpl(Context, WorldContext);
		}
		// Check if Editor World
		else
		{
			typedef NCsCore::NSettings::FLibrary SettingsLibrary;

			return SettingsLibrary::SafeLoadDataRootSet(Context);
		}
		return nullptr;
	#else
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetSafeDataRootSetImpl(Context, WorldContext);
	#endif // #if WITH_EDITOR
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, const UGameInstance* GameInstance)
	{
		CS_IS_PTR_NULL_CHECKED(GameInstance)

		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataRootSetImplChecked(Context, GameInstance);
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, const UObject* WorldContext)
	{
	#if WITH_EDITOR
		typedef NCsWorld::FLibrary WorldLibrary;

		if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
		{
			typedef NCsCore::NSettings::FLibrary SettingsLibrary;

			return SettingsLibrary::LoadDataRootSetChecked(Context);
		}
	#endif // #if WITH_EDITOR

		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataRootSetImplChecked(Context, WorldContext);
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

		typedef NCsWorld::FLibrary WorldLibrary;

		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (WorldLibrary::IsGameWorld(World))
		{
			typedef NCsData::NManager::FLibrary DataManagerLibrary;

			return DataManagerLibrary::GetSafeDataTable(Context, WorldContext, DataTableSoftObject);
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

		return DataManagerLibrary::GetSafeDataTable(Context, WorldContext, DataTableSoftObject);
#	endif // #if WITH_EDITOR
	}

	UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataTableChecked(Context, WorldContext, DataTableSoftObject);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const FName& RowName)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataTableRowChecked(Context, WorldContext, DataTableSoftObject, RowName);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const UScriptStruct* RowStruct, const FName& RowName)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataTableRowChecked(Context, WorldContext, DataTableSoftObject, RowStruct, RowName);
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