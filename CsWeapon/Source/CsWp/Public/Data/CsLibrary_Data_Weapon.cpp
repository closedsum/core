// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Weapon.h"

// Library
#include "Projectile/Data/CsLibrary_Data_ProjectileWeapon.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

#define DataType NCsWeapon::NData::IData
bool FCsLibrary_Data_Weapon::IsValidChecked(const FString& Context, DataType* Data)
{
#undef DataType

	typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;

	if (ProjectileDataType* PrjData = GetSafeInterfaceChecked<ProjectileDataType>(Context, Data))
		return FCsLibrary_Data_ProjectileWeapon::IsValidChecked(Context, PrjData);
	return true;
}