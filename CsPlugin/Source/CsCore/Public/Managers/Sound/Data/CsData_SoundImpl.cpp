// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Data/CsData_SoundImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsData_SoundImpl::Name = FName("FCsData_SoundImpl");

FCsData_SoundImpl::FCsData_SoundImpl() :
		InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_SoundImpl::Name);

	InterfaceMap->Add<ICsData_Sound>(static_cast<ICsData_Sound*>(this));
}

FCsData_SoundImpl::~FCsData_SoundImpl()
{
	delete InterfaceMap;
}