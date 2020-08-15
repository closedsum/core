// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_ProjectileInterfaceMap::Name = FName("FCsPayload_ProjectileInterfaceMap");

FCsPayload_ProjectileInterfaceMap::FCsPayload_ProjectileInterfaceMap() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_ProjectileInterfaceMap::Name);
	InterfaceMap->SetUniqueBasedSlices();
}

FCsPayload_ProjectileInterfaceMap::~FCsPayload_ProjectileInterfaceMap()
{
}