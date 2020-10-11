// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
				UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

				OutDataTableSoftObject = DataRootSet.UserWidgetClasses;

				checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsUIDataRootSet().UserWidgetClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				OutDataTable = Manager_Data->GetDataTable(OutDataTableSoftObject);

				checkf(OutDataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(OutDataTableSoftObject.ToSoftObjectPath().ToString()));
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.UserWidgets;

				checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsUIDataRootSet().UserWidgets is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

				checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

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
				UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

				OutDataTableSoftObject = DataRootSet.UserWidgetPooledClasses;

				checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsUIDataRootSet().UserWidgetPooledClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				OutDataTable = Manager_Data->GetDataTable(OutDataTableSoftObject);

				checkf(OutDataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(OutDataTableSoftObject.ToSoftObjectPath().ToString()));
			}

			void FPooledClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.UserWidgetPooleds;

				checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsUIDataRootSet().UserWidgetPooleds is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

				checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion ClassHandlerType
		}
	}
}