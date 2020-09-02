// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Data/CsData_UserWidgetInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_UserWidgetInterfaceMap::Name = FName("FCsData_UserWidgetInterfaceMap");

FCsData_UserWidgetInterfaceMap::FCsData_UserWidgetInterfaceMap() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_UserWidgetInterfaceMap::Name);
	InterfaceMap->SetUniqueBasedSlices();
}

FCsData_UserWidgetInterfaceMap::~FCsData_UserWidgetInterfaceMap()
{
	delete InterfaceMap;
}