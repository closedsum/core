// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Types/CsTypes_Beam.h"
// Data
#include "Data/CsData_Beam.h"
#include "Data/CsData_BeamInterfaceMap.h"
#pragma once

namespace NCsBeam
{
	namespace NManager
	{
		namespace NHandler
		{
		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataType NCsBeam::NData::IData
		#define DataInterfaceMapType NCsBeam::NData::FInterfaceMap

			/**
			*/
			class CSBEAM_API FData : public DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType> Super;

			public:

				FData();

			// DataHandlerType (NCsData::NManager::NHandler::TData)
			#pragma region
			protected:

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
			};

		#undef DataHandlerType
		#undef DataType
		#undef DataInterfaceMapType
		}
	}

}