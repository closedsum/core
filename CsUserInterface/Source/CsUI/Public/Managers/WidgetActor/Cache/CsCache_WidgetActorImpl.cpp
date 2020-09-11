// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Cache/CsCache_WidgetActorImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
#include "NiagaraComponent.h"
// Component
#include "Components/CsWidgetComponent.h"

const FName FCsCache_WidgetActorImpl::Name = FName("FCsCache_WidgetActorImpl");

// Cached
#pragma region

namespace NCsCacheWidgetActorImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_STRING(Allocate, "FCsCache_WidgetActorImpl::Allocate");
	}
}

#pragma endregion Cached

FCsCache_WidgetActorImpl::FCsCache_WidgetActorImpl() :
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
	DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
	QueuedLifeTime(0.0f)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsCache_WidgetActorImpl::Name);

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	InterfaceMap->Add<ICsCache_WidgetActor>(static_cast<ICsCache_WidgetActor*>(this));
}

FCsCache_WidgetActorImpl::~FCsCache_WidgetActorImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsCache_WidgetActorImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsCacheWidgetActorImplCached;

	const FString& Context = Str::Allocate;

	// ICsPooledObjectCache
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();

	// ICsCache_WidgetActor
	ICsPayload_WidgetActor* WidgetPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_WidgetActor>(Context, Payload);

	DeallocateMethod = WidgetPayload->GetDeallocateMethod();
	QueuedLifeTime   = WidgetPayload->GetLifeTime();
}

void FCsCache_WidgetActorImpl::Deallocate()
{
	Reset();
}

void FCsCache_WidgetActorImpl::QueueDeallocate()
{
	bQueueDeallocate = true;

	// LifeTime
	if (DeallocateMethod == ECsWidgetActorDeallocateMethod::LifeTime)
	{
		// Reset ElapsedTime
		ElapsedTime.Reset();
		// Set LifeTime
		LifeTime = QueuedLifeTime;
	}
}

bool FCsCache_WidgetActorImpl::ShouldDeallocate() const
{
	if (bQueueDeallocate)
	{
		// LifeTime, let HasLifeTimeExpired handle deallocation
		if (DeallocateMethod == ECsWidgetActorDeallocateMethod::LifeTime)
		{
			return false;
		}
		return bQueueDeallocate;
	}
	return false;
}

bool FCsCache_WidgetActorImpl::HasLifeTimeExpired()
{
	return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
}

void FCsCache_WidgetActorImpl::Reset()
{
	// ICsPooledObjectCache
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
	// ICsCache_WidgetActor
	DeallocateMethod = ECsWidgetActorDeallocateMethod::ECsWidgetActorDeallocateMethod_MAX;
	QueuedLifeTime = 0.0f;
}

#pragma endregion ICsPooledObjectCache

void FCsCache_WidgetActorImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}