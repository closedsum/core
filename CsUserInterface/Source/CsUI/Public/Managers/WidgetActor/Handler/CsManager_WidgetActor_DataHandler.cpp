// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_DataHandler.h"

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
				typedef NCsUI::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsUIDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::WidgetActors;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
		}
	}
}