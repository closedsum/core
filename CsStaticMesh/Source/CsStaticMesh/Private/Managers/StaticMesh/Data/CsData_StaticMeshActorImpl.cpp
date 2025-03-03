// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Data/CsData_StaticMeshActorImpl.h"

// Types
#include "CsMacro_Interface.h"
// Containers
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(FCsData_StaticMeshActorImpl);

FCsData_StaticMeshActorImpl::FCsData_StaticMeshActorImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	CS_INTERFACE_MAP_SET_ROOT(FCsData_StaticMeshActorImpl);

	CS_INTERFACE_MAP_ADD(ICsData_StaticMeshActor);
}

FCsData_StaticMeshActorImpl::~FCsData_StaticMeshActorImpl()
{
	delete InterfaceMap;
}