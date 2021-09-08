// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
// Types
#include "Types/CsTypes_Projectile.h"
#include "Managers/Projectile/CsProjectilePooled.h"
#pragma once

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NHandler
		{
		#define ClassHandlerType NCsPooledObject::NManager::NHandler::TClass

			/**
			*/
			class CSPRJ_API FClass : public ClassHandlerType<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass>
			{
			private:

				typedef ClassHandlerType<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass> Super;

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