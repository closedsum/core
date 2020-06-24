// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/Cache/CsTdCreepPooledCacheImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsTdCreepPooledCacheImpl::Name = FName("FCsTdCreepPooledCacheImpl");

FCsTdCreepPooledCacheImpl::FCsTdCreepPooledCacheImpl() :
	Index(INDEX_NONE),
	bAllocated(false),
	bQueueDeallocate(false),
	State(ECsPooledObjectState::Inactive),
	UpdateType(ECsPooledObjectUpdate::Manager),
	Instigator(),
	Owner(),
	Parent(),
	WarmUpTime(0.0f),
	LifeTime(0.0f),
	StartTime(),
	ElapsedTime(),
	InterfaceMap(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
}

FCsTdCreepPooledCacheImpl::~FCsTdCreepPooledCacheImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsTdCreepPooledCacheImpl::Allocate(ICsPooledObjectPayload* Payload)
{
}


void FCsTdCreepPooledCacheImpl::Deallocate()
{
	Reset();
}

void FCsTdCreepPooledCacheImpl::Reset()
{
	bAllocated = false;
	bQueueDeallocate = false;
}

#pragma endregion ICsPooledObjectCache