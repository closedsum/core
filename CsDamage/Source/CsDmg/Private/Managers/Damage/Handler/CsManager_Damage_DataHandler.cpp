// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Handler/CsManager_Damage_DataHandler.h"

// Library
#include "Data/CsDmgLibrary_DataRootSet.h"

namespace NCsDamage
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				using DataRootSetLibrary = NCsDamage::NDataRootSet::FLibrary;
				using MemberType = FCsDmgDataRootSet::EMember;

				FData::FData()
				{
				}

				// DataHandlerType
				#pragma region

				void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
				{
					const MemberType Member = MemberType::Damages;

					UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
					TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}

				#pragma endregion DataHandlerType
			}
		}
	}
}