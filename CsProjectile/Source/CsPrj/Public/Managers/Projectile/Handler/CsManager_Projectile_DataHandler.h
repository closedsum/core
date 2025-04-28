// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Types/CsTypes_Projectile.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileInterfaceMap.h"

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{	
				using DataType = NCsProjectile::NData::IData;
				using DataInterfaceMapType = NCsProjectile::NData::FInterfaceMap;
				using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>;

				/**
				*/
				class CSPRJ_API FData : public DataHandlerType
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