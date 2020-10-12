// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/Projectile/CsTypes_Projectile.h"
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
#define DataHandlerType NCsPooledObject::NManager::NHandler::TData

			/**
			*/
			class CSPRJ_API FData : public DataHandlerType<ICsData_Projectile, FCsData_ProjectilePtr, FCsData_ProjectileInterfaceMap>
			{
			private:

				typedef DataHandlerType<ICsData_Projectile, FCsData_ProjectilePtr, FCsData_ProjectileInterfaceMap> Super;

			public:

				FData();

			// DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			#pragma region
			protected:

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

				virtual bool HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const override;

				virtual void CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject) override;

				virtual bool DeconstructEmulatedData(const FName& InterfaceImplName, void* Data) override;

			#pragma endregion DataHandlerType (NCsPooledObject::NManager::NHandler::TData)

			protected:

				const TSet<FECsProjectileData>& GetEmulatedDataInterfaces(const FString& Context, const int32& Index);
			};

#undef DataHandlerType
		}
	}

}