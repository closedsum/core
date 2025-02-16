// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/Cache/CsCache_SoundImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
// Component
#include "Components/SceneComponent.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsSound::NCache::NImpl::FImpl);

namespace NCsSound
{
	namespace NCache
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_STRING(Allocate, "Allocate");
				}
			}

			FImpl::FImpl() :
				InterfaceMap(nullptr),
				// PooledPayloadType (NCsPooledObject::NCache::ICache)
				Index(INDEX_NONE),
				bAllocated(false),
				bQueueDeallocate(false),
				State(StateType::Inactive),
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

			using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsSound::NPayload::IPayload;

			// PooledPayloadType (NCsPooledObject::NCache::ICache)
			#pragma region

			void FImpl::Allocate(PooledPayloadType* Payload)
			{
				using namespace NCsSound::NCache::NImpl::NCached;

				// PooledPayloadType (NCsPooledObject::NCache::ICache)
				bAllocated = true;
				UpdateType = Payload->GetUpdateType();
				State	   = StateType::Active;
				Instigator = Payload->GetInstigator();
				Owner	   = Payload->GetOwner();
				Parent	   = Payload->GetParent();
				StartTime  = Payload->GetTime();

				// SoundCacheType (NCsSound::NCache::ICache)
				PayloadType* SoundPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Str::Allocate, Payload);

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
				checkf(AudioComponent, TEXT("NCsSound::NCache::NImpl::FImpl::QueueDeallocate: AudioComponent is NULL."));

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
						checkf(SoundComponent, TEXT("NCsSound::NCache::NImpl::FImpl::ShouldDeallocate: SoundComponent is NULL."));

						FNiagaraSystemInstance* SystemInstance = FXComponent->GetSystemInstance();

						checkf(SystemInstance, TEXT("NCsSound::NCache::NImpl::FImpl::ShouldDeallocate: SystemInstance is NULL on FXComponent: %s."), *(FXComponent->GetName()));

						const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

						return ExecutionState == ENiagaraExecutionState::Inactive ||
							   ExecutionState == ENiagaraExecutionState::Complete ||
							   ExecutionState == ENiagaraExecutionState::Disabled;
							   */
					}
				}
				return false;
			}

			bool FImpl::HasLifeTimeExpired() const
			{
				return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
			}

			void FImpl::Reset()
			{
				// PooledPayloadType (NCsPooledObject::NCache::ICache)
				bAllocated = false;
				bQueueDeallocate = false;
				State = StateType::Inactive;
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
}