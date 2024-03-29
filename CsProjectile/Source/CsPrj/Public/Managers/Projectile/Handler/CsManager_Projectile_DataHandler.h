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
#define DataHandlerType NCsData::NManager::NHandler::TData
#define DataType NCsProjectile::NData::IData
#define DataInterfaceMapType NCsProjectile::NData::FInterfaceMap

			/**
			*/
			class CSPRJ_API FData : public DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType> Super;

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