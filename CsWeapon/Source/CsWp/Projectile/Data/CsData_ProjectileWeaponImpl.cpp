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
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_ProjectileWeaponImpl::Name);

	InterfaceMap->Add<ICsData_Weapon>(static_cast<ICsData_Weapon*>(this));
	InterfaceMap->Add<ICsData_ProjectileWeapon>(static_cast<ICsData_ProjectileWeapon*>(this));
}

FCsData_ProjectileWeaponImpl::~FCsData_ProjectileWeaponImpl() 
{
	delete InterfaceMap;
}