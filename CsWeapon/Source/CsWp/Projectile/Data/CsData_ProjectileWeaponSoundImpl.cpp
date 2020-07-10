// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileWeaponSoundImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileWeaponSoundImpl::Name = FName("FCsData_ProjectileWeaponSoundImpl");

FCsData_ProjectileWeaponSoundImpl::FCsData_ProjectileWeaponSoundImpl() :
		InterfaceMap(nullptr),
		FireSound(nullptr)
{
}

FCsData_ProjectileWeaponSoundImpl::~FCsData_ProjectileWeaponSoundImpl()
{
}