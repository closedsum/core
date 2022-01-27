// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_Datahandler.h"

// Library
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
				typedef NCsUIDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsUIDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::WidgetActors;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

#			pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
		}
	}
}