// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsLibrary_DataRootSet.h"
#include "CsData.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Settings
#include "Settings/CsLibrary_DataSettings.h"
	// Common
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Interfaces
#include "Data/CsGetDataRootSet.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsDataRootSet
{
	using MemberType = FCsDataRootSet::EMember;

	UObject* FLibrary::GetSafeImpl(const FString& Context)
	{
	#if WITH_EDITOR
		return CsDataSettingsLibrary::SafeLoadDataRootSet(Context);
	#else
		checkf(0, TEXT("%s: This implementation of GetSafeImpl is NOT supported outside of Editor."), *Context);
		return nullptr;
	#endif // #if WITH_EDITOR
	}

	UObject* FLibrary::GetSafeImpl(const FString& Context, const UObject* WorldContext)
	{
	#if WITH_EDITOR
		// Check WorldContext is Valid.
		if (!WorldContext)
		{
			return CsDataSettingsLibrary::SafeLoadDataRootSet(Context);
		}
		// Check if World from WorldContext is Valid.
		UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (CsWorldLibrary::IsGameWorld(World))
		{
			return CsDataManagerLibrary::GetSafeDataRootSetImpl(Context, WorldContext);
		}
		// Check if Editor World
		else
		{
			return CsDataSettingsLibrary::SafeLoadDataRootSet(Context);
		}
	#else
		return CsDataManagerLibrary::GetSafeDataRootSetImpl(Context, WorldContext);
	#endif // #if WITH_EDITOR
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, const UGameInstance* GameInstance)
	{
		CS_IS_PTR_NULL_CHECKED(GameInstance)

		return CsDataManagerLibrary::GetDataRootSetImplChecked(Context, GameInstance);
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, const UObject* WorldContext)
	{
	#if WITH_EDITOR
		if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
		{
			return CsDataSettingsLibrary::LoadDataRootSetChecked(Context);
		}
	#endif // #if WITH_EDITOR
		return CsDataManagerLibrary::GetDataRootSetImplChecked(Context, WorldContext);
	}

	const FCsDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
	{
		return GetSafe<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, WorldContext, &NCsData::FLog::Warning);
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
				UE_LOG(LogCsData, Warning, TEXT("%s: Path for %s.%s is NOT Valid."), *Context, *InterfaceGetName, *DataTableName);
				return nullptr;
			}

			if (UDataTable* DataTable = DataTableSoftObject.LoadSynchronous())
			{
				return DataTable;
			}
			else
			{
				UE_LOG(LogCsData, Warning, TEXT("%s: Failed to Load %s.%s @ %s."), *Context, *InterfaceGetName, *DataTableName, *(Path.ToString()));
			}
			return nullptr;
		}

		UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (CsWorldLibrary::IsGameWorld(World))
		{
			return CsDataManagerLibrary::GetSafeDataTable(Context, WorldContext, DataTableSoftObject);
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
					UE_LOG(LogCsData, Warning, TEXT("%s: Failed to Load %s.%s.%s @ %s."), *Context, *(WorldContext->GetName()), *InterfaceGetName, *DataTableName, *(Path.ToString()));
				}
			}
			else
			{
				UE_LOG(LogCsData, Warning, TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName()), *InterfaceGetName, *DataTableName);
			}
		}
		return nullptr;
	#else
		return CsDataManagerLibrary::GetSafeDataTable(Context, WorldContext, DataTableSoftObject);
#	endif // #if WITH_EDITOR
	}

	UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
	{
		return CsDataManagerLibrary::GetDataTableChecked(Context, WorldContext, DataTableSoftObject);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const FName& RowName)
	{
		return CsDataManagerLibrary::GetDataTableRowChecked(Context, WorldContext, DataTableSoftObject, RowName);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const UScriptStruct* RowStruct, const FName& RowName)
	{
		return CsDataManagerLibrary::GetDataTableRowChecked(Context, WorldContext, DataTableSoftObject, RowStruct, RowName);
	}

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
}