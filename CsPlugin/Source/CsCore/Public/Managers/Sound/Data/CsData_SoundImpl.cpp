// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/Data/CsData_SoundImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_SoundImpl::Name = FName("FCsData_SoundImpl");

FCsData_SoundImpl::FCsData_SoundImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRoot<FCsData_SoundImpl>(this);

	InterfaceMap->Add<ICsData_Sound>(static_cast<ICsData_Sound*>(this));
}

FCsData_SoundImpl::~FCsData_SoundImpl()
{
	delete InterfaceMap;
}