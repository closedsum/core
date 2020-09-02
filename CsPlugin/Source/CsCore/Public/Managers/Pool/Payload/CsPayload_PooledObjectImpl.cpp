// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObjectImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_PooledObjectImpl::Name = FName("FCsPayload_PooledObjectImpl");

FCsPayload_PooledObjectImpl::FCsPayload_PooledObjectImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time()
{
	// ICsGetInterfaceMap
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_PooledObjectImpl::Name);

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
}

FCsPayload_PooledObjectImpl::~FCsPayload_PooledObjectImpl()
{
	// ICsGetInterfaceMap
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_PooledObjectImpl::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;

	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
}

#pragma endregion ICsPayload_PooledObject