// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Data/Handler/CsManager_Data_ClassHandler.h"
// Types
#include "Types/CsTypes_Weapon.h"
#include "CsWeaponClass.h"

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
		#define ClassHandlerType NCsData::NManager::NHandler::TClass

			/**
			*/
			class CSWP_API FClass : public ClassHandlerType<FCsWeaponClass, FCsWeaponPtr, FECsWeaponClass>
			{
			private:

				typedef ClassHandlerType<FCsWeaponClass, FCsWeaponPtr, FECsWeaponClass> Super;

			public:

				FClass();

			// ClassHandlerType
			#pragma region
			protected:

				virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

			#pragma endregion ClassHandlerType
			};

		#undef ClassHandlerType
		}
	}
}