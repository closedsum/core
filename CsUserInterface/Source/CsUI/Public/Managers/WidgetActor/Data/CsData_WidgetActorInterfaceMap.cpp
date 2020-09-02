// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Data/CsData_WidgetActorInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_WidgetActorInterfaceMap::Name = FName("FCsData_WidgetActorInterfaceMap");

FCsData_WidgetActorInterfaceMap::FCsData_WidgetActorInterfaceMap() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_WidgetActorInterfaceMap::Name);
	InterfaceMap->SetUniqueBasedSlices();
}

FCsData_WidgetActorInterfaceMap::~FCsData_WidgetActorInterfaceMap()
{
	delete InterfaceMap;
}