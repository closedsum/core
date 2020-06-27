// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsFXPooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsFXPooledPayloadImpl::Name = FName("FCsFXPooledPayloadImpl");;

FCsFXPooledPayloadImpl::FCsFXPooledPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsFXPooledPayloadImpl::Name);

	InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));
	InterfaceMap->Add<ICsFXPooledPayload>(static_cast<ICsFXPooledPayload*>(this));
}

FCsFXPooledPayloadImpl::~FCsFXPooledPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectPayload
#pragma region

void FCsFXPooledPayloadImpl::Reset()
{
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
}

#pragma endregion ICsPooledObjectPayload