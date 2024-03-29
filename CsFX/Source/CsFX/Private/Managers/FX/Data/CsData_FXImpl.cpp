// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Data/CsData_FXImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_FXImpl::Name = FName("FCsData_FXImpl");

FCsData_FXImpl::FCsData_FXImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRoot<FCsData_FXImpl>(this);

	InterfaceMap->Add<ICsData_FX>(static_cast<ICsData_FX*>(this));
}

FCsData_FXImpl::~FCsData_FXImpl()
{
	delete InterfaceMap;
}