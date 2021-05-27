// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
// Types
#include "Types/CsTypes_Weapon.h"
#include "CsWeapon.h"
#pragma once

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
		#define ClassHandlerType NCsPooledObject::NManager::NHandler::TClass

			/**
			*/
			class CSWP_API FClass : public ClassHandlerType<FCsWeapon, FCsWeaponPtr, FECsWeaponClass>
			{
			private:

				typedef ClassHandlerType<FCsWeapon, FCsWeaponPtr, FECsWeaponClass> Super;

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