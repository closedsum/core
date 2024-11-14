// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_ClassHandler.h"

// Library
#include "Data/CsUILibrary_DataRootSet.h"

using DataRootSetLibrary = NCsUI::NDataRootSet::FLibrary;
using MemberType = FCsUIDataRootSet::EMember;

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NClass
			{
				FClass::FClass()
				{
				}

				// ClassHandlerType
				#pragma region

				void FClass::GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
				{
					const MemberType Member = MemberType::WidgetActorClasses;

					OutDataTable		   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
					OutDataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);
				}

				void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
				{
					const MemberType Member = MemberType::WidgetActors;

					UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
					TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}

				#pragma endregion ClassHandlerType
			}
		}
	}
}