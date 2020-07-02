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
}

FCsData_ProjectileImpl::~FCsData_ProjectileImpl()
{
}