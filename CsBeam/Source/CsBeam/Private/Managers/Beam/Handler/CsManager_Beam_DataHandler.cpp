// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsBeamLibrary_DataRootSet.h"
// Beam
#include "Data/CsData_BeamImplSlice.h"

namespace NCsBeam
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				FData::FData()
				{
				}

				// DataHandlerType (NCsData::NManager::NHandler::TData)
				#pragma region

				void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
				{
					UObject* DataRootSetImpl			  = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
					const FCsBeamDataRootSet& DataRootSet = NCsBeam::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);
					/*
					for (const FCsBeamSettings_DataTable_Beams& Beams : DataRootSet.Beams)
					{
						TSoftObjectPtr<UDataTable> DataTableSoftObject = Beams.Beams;

						checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsBeamDataRootSet().Beams is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

						typedef NCsData::NManager::FLibrary DataManagerLibrary;

						UDataTable* DataTable = DataManagerLibrary::GetDataTableChecked(Context, MyRoot, DataTableSoftObject);

						OutDataTables.Add(DataTable);
						OutDataTableSoftObjects.Add(DataTableSoftObject);
					}
					*/
				}

				#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
			}
		}
	}
}