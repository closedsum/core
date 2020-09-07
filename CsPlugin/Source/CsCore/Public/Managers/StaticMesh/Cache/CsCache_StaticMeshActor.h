// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#pragma once

/**
* Cache associated with a StaticMeshActor Pooled.
*  The Manager for StaticMeshActor primarily interacts with the Cache object in terms
*  of allocation and deallocation.
*/
struct CSCORE_API ICsCache_StaticMeshActor : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsCache_StaticMeshActor() {}
};