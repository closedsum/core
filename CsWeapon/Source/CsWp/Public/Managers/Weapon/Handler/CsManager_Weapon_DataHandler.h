// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Types/CsTypes_Weapon.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/CsData_WeaponInterfaceMap.h"

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				using DataType = NCsWeapon::NData::IData;
				using DataInterfaceMapType = NCsWeapon::NData::FInterfaceMap;
				using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_WeaponPtr, DataInterfaceMapType>;
				

				/**
				*/
				class CSWP_API FData : public DataHandlerType
				{
				private:

					using Super = DataHandlerType;

				public:

					FData();

				// DataHandlerType (NCsData::NManager::NHandler::TData)
				#pragma region
				protected:

					virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

				#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
				};
			}
		}
	}

}