// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsProjectilePooledCacheImpl.h"

#include "Containers/CsInterfaceMap.h"

FCsProjectilePooledCacheImpl::FCsProjectilePooledCacheImpl() :
	InterfaceMap(nullptr),
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
	ElapsedTime()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	InterfaceMap->Add<ICsProjectileCache>(static_cast<ICsProjectileCache*>(this));
}

FCsProjectilePooledCacheImpl::~FCsProjectilePooledCacheImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsProjectilePooledCacheImpl::Allocate(ICsPooledObjectPayload* Payload, const FCsTime& InTime)
{

}

void FCsProjectilePooledCacheImpl::Reset()
{

}

#pragma endregion ICsPooledObjectCache