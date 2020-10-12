// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_Datahandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUILibrary_DataRootSet.h"

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NHandler
		{
			FData::FData()
			{

			}

			// DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.WidgetActors;

				checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetB5DataRootSet().WidgetActors is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

				checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

#			pragma endregion DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
		}
	}
}