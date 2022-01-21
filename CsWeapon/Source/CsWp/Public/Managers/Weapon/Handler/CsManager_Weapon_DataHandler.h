// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Types/CsTypes_Weapon.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/CsData_WeaponInterfaceMap.h"
#pragma once

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
#define DataHandlerType NCsData::NManager::NHandler::TData
#define DataType NCsWeapon::NData::IData
#define DataInterfaceMapType NCsWeapon::NData::FInterfaceMap

			/**
			*/
			class CSWP_API FData : public DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType> Super;

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

				const TSet<FECsWeaponData>& GetEmulatedDataInterfaces(const FString& Context, const int32& Index);
			};

#undef DataHandlerType
#undef DataType
#undef DataInterfaceMapType
		}
	}

}