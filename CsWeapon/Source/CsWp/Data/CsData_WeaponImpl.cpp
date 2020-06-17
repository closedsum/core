// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_WeaponImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_WeaponImpl::Name = FName("FCsData_WeaponImpl");

FCsData_WeaponImpl::FCsData_WeaponImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_WeaponImpl::Name);

	InterfaceMap->Add<ICsData_Weapon>(static_cast<ICsData_Weapon*>(this));
}

FCsData_WeaponImpl::~FCsData_WeaponImpl()
{
	delete InterfaceMap;
}