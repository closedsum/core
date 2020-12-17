// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_DataRootSet.h"
#include "CsCore.h"

// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsDataRootSet
{
	UObject* FLibrary::GetImplChecked(const FString& Context, UObject* ContextRoot)
	{
		checkf(ContextRoot, TEXT("%s: ContextRoot is NULL."), *Context);

		UWorld* World				  = ContextRoot->GetWorld();
		UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());
		UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

		checkf(DataRootSetImpl, TEXT("%s: DataRootSetImpl is NULL. Failed to find DataRootSet."), *Context);

		return DataRootSetImpl;
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