// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsProjectilePooledCacheImpl.h"

#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Containers/CsInterfaceMap.h"
// Data
#include "Data/CsData_Projectile.h"

const FName FCsProjectilePooledCacheImpl::Name = FName("FCsProjectilePooledCacheImpl");

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
	ElapsedTime(),
	Data(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsProjectilePooledCacheImpl::Name);

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	InterfaceMap->Add<ICsProjectileCache>(static_cast<ICsProjectileCache*>(this));
}

FCsProjectilePooledCacheImpl::~FCsProjectilePooledCacheImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsProjectilePooledCacheImpl::Allocate(ICsPooledObjectPayload* Payload)
{
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();
}

void FCsProjectilePooledCacheImpl::Deallocate()
{
	Reset();
}

bool FCsProjectilePooledCacheImpl::HasLifeTimeExpired()
{
	if (LifeTime > 0.0f)
	{
		return ElapsedTime.Time > LifeTime;
	}
	return false;
}

void FCsProjectilePooledCacheImpl::Reset()
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

void FCsProjectilePooledCacheImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}

void FCsProjectilePooledCacheImpl::SetData(ICsData_Projectile* InData)
{
	Data	 = InData;
	LifeTime = Data->GetLifeTime();
}