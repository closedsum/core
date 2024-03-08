// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/Handler/CsManager_StatusEffect_DataHandler.h"

// Library
#include "Data/CsSeLibrary_DataRootSet.h"

namespace NCsStatusEffect
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
				typedef NCsStatusEffect::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsSeDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::StatusEffects;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion DataHandlerType
		}
	}
}