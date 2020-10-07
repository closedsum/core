// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsLibrary_Data_ProjectileWeapon.h"
#include "CsWp.h"

// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

#define DataType NCsWeapon::NProjectile::NData::IData
bool FCsLibrary_Data_ProjectileWeapon::IsValidChecked(const FString& Context, DataType* Data)
{
#undef DataType

	checkf(Data, TEXT("%s: Data is NULL."), *Context);

	// Check MaxAmmo is a valid value
	if (!Data->HasInfiniteAmmo())
	{
		checkf(Data->GetMaxAmmo() > 0, TEXT("%s: MaxAmmo must be > 0."), *Context);
	}
	// Check ProjectilesPerShot >= 1
	checkf(Data->GetProjectilesPerShot() >= 1, TEXT("%s: ProjectilesPerShot must be >= 1."), *Context);
	// Check TimeBetweenProjectilesPerShot is valid when ProjectilesPerShot > 1
	if (Data->GetProjectilesPerShot() > 1)
	{
		checkf(Data->GetTimeBetweenProjectilesPerShot() > 0.0f, TEXT("%s: TimeBetweenProjectilesPerShot must be > 0.0f when ProjectilesPerShot > 1."), *Context);
	}
	return true;
}