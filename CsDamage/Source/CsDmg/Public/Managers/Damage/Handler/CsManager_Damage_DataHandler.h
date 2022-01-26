// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
// Data
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/CsData_DamageInterfaceMap.h"

namespace NCsDamage
{
	namespace NManager
	{
		namespace NHandler
		{
		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataType NCsDamage::NData::IData
		#define DataInterfaceMapType NCsDamage::NData::FInterfaceMap

			/**
			*/
			class CSDMG_API FData : public DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType> Super;

			public:

				FData();

			// DataHandlerType
			#pragma region
			protected:

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

			#pragma endregion DataHandlerType
			};

		#undef DataHandlerType
		#undef DataType
		#undef DataInterfaceMapType
		}
	}

}