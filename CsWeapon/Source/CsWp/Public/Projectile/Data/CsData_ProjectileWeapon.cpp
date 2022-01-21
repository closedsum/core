// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileWeapon.h"
#include "CsWp.h"

const FName ICsData_ProjectileWeapon::Name = FName("ICsData_ProjectileWeapon");

UCsData_ProjectileWeapon::UCsData_ProjectileWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName NCsWeapon::NProjectile::NData::IData::Name = FName("NCsWeapon::NProjectile::NData::IData");