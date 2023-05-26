// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Handler/CsManager_Projectile_ClassHandler.h"

// Library
#include "Data/CsPrjLibrary_DataRootSet.h"

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NHandler
		{
			FClass::FClass()
			{

			}

			// ClassHandlerType
			#pragma region

			void FClass::GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject)
			{
				typedef NCsProjectile::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsPrjDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::ProjectileClasses;

				OutDataTable		   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				OutDataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);
			}

			void FClass::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				typedef NCsProjectile::NDataRootSet::FLibrary DataRootSetLibrary;
				typedef FCsPrjDataRootSet::EMember MemberType;

				const MemberType Member = MemberType::Projectiles;

				UDataTable* DataTable						   = DataRootSetLibrary::GetDataTableChecked(Context, MyRoot, Member);
				TSoftObjectPtr<UDataTable> DataTableSoftObject = DataRootSetLibrary::GetDataTableSoftObjectChecked(Context, MyRoot, Member);

				OutDataTables.Add(DataTable);
				OutDataTableSoftObjects.Add(DataTableSoftObject);
			}

			#pragma endregion ClassHandlerType
		}
	}
}