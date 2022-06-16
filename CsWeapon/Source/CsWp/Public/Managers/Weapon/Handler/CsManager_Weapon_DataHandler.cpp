// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"

// Library
#include "Data/CsWpLibrary_DataRootSet.h"

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
			FData::FData()
			{
			}
			 
			// DataHandlerType (NCsData::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				typedef NCsWeapon::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsWpDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::Weapons;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
		}
	}
}