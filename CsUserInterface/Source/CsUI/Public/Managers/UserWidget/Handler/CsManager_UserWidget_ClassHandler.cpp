// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Handler/CsManager_UserWidget_Classhandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
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
				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				check(DataRootSet.IsValidChecked(Context, DataRootSetImpl, FCsUIDataRootSet::EMember::_UserWidgetClasses));

				OutDataTableSoftObject = DataRootSet.UserWidgetClasses;

				OutDataTable = Manager_Data->GetDataTableChecked(Context, OutDataTableSoftObject);
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				check(DataRootSet.IsValidChecked(Context, DataRootSetImpl, FCsUIDataRootSet::EMember::_UserWidgets));

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.UserWidgets;

				UDataTable* DataTable = Manager_Data->GetDataTableChecked(Context, DataTableSoftObject);

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
				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				check(DataRootSet.IsValidChecked(Context, DataRootSetImpl, FCsUIDataRootSet::EMember::_UserWidgetPooledClasses));

				OutDataTableSoftObject = DataRootSet.UserWidgetPooledClasses;

				OutDataTable = Manager_Data->GetDataTableChecked(Context, OutDataTableSoftObject);
			}

			void FPooledClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				check(DataRootSet.IsValidChecked(Context, DataRootSetImpl, FCsUIDataRootSet::EMember::_UserWidgetPooled));

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.UserWidgetPooled;

				UDataTable* DataTable = Manager_Data->GetDataTableChecked(Context, DataTableSoftObject);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion ClassHandlerType
		}
	}
}