// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/CsData_ProjectileStaticMeshVisualEmuSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileStaticMeshVisualEmuSlice::Name = FName("FCsData_ProjectileStaticMeshVisualEmuSlice");

FCsData_ProjectileStaticMeshVisualEmuSlice::FCsData_ProjectileStaticMeshVisualEmuSlice() :
		InterfaceMap(nullptr),
		StaticMesh(nullptr)
{
}

FCsData_ProjectileStaticMeshVisualEmuSlice::~FCsData_ProjectileStaticMeshVisualEmuSlice()
{
}