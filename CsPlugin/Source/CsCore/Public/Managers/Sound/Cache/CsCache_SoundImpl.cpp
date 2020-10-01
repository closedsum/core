// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
			// NCsSound::NCache::ICache
			AudioComponent(nullptr),
			DeallocateMethod(ECsSoundDeallocateMethod::Complete),
			QueuedLifeTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
			InterfaceMap->Add<NCsSound::NCache::ICache>(static_cast<NCsSound::NCache::ICache*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// NCsPooledObject::NCache::ICache
		#pragma region

		void FImpl::Allocate(NCsPooledObject::NPayload::IPayload* Payload)
		{
			using namespace NImplCached;

			// NCsPooledObject::NCache::ICache
			bAllocated = true;
			State	   = ECsPooledObjectState::Active;
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// NCsSound::NCache::ICache
			NCsSound::NPayload::IPayload* FXPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<NCsSound::NPayload::IPayload>(Str::Allocate, Payload);

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
			if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
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
				if (DeallocateMethod == ECsSoundDeallocateMethod::LifeTime)
				{
					return false;
				}
				// Complete
				if (DeallocateMethod == ECsSoundDeallocateMethod::Complete)
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
			// NCsSound::NCache::ICache
			AudioComponent = nullptr;
			DeallocateMethod = ECsSoundDeallocateMethod::Complete;
			QueuedLifeTime = 0.0f;
		}

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}