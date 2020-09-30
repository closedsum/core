// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Cache/CsFXPooledCacheImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/FX/Payload/CsFXPooledPayload.h"
#include "NiagaraComponent.h"
// Component
#include "Components/SceneComponent.h"

const FName FCsFXPooledCacheImpl::Name = FName("FCsFXPooledCacheImpl");

// Cached
#pragma region

namespace NCsFXPooledCacheImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsFXPooledCacheImpl, Allocate);
	}
}

#pragma endregion Cached

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
	ElapsedTime(),
	FXComponent(nullptr),
	DeallocateMethod(ECsFXDeallocateMethod::Complete),
	QueuedLifeTime(0.0f)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsFXPooledCacheImpl::Name);

	InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
	InterfaceMap->Add<ICsFXPooledCache>(static_cast<ICsFXPooledCache*>(this));
}

FCsFXPooledCacheImpl::~FCsFXPooledCacheImpl()
{
	delete InterfaceMap;
}

// NCsPooledObject::NCache::ICache
#pragma region

void FCsFXPooledCacheImpl::Allocate(NCsPooledObject::NPayload::IPayload* Payload)
{
	using namespace NCsFXPooledCacheImplCached;

	// NCsPooledObject::NCache::ICache
	bAllocated = true;
	State	   = ECsPooledObjectState::Active;
	Instigator = Payload->GetInstigator();
	Owner	   = Payload->GetOwner();
	Parent	   = Payload->GetParent();
	StartTime  = Payload->GetTime();

	// ICsFXPooledCache
	ICsFXPooledPayload* FXPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsFXPooledPayload>(Str::Allocate, Payload);

	DeallocateMethod = FXPayload->GetDeallocateMethod();
	QueuedLifeTime   = FXPayload->GetLifeTime();
}

void FCsFXPooledCacheImpl::Deallocate()
{
	Reset();
}

void FCsFXPooledCacheImpl::QueueDeallocate()
{
	bQueueDeallocate = true;
	// Deactivate FX Component
	checkf(FXComponent, TEXT("FCsFXPooledCacheImpl::QueueDeallocate: FXComponent is NULL."));

	FXComponent->Deactivate();

	// LifeTime
	if (DeallocateMethod == ECsFXDeallocateMethod::LifeTime)
	{
		// Reset ElapsedTime
		ElapsedTime.Reset();
		// Set LifeTime
		LifeTime = QueuedLifeTime;
	}
}

bool FCsFXPooledCacheImpl::ShouldDeallocate() const
{
	if (bQueueDeallocate)
	{
		// LifeTime, let HasLifeTimeExpired handle deallocation
		if (DeallocateMethod == ECsFXDeallocateMethod::LifeTime)
		{
			return false;
		}
		// Complete
		if (DeallocateMethod == ECsFXDeallocateMethod::Complete)
		{ 
			checkf(FXComponent, TEXT("FCsFXPooledCacheImpl::ShouldDeallocate: FXComponent is NULL."));

			FNiagaraSystemInstance* SystemInstance = FXComponent->GetSystemInstance();

			checkf(SystemInstance, TEXT("FCsFXPooledCacheImpl::ShouldDeallocate: SystemInstance is NULL on FXComponent: %s."), *(FXComponent->GetName()));

			const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

			return ExecutionState == ENiagaraExecutionState::Inactive ||
				   ExecutionState == ENiagaraExecutionState::Complete ||
				   ExecutionState == ENiagaraExecutionState::Disabled;
		}
	}
	return false;
}

bool FCsFXPooledCacheImpl::HasLifeTimeExpired()
{
	return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
}

void FCsFXPooledCacheImpl::Reset()
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
	// ICsFXPooledCache
	FXComponent = nullptr;
}

#pragma endregion NCsPooledObject::NCache::ICache

void FCsFXPooledCacheImpl::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTime += DeltaTime;
}