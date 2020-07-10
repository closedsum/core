// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileWeaponImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileWeaponImpl::Name = FName("FCsData_ProjectileWeaponImpl");

FCsData_ProjectileWeaponImpl::FCsData_ProjectileWeaponImpl() :
		InterfaceMap(nullptr),
		bDoFireOnRelease(nullptr),
		bFullAuto(nullptr),
		MaxAmmo(nullptr),
		ProjectilesPerShot(nullptr),
		TimeBetweenShots(nullptr),
		TimeBetweenAutoShots(nullptr),
		TimeBetweenProjectilesPerShot(nullptr)
{
}

FCsData_ProjectileWeaponImpl::~FCsData_ProjectileWeaponImpl() 
{
}