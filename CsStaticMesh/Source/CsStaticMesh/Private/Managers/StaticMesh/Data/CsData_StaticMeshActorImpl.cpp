// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Data/CsData_StaticMeshActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_StaticMeshActorImpl::Name = FName("FCsData_StaticMeshActorImpl");

FCsData_StaticMeshActorImpl::FCsData_StaticMeshActorImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRoot<FCsData_StaticMeshActorImpl>(this);

	InterfaceMap->Add<ICsData_StaticMeshActor>(static_cast<ICsData_StaticMeshActor*>(this));
}

FCsData_StaticMeshActorImpl::~FCsData_StaticMeshActorImpl()
{
	delete InterfaceMap;
}