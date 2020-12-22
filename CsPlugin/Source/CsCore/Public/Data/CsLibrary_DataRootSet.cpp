// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_DataRootSet.h"
#include "CsCore.h"

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
	UObject* FLibrary::GetImplChecked(const FString& Context, UGameInstance* GameInstance)
	{
		checkf(GameInstance, TEXT("%s: GameInstance is NULL."), *Context);

		UCsManager_Data* Manager_Data = UCsManager_Data::Get(GameInstance);
		UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

		checkf(DataRootSetImpl, TEXT("%s: DataRootSetImpl is NULL. Failed to find DataRootSet."), *Context);

		return DataRootSetImpl;
	}

	UObject* FLibrary::GetImplChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		return GetImplChecked(Context, World->GetGameInstance());
	}

	const FCsDataRootSet& FLibrary::GetChecked(const FString& Context, UGameInstance* GameInstance)
	{
		return GetChecked<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, GameInstance);
	}

	const FCsDataRootSet& FLibrary::GetChecked(const FString& Context, UObject* WorldContext)
	{
		return GetChecked<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, WorldContext);
	}

	UDataTable* FLibrary::GetSafeDataTable(const FString& Context, UObject* Object, const FString& InterfaceGetName, TSoftObjectPtr<UDataTable> DataTableSoftObject, const FString& DataTableName)
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
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load %s.%s.%s @ %s."), *Context, *(Object->GetName()), *InterfaceGetName, *DataTableName, *(Path.ToString()));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(Object->GetName()), *InterfaceGetName, *DataTableName);
		}
		return nullptr;
	}
}