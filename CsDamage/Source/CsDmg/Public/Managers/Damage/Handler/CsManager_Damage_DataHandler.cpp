// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Handler/CsManager_Damage_Datahandler.h"

// Library
#include "Data/CsDmgLibrary_DataRootSet.h"

namespace NCsDamage
{
	namespace NManager
	{
		namespace NHandler
		{
			FData::FData()
			{
			}

			// DataHandlerType
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				typedef NCsDamage::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsDmgDataRootSet::EMember MemberType;

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