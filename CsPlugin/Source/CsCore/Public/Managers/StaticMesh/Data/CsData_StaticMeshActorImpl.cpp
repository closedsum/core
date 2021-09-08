// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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