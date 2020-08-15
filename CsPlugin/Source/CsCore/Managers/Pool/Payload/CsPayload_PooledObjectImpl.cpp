// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObjectImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_PooledObjectImpl::Name = FName("FCsPayload_PooledObjectImpl");

FCsPayload_PooledObjectImpl::FCsPayload_PooledObjectImpl()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_PooledObjectImpl::Name);

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));

	Reset();
}

FCsPayload_PooledObjectImpl::~FCsPayload_PooledObjectImpl()
{
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_PooledObjectImpl::Reset()
{
	bAllocated = false;

	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
}

#pragma endregion ICsPayload_PooledObject