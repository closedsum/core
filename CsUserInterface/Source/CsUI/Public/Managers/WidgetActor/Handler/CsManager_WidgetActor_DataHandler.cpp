// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Handler/CsManager_WidgetActor_Datahandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsUILibrary_DataRootSet.h"

FCsManager_WidgetActor_DataHandler::FCsManager_WidgetActor_DataHandler()
{

}

// TCsManager_PooledObject_DataHandler Interface
#pragma region

void FCsManager_WidgetActor_DataHandler::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
{
	UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsUIDataRootSet& DataRootSet = FCsUILibrary_DataRootSet::GetChecked(Context, MyRoot);

	TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSet.WidgetActors;

	checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetSbDataRootSet().WidgetActors is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

	checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

	OutDataTables.Add(DataTable);
	OutDataTableSoftObjects.Add(DataTableSoftObject);
}

#pragma endregion TCsManager_PooledObject_DataHandler Interface