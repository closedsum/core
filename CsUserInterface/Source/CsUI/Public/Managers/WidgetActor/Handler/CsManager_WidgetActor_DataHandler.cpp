// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

			// DataHandlerType (NCsData::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.WidgetActors;

				checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetB5DataRootSet().WidgetActors is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UDataTable* DataTable = Manager_Data->GetDataTableChecked(Context, DataTableSoftObject);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

#			pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
		}
	}
}