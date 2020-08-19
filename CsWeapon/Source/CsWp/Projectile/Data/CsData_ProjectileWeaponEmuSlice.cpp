// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileWeaponEmuSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileWeaponEmuSlice::Name = FName("FCsData_ProjectileWeaponEmuSlice");

FCsData_ProjectileWeaponEmuSlice::FCsData_ProjectileWeaponEmuSlice() :
		InterfaceMap(nullptr),
		bDoFireOnRelease(nullptr),
		bFullAuto(nullptr),
		bInfiniteAmmo(nullptr),
		MaxAmmo(nullptr),
		ProjectilesPerShot(nullptr),
		TimeBetweenShots(nullptr),
		TimeBetweenAutoShots(nullptr),
		TimeBetweenProjectilesPerShot(nullptr)
{
}

FCsData_ProjectileWeaponEmuSlice::~FCsData_ProjectileWeaponEmuSlice()
{
}