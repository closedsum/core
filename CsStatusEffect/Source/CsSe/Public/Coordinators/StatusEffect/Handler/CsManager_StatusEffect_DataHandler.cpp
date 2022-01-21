// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/Handler/CsManager_StatusEffect_Datahandler.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsSeLibrary_DataRootSet.h"
#include "Library/CsLibrary_Property.h"

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
				typedef NCsSeDataRootSet::FLibrary DataRootSetLibrary;
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