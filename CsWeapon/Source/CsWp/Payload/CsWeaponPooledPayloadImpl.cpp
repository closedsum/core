// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsWeaponPooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsWeaponPooledPayloadImpl::FCsWeaponPooledPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));
	InterfaceMap->Add<ICsWeaponPayload>(static_cast<ICsWeaponPayload*>(this));
}

FCsWeaponPooledPayloadImpl::~FCsWeaponPooledPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectPayload
#pragma region

void FCsWeaponPooledPayloadImpl::Reset()
{
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;
}

#pragma endregion ICsPooledObjectPayload