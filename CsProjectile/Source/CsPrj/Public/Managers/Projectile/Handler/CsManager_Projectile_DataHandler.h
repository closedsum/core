// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Types/CsTypes_Projectile.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileInterfaceMap.h"
#pragma once

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

				virtual bool HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const override;

				virtual void CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject) override;

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)

			protected:

				const TSet<FECsProjectileData>& GetEmulatedDataInterfaces(const FString& Context, const int32& Index);
			};

#undef DataHandlerType
#undef DataType
#undef DataInterfaceMapType
		}
	}

}