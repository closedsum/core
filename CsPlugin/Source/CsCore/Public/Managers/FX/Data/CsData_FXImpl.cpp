// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Data/CsData_FXImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_FXImpl::Name = FName("FCsData_FXImpl");

FCsData_FXImpl::FCsData_FXImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_FXImpl::Name);

	InterfaceMap->Add<ICsData_FX>(static_cast<ICsData_FX*>(this));
}

FCsData_FXImpl::~FCsData_FXImpl()
{
	delete InterfaceMap;
}