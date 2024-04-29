// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

// Library
#include "Data/CsPrjLibrary_DataRootSet.h"

namespace NCsProjectile
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
				typedef NCsProjectile::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsPrjDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::Projectiles;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
		}
	}
}