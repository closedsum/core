// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/Payload/CsTdCreepPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsTdCreepPayloadImpl::Name = FName("FCsTdCreepPayloadImpl");

FCsTdCreepPayloadImpl::FCsTdCreepPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));
	InterfaceMap->Add<ICsTdCreepPayload>(static_cast<ICsTdCreepPayload*>(this));
}

FCsTdCreepPayloadImpl::~FCsTdCreepPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectPayload
#pragma region

void FCsTdCreepPayloadImpl::Reset()
{
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;
}

#pragma endregion ICsPooledObjectPayload