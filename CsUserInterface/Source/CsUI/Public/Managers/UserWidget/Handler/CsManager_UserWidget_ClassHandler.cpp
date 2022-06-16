// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Handler/CsManager_UserWidget_ClassHandler.h"

// Library
#include "Data/CsUILibrary_DataRootSet.h"

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
			FClass::FClass()
			{

			}

			// ClassHandlerType
			#pragma region

			void FClass::GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
			{
				typedef NCsUI::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsUIDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::UserWidgetClasses;

				OutDataTable		   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				OutDataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				typedef NCsUI::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsUIDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::UserWidgets;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion ClassHandlerType

			FPooledClass::FPooledClass()
			{

			}

			// ClassHandlerType
			#pragma region

			void FPooledClass::GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
			{
				typedef NCsUI::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsUIDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::UserWidgetPooledClasses;

				OutDataTable		   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				OutDataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);
			}

			void FPooledClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				typedef NCsUI::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsUIDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::UserWidgetPooled;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion ClassHandlerType
		}
	}
}