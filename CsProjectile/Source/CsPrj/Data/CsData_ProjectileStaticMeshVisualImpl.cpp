// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileStaticMeshVisualImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileStaticMeshVisualImpl::Name = FName("FCsData_ProjectileStaticMeshVisualImpl");

FCsData_ProjectileStaticMeshVisualImpl::FCsData_ProjectileStaticMeshVisualImpl() :
		InterfaceMap(nullptr),
		StaticMesh(nullptr)
{
}

FCsData_ProjectileStaticMeshVisualImpl::~FCsData_ProjectileStaticMeshVisualImpl()
{
}