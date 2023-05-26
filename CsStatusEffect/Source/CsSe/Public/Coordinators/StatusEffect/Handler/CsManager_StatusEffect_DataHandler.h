// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Types/CsTypes_StatusEffect.h"
// Data
#include "Data/CsData_StatusEffect.h"
#include "Data/CsData_StatusEffectInterfaceMap.h"

namespace NCsStatusEffect
{
	namespace NManager
	{
		namespace NHandler
		{
		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataType NCsStatusEffect::NData::IData
		#define DataInterfaceMap NCsStatusEffect::NData::FInterfaceMap

			/**
			*/
			class CSSE_API FData : public DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMap>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMap> Super;

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
		#undef DataInterfaceMap
		}
	}
}