// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Cache/CsCache_SoundImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Components/AudioComponent.h"
// Component
#include "Components/SceneComponent.h"

const FName NCsSound::NCache::FImpl::Name = FName("NCsSound::NCache::FImpl");

namespace NCsSound
{
	namespace NCache
	{
		namespace NImplCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSound::NCache::FImpl, Allocate);
			}
		}

		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NCache::ICache)
			Index(INDEX_NONE),
			bAllocated(false),
			bQueueDeallocate(false),
			State(NCsPooledObject::EState::Inactive),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(),
			Owner(),
			Parent(),
			WarmUpTime(0.0f),
			LifeTime(0.0f),
			StartTime(),
			ElapsedTime(),
			// SoundCacheType (NCsSound::NCache::ICache)
			AudioComponent(nullptr),
			DeallocateMethod(EDeallocateMethod::Complete),
			QueuedLifeTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsSound::NCache::ICache SoundCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<SoundCacheType>(static_cast<SoundCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledPayloadType (NCsPooledObject::NCache::ICache)
		#pragma region

		#define PayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PayloadType* Payload)
		{
		#undef PayloadType
			using namespace NImplCached;

			// PooledPayloadType (NCsPooledObject::NCache::ICache)
			bAllocated = true;
			UpdateType = Payload->GetUpdateType();
			State	   = NCsPooledObject::EState::Active;
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// SoundCacheType (NCsSound::NCache::ICache)
			typedef NCsSound::NPayload::IPayload SoundPayloadType;
			typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

			SoundPayloadType* SoundPayload = PooledPayloadLibrary::GetInterfaceChecked<SoundPayloadType>(Str::Allocate, Payload);

			DeallocateMethod = SoundPayload->GetDeallocateMethod();
			LifeTime		 = SoundPayload->GetLifeTime();

			if (USoundBase* Sound = SoundPayload->GetSound())
			{
				if (DeallocateMethod == EDeallocateMethod::Complete)
				{
					LifeTime = SoundPayload->GetDurationMultiplier() * Sound->GetDuration();
				}
			}
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			bQueueDeallocate = true;
			// Deactivate Audio Component
			checkf(AudioComponent, TEXT("NCsSound::NCache::FImpl::QueueDeallocate: AudioComponent is NULL."));

			/*
			AudioComponent->Deactivate();

			// LifeTime
			if (DeallocateMethod == EDeallocateMethod::LifeTime)
			{
				// Reset ElapsedTime
				ElapsedTime.Reset();
				// Set LifeTime
				LifeTime = QueuedLifeTime;
			}
			*/
		}

		bool FImpl::ShouldDeallocate() const
		{
			if (bQueueDeallocate)
			{
				// LifeTime, let HasLifeTimeExpired handle deallocation
				if (DeallocateMethod == EDeallocateMethod::LifeTime)
				{
					return false;
				}
				// Complete
				if (DeallocateMethod == EDeallocateMethod::Complete)
				{ 
					/*
					checkf(SoundComponent, TEXT("NCsSound::NCache::FImpl::ShouldDeallocate: SoundComponent is NULL."));

					FNiagaraSystemInstance* SystemInstance = FXComponent->GetSystemInstance();

					checkf(SystemInstance, TEXT("NCsSound::NCache::FImpl::ShouldDeallocate: SystemInstance is NULL on FXComponent: %s."), *(FXComponent->GetName()));

					const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

					return ExecutionState == ENiagaraExecutionState::Inactive ||
						   ExecutionState == ENiagaraExecutionState::Complete ||
						   ExecutionState == ENiagaraExecutionState::Disabled;
						   */
				}
			}
			return false;
		}

		bool FImpl::HasLifeTimeExpired()
		{
			return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
		}

		void FImpl::Reset()
		{
			// PooledPayloadType (NCsPooledObject::NCache::ICache)
			bAllocated = false;
			bQueueDeallocate = false;
			State = NCsPooledObject::EState::Inactive;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator.Reset();
			Owner.Reset();
			Parent.Reset();
			WarmUpTime = 0.0f;
			LifeTime = 0.0f;
			StartTime.Reset();
			ElapsedTime.Reset();
			// SoundCacheType (NCsSound::NCache::ICache)
			DeallocateMethod = EDeallocateMethod::Complete;
			QueuedLifeTime = 0.0f;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NCache::ICache)

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}