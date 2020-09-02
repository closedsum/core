// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Cache/CsCache_UserWidgetImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// UserWidget
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
// Component
#include "Components/SceneComponent.h"

const FName FCsCache_UserWidgetImpl::Name = FName("FCsCache_UserWidgetImpl");

// Cached
#pragma region

namespace NCsCacheUserWidgetImplCached
{
	namespace Str
	{
		const FString Allocate = TEXT("FCsCache_UserWidgetImpl::Allocate");
	}
}

#pragma endregion Cached

FCsCache_UserWidgetImpl::FCsCache_UserWidgetImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsCache_PooledObject
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

	InterfaceMap->SetRootName(FCsCache_UserWidgetImpl::Name);

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	InterfaceMap->Add<ICsCache_UserWidget>(static_cast<ICsCache_UserWidget*>(this));
}

FCsCache_UserWidgetImpl::~FCsCache_UserWidgetImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsCache_UserWidgetImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsCacheUserWidgetImplCached;

	// ICsPooledObjectCache
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();
}

void FCsCache_UserWidgetImpl::Deallocate()
{
	Reset();
}

void FCsCache_UserWidgetImpl::QueueDeallocate()
{
	bQueueDeallocate = true;
}

bool FCsCache_UserWidgetImpl::ShouldDeallocate() const
{
	return bQueueDeallocate;
}

bool FCsCache_UserWidgetImpl::HasLifeTimeExpired()
{
	return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
}

void FCsCache_UserWidgetImpl::Reset()
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
}

#pragma endregion ICsPooledObjectCache

void FCsCache_UserWidgetImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}