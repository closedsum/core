// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Handler/CsManager_Weapon_ClassHandler.h"

// Library
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
				typedef NCsWeapon::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsWpDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::WeaponClasses;

				OutDataTable		   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				OutDataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				typedef NCsWeapon::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsWpDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::Weapons;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion ClassHandlerType
		}
	}
}