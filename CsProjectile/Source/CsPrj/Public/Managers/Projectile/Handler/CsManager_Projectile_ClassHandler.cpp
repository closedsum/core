// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Handler/CsManager_Projectile_Classhandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjLibrary_DataRootSet.h"

FCsManager_Projectile_ClassHandler::FCsManager_Projectile_ClassHandler()
{

}

// TCsManager_PooledObject_ClassHandler
#pragma region

void FCsManager_Projectile_ClassHandler::GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
{
	UObject* DataRootSetImpl			= FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsPrjDataRootSet& DataRootSet = FCsPrjLibrary_DataRootSet::GetChecked(Context, MyRoot);

	OutDataTableSoftObject = DataRootSet.ProjectileClasses;

	checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().ProjectileClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

	UWorld* World				  = MyRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

	OutDataTable = Manager_Data->GetDataTable(OutDataTableSoftObject);

	checkf(OutDataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(OutDataTableSoftObject.ToSoftObjectPath().ToString()));
}

void FCsManager_Projectile_ClassHandler::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
{
	UObject* DataRootSetImpl			 = FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsPrjDataRootSet& DataRootSet = FCsPrjLibrary_DataRootSet::GetChecked(Context, MyRoot);

	for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet.Projectiles)
	{
		TSoftObjectPtr<UDataTable> DataTableSoftObject = Projectiles.Projectiles;

		checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().Projectiles is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

		UWorld* World				  = MyRoot->GetWorld();
		UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

		UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

		checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

		OutDataTables.Add(DataTable);
		OutDataTableSoftObjects.Add(DataTableSoftObject);
	}
}

#pragma endregion TCsManager_PooledObject_ClassHandler