// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Cache/CsFXPooledCacheImpl.h"

#include "Managers/Pool/CsPooledObjectPayload.h"
#include "Containers/CsInterfaceMap.h"
// Data
//#include "Data/CsData_Projectile.h"

const FName FCsFXPooledCacheImpl::Name = FName("FCsFXPooledCacheImpl");

FCsFXPooledCacheImpl::FCsFXPooledCacheImpl() :
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
	//Data(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsFXPooledCacheImpl::Name);

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	InterfaceMap->Add<ICsFXPooledCache>(static_cast<ICsFXPooledCache*>(this));
}

FCsFXPooledCacheImpl::~FCsFXPooledCacheImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsFXPooledCacheImpl::Allocate(ICsPooledObjectPayload* Payload)
{
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();
}

void FCsFXPooledCacheImpl::Deallocate()
{
	Reset();
}

bool FCsFXPooledCacheImpl::HasLifeTimeExpired()
{
	return false;
}

void FCsFXPooledCacheImpl::Reset()
{
	bAllocated = false;
	bQueueDeallocate = false;
	State = ECsPooledObjectState::Inactive;
	Instigator.Reset();
	Owner.Reset();
	Parent.Reset();
	WarmUpTime = 0.0f;
	LifeTime = 0.0f;
	StartTime.Reset();
	ElapsedTime.Reset();
}

#pragma endregion ICsPooledObjectCache

void FCsFXPooledCacheImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}

/*
void FCsFXPooledCacheImpl::SetData(ICsData_Projectile* InData)
{
	Data = InData;
}
*/