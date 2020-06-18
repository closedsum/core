// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileImpl::Name = FName("FCsData_ProjectileImpl");

FCsData_ProjectileImpl::FCsData_ProjectileImpl() :
		InterfaceMap(nullptr),
		InitialSpeed(nullptr),
		MaxSpeed(nullptr),
		GravityScale(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_ProjectileImpl::Name);

	InterfaceMap->Add<ICsData_Projectile>(static_cast<ICsData_Projectile*>(this));
}

FCsData_ProjectileImpl::~FCsData_ProjectileImpl()
{
	delete InterfaceMap;
}