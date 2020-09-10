// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Cache/CsCache_StaticMeshActorImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Sound
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"
//#include "Components/AudioComponent.h"
// Component
//#include "Components/SceneComponent.h"

const FName FCsCache_StaticMeshActorImpl::Name = FName("FCsCache_StaticMeshActorImpl");

// Cached
#pragma region

namespace NCsCacheStaticMeshActorImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_STRING(Allocate, "FCsCache_StaticMeshActorImpl::Allocate");
	}
}

#pragma endregion Cached

FCsCache_StaticMeshActorImpl::FCsCache_StaticMeshActorImpl() :
	InterfaceMap(nullptr),
	// ICsPooledObjectCache
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
	// ICsCache_StaticMeshActor
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsCache_StaticMeshActorImpl::Name);

	InterfaceMap->Add<ICsPooledObjectCache>(static_cast<ICsPooledObjectCache*>(this));
	InterfaceMap->Add<ICsCache_StaticMeshActor>(static_cast<ICsCache_StaticMeshActor*>(this));
}

FCsCache_StaticMeshActorImpl::~FCsCache_StaticMeshActorImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectCache
#pragma region

void FCsCache_StaticMeshActorImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsCacheStaticMeshActorImplCached;

	// ICsPooledObjectCache
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();

	// ICsCache_StaticMeshActor
	/*
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
	*/
}

void FCsCache_StaticMeshActorImpl::Deallocate()
{
	Reset();
}

void FCsCache_StaticMeshActorImpl::QueueDeallocate()
{
	//bQueueDeallocate = true;
	// Deactivate Audio Component
	//checkf(AudioComponent, TEXT("FCsSoundPooledCacheImpl::QueueDeallocate: AudioComponent is NULL."));

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

bool FCsCache_StaticMeshActorImpl::ShouldDeallocate() const
{
	//if (bQueueDeallocate)
	{
		// LifeTime, let HasLifeTimeExpired handle deallocation
		//if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
		{
			return false;
		}
		// Complete
		//if (DeallocateMethod == ECsSoundDeallocateMethod::Complete)
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

bool FCsCache_StaticMeshActorImpl::HasLifeTimeExpired()
{
	return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
}

void FCsCache_StaticMeshActorImpl::Reset()
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
	// ICsCache_StaticMeshActor
	//AudioComponent = nullptr;
	//DeallocateMethod = ECsSoundDeallocateMethod::Complete;
	//QueuedLifeTime = 0.0f;
}

#pragma endregion ICsPooledObjectCache

void FCsCache_StaticMeshActorImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}