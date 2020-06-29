// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileVisualImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_ProjectileVisualImpl::Name = FName("FCsData_ProjectileVisualImpl");

FCsData_ProjectileVisualImpl::FCsData_ProjectileVisualImpl() :
		InterfaceMap(nullptr),
		StaticMesh(nullptr),
		SkeletalMesh(nullptr),
		TrailFX(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_ProjectileVisualImpl::Name);

	InterfaceMap->Add<ICsData_ProjectileVisual>(static_cast<ICsData_ProjectileVisual*>(this));
}

FCsData_ProjectileVisualImpl::~FCsData_ProjectileVisualImpl()
{
	delete InterfaceMap;
}