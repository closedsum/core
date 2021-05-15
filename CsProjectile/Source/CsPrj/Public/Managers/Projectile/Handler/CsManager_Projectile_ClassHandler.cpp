// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Handler/CsManager_Projectile_Classhandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjLibrary_DataRootSet.h"

namespace NCsProjectile
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
				UObject* DataRootSetImpl			 = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsPrjDataRootSet& DataRootSet = NCsProjectile::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				OutDataTableSoftObject = DataRootSet.ProjectileClasses;

				checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().ProjectileClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				typedef NCsData::NManager::FLibrary DataManagerLibrary;

				OutDataTable = DataManagerLibrary::GetDataTableChecked(Context, MyRoot, OutDataTableSoftObject);
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			 = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsPrjDataRootSet& DataRootSet = NCsProjectile::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet.Projectiles)
				{
					TSoftObjectPtr<UDataTable> DataTableSoftObject = Projectiles.Projectiles;

					checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().Projectiles is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

					typedef NCsData::NManager::FLibrary DataManagerLibrary;

					UDataTable* DataTable = DataManagerLibrary::GetDataTableChecked(Context, MyRoot, DataTableSoftObject);

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}
			}

			#pragma endregion ClassHandlerType
		}
	}
}