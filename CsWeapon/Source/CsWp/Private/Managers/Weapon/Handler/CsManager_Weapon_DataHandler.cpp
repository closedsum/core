// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"

// Library
#include "Data/CsWpLibrary_DataRootSet.h"

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				using DataRootSetLibrary = NCsWeapon::NDataRootSet::FLibrary;
				using MemberType = FCsWpDataRootSet::EMember;

				FData::FData()
				{
				}
			 
				// DataHandlerType (NCsData::NManager::NHandler::TData)
				#pragma region

				void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
				{
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
}