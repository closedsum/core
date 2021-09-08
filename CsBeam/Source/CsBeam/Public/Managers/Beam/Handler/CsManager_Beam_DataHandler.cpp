// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Beam/Handler/CsManager_Beam_Datahandler.h"

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
			namespace NCached
			{
				namespace Name
				{
					const FName LifeTime = FName("LifeTime");
					const FName InitialSpeed = FName("InitialSpeed");
					const FName MaxSpeed = FName("MaxSpeed");
					const FName GravityScale = FName("GravityScale");
				}
			}


			FData::FData()
			{
			}

			// DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			  = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsBeamDataRootSet& DataRootSet = NCsBeam::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				for (const FCsBeamSettings_DataTable_Beams& Beams : DataRootSet.Beams)
				{
					TSoftObjectPtr<UDataTable> DataTableSoftObject = Beams.Beams;

					checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsBeamDataRootSet().Beams is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

					typedef NCsData::NManager::FLibrary DataManagerLibrary;

					UDataTable* DataTable = DataManagerLibrary::GetDataTableChecked(Context, MyRoot, DataTableSoftObject);

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}
			}

			#pragma endregion DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
		}
	}
}