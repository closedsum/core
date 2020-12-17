// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_Classhandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUILibrary_DataRootSet.h"

namespace NCsWidgetActor
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
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				OutDataTableSoftObject = DataRootSet.WidgetActorClasses;

				checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetB5DataRootSet().WidgetActorClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				OutDataTable = Manager_Data->GetDataTable(OutDataTableSoftObject);

				checkf(OutDataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(OutDataTableSoftObject.ToSoftObjectPath().ToString()));
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.WidgetActors;

				checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetB5DataRootSet().WidgetActors is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

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