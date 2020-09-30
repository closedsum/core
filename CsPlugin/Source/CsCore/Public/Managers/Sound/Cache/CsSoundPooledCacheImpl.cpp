// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Cache/CsSoundPooledCacheImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Sound
#include "Managers/Sound/Payload/CsSoundPooledPayload.h"
#include "Components/AudioComponent.h"
// Component
#include "Components/SceneComponent.h"

const FName FCsSoundPooledCacheImpl::Name = FName("FCsSoundPooledCacheImpl");

// Cached
#pragma region

namespace NCsSoundPooledCacheImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsSoundPooledCacheImpl, Allocate);
	}
}

#pragma endregion Cached

FCsSoundPooledCacheImpl::FCsSoundPooledCacheImpl() :
	InterfaceMap(nullptr),
	// NCsPooledObject::NCache::ICache
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
	// ICsSoundPooledCache
	AudioComponent(nullptr),
	DeallocateMethod(ECsSoundDeallocateMethod::Complete),
	QueuedLifeTime(0.0f)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsSoundPooledCacheImpl::Name);

	InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
	InterfaceMap->Add<ICsSoundPooledCache>(static_cast<ICsSoundPooledCache*>(this));
}

FCsSoundPooledCacheImpl::~FCsSoundPooledCacheImpl()
{
	delete InterfaceMap;
}

// NCsPooledObject::NCache::ICache
#pragma region

void FCsSoundPooledCacheImpl::Allocate(NCsPooledObject::NPayload::IPayload* Payload)
{
	using namespace NCsSoundPooledCacheImplCached;

	// NCsPooledObject::NCache::ICache
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();

	// ICsSoundPooledCache
	ICsSoundPooledPayload* FXPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsSoundPooledPayload>(Str::Allocate, Payload);

	DeallocateMethod = FXPayload->GetDeallocateMethod();
	LifeTime		 = FXPayload->GetLifeTime();

	if (USoundBase* Sound = FXPayload->GetSound())
	{
		if (DeallocateMethod == ECsSoundDeallocateMethod::Complete)
		{
			LifeTime = Sound->GetDuration();
		}
	}
}

void FCsSoundPooledCacheImpl::Deallocate()
{
	Reset();
}

void FCsSoundPooledCacheImpl::QueueDeallocate()
{
	bQueueDeallocate = true;
	// Deactivate Audio Component
	checkf(AudioComponent, TEXT("FCsSoundPooledCacheImpl::QueueDeallocate: AudioComponent is NULL."));

	/*
	AudioComponent->Deactivate();

	// LifeTime
	if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
	{
		// Reset ElapsedTime
		ElapsedTime.Reset();
		// Set LifeTime
		LifeTime = QueuedLifeTime;
	}
	*/
}

bool FCsSoundPooledCacheImpl::ShouldDeallocate() const
{
	if (bQueueDeallocate)
	{
		// LifeTime, let HasLifeTimeExpired handle deallocation
		if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
		{
			return false;
		}
		// Complete
		if (DeallocateMethod == ECsSoundDeallocateMethod::Complete)
		{ 
			/*
			checkf(SoundComponent, TEXT("FCsSoundPooledCacheImpl::ShouldDeallocate: SoundComponent is NULL."));

			FNiagaraSystemInstance* SystemInstance = FXComponent->GetSystemInstance();

			checkf(SystemInstance, TEXT("FCsSoundPooledCacheImpl::ShouldDeallocate: SystemInstance is NULL on FXComponent: %s."), *(FXComponent->GetName()));

			const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

			return ExecutionState == ENiagaraExecutionState::Inactive ||
				   ExecutionState == ENiagaraExecutionState::Complete ||
				   ExecutionState == ENiagaraExecutionState::Disabled;
				   */
		}
	}
	return false;
}

bool FCsSoundPooledCacheImpl::HasLifeTimeExpired()
{
	return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
}

void FCsSoundPooledCacheImpl::Reset()
{
	// NCsPooledObject::NCache::ICache
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
	// ICsSoundPooledCache
	AudioComponent = nullptr;
	DeallocateMethod = ECsSoundDeallocateMethod::Complete;
	QueuedLifeTime = 0.0f;
}

#pragma endregion NCsPooledObject::NCache::ICache

void FCsSoundPooledCacheImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}