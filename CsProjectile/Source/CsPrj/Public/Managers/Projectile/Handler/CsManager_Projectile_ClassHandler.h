// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Data/Handler/CsManager_Data_ClassHandler.h"
// Types
#include "Types/CsTypes_Projectile.h"
#include "CsProjectilePooled.h"

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NClass
			{
				using ClassHandlerType = NCsData::NManager::NHandler::TClass<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass>;

				/**
				*/
				class CSPRJ_API FClass : public ClassHandlerType
				{
				private:

					using Super = ClassHandlerType;

				public:

					FClass();

				// ClassHandlerType
				#pragma region
				protected:

					virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

					virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

				#pragma endregion ClassHandlerType
				};
			}
		}
	}
}