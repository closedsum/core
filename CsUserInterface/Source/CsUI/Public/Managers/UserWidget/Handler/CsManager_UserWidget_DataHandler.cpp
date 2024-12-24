// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Handler/CsManager_UserWidget_DataHandler.h"

// Library
#include "Data/CsUILibrary_DataRootSet.h"

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				using DataRootSetLibrary = NCsUI::NDataRootSet::FLibrary;
				using MemberType = FCsUIDataRootSet::EMember;

				FData::FData()
				{
				}

				// DataHandlerType (NCsData::NManager::NHandler::TData)
				#pragma region

				void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
				{
					const MemberType Member = MemberType::UserWidgets;

					UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
					TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}

				#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
			}
		}
	}
}