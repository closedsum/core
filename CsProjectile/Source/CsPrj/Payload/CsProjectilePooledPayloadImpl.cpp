// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsProjectilePooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsProjectilePooledPayloadImpl::FCsProjectilePooledPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Direction(0.0f),
	Location(0.0f)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));
	InterfaceMap->Add<ICsProjectilePayload>(static_cast<ICsProjectilePayload*>(this));
}

FCsProjectilePooledPayloadImpl::~FCsProjectilePooledPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectPayload
#pragma region

void FCsProjectilePooledPayloadImpl::Reset()
{
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Direction = FVector::ZeroVector;
	Location = FVector::ZeroVector;
}

#pragma endregion ICsPooledObjectPayload