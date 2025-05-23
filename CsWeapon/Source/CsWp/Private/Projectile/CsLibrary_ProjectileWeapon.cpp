// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/CsLibrary_ProjectileWeapon.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/Types/CsData_GetProjectileType.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		const FECsProjectile& FLibrary::GetProjectileTypeChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
			typedef NCsWeapon::NData::IData WeaponDataType;

			WeaponDataType* Data = WeaponManagerLibrary::GetDataChecked(Context, WorldContext, Type);

			ICsData_GetProjectileType* Data_GetProjectileType = CsWeaponDataLibrary::GetInterfaceChecked<ICsData_GetProjectileType>(Context, Data);

			const FECsProjectile& ProjectileType = Data_GetProjectileType->GetProjectileType();

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, ProjectileType)

			return ProjectileType;
		}

		const FECsProjectile& FLibrary::GetSafeProjectileType(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
			typedef NCsWeapon::NData::IData WeaponDataType;

			WeaponDataType* Data = WeaponManagerLibrary::GetSafeData(Context, WorldContext, Type, Log);

			if (!Data)
			{
				return EMCsProjectile::Get().GetMAX();
			}

			ICsData_GetProjectileType* Data_GetProjectileType = CsWeaponDataLibrary::GetSafeInterfaceChecked<ICsData_GetProjectileType>(Context, Data);

			if (!Data_GetProjectileType)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT implement interface: ICsData_GetProjectileType."), *Context, Type.ToChar()));
				return EMCsProjectile::Get().GetMAX();
			}

			const FECsProjectile& ProjectileType = Data_GetProjectileType->GetProjectileType();

			CS_IS_ENUM_STRUCT_VALID_RET_VALUE(EMCsProjectile, FECsProjectile, ProjectileType, EMCsProjectile::Get().GetMAX())

			return ProjectileType;
		}
	}
}