// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileWeaponImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsData_ProjectileWeaponImpl::FCsData_ProjectileWeaponImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsData_ProjectileWeapon>(static_cast<ICsData_ProjectileWeapon*>(this));
}

FCsData_ProjectileWeaponImpl::~FCsData_ProjectileWeaponImpl() 
{
	delete InterfaceMap;
}