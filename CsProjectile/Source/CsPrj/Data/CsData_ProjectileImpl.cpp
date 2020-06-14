// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsData_ProjectileImpl::FCsData_ProjectileImpl() :
		InterfaceMap(nullptr),
		InitialSpeed(nullptr),
		MaxSpeed(nullptr),
		GravityScale(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsData_Projectile>(static_cast<ICsData_Projectile*>(this));
}

FCsData_ProjectileImpl::~FCsData_ProjectileImpl()
{
	delete InterfaceMap;
}