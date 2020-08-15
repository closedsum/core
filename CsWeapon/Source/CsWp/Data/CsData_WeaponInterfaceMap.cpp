// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_WeaponInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_WeaponInterfaceMap::Name = FName("FCsData_WeaponInterfaceMap");

FCsData_WeaponInterfaceMap::FCsData_WeaponInterfaceMap() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_WeaponInterfaceMap::Name);
	InterfaceMap->SetUniqueBasedSlices();
}

FCsData_WeaponInterfaceMap::~FCsData_WeaponInterfaceMap()
{
}