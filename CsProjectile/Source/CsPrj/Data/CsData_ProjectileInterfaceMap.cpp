// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileInterfaceMap::Name = FName("FCsData_ProjectileInterfaceMap");

FCsData_ProjectileInterfaceMap::FCsData_ProjectileInterfaceMap() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_ProjectileInterfaceMap::Name);
	InterfaceMap->SetEmulated();
}

FCsData_ProjectileInterfaceMap::~FCsData_ProjectileInterfaceMap()
{
}