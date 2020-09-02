// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsWeaponPooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsWeaponPooledPayloadImpl::FCsWeaponPooledPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
	InterfaceMap->Add<ICsWeaponPayload>(static_cast<ICsWeaponPayload*>(this));
}

FCsWeaponPooledPayloadImpl::~FCsWeaponPooledPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsWeaponPooledPayloadImpl::Reset()
{
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
}

#pragma endregion ICsPayload_PooledObject