// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Data/CsData_SkeletalMeshActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_SkeletalMeshActorImpl::Name = FName("FCsData_SkeletalMeshActorImpl");

FCsData_SkeletalMeshActorImpl::FCsData_SkeletalMeshActorImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRoot<FCsData_SkeletalMeshActorImpl>(this);

	InterfaceMap->Add<ICsData_SkeletalMeshActor>(static_cast<ICsData_SkeletalMeshActor*>(this));
}

FCsData_SkeletalMeshActorImpl::~FCsData_SkeletalMeshActorImpl()
{
	delete InterfaceMap;
}