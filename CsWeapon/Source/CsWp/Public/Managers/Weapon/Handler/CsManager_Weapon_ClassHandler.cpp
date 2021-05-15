// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Handler/CsManager_Weapon_Classhandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsWpLibrary_DataRootSet.h"

namespace NCsWeapon
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
				const FCsWpDataRootSet& DataRootSet = NCsWeapon::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				OutDataTableSoftObject = DataRootSet.WeaponClasses;

				checkf(OutDataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsWpDataRootSet().WeaponClasses is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

				typedef NCsData::NManager::FLibrary DataManagerLibrary;

				OutDataTable = DataManagerLibrary::GetDataTableChecked(Context, MyRoot, OutDataTableSoftObject);
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsWpDataRootSet& DataRootSet = NCsWeapon::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				for (const FCsWeaponSettings_DataTable_Weapons& Weapons : DataRootSet.Weapons)
				{
					TSoftObjectPtr<UDataTable> DataTableSoftObject = Weapons.Weapons;

					checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsWpDataRootSet().Weapons is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

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