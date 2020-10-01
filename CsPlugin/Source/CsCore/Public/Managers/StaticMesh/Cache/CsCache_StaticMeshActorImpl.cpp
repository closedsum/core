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

const FName NCsStaticMeshActor::NCache::FImpl::Name = FName("NCsStaticMeshActor::NCache::FImpl");

namespace NCsStaticMeshActor
{
	namespace NCache
	{
		namespace NImplCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NCache::FImpl, Allocate);
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
			ElapsedTime()
			// NCsStaticMeshActor::NCache::ICache
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
			InterfaceMap->Add<NCsStaticMeshActor::NCache::ICache>(static_cast<NCsStaticMeshActor::NCache::ICache*>(this));
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

			// NCsStaticMeshActor::NCache::ICache
			/*
			*/
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			//bQueueDeallocate = true;
			// Deactivate Audio Component
			//checkf(AudioComponent, TEXT("NCsStaticMeshActor::NCache::FImpl::QueueDeallocate: AudioComponent is NULL."));

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
					checkf(SoundComponent, TEXT("NCsStaticMeshActor::NCache::FImpl::ShouldDeallocate: SoundComponent is NULL."));

					FNiagaraSystemInstance* SystemInstance = FXComponent->GetSystemInstance();

					checkf(SystemInstance, TEXT("NCsStaticMeshActor::NCache::FImpl::ShouldDeallocate: SystemInstance is NULL on FXComponent: %s."), *(FXComponent->GetName()));

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
			// NCsStaticMeshActor::NCache::ICache
			//AudioComponent = nullptr;
			//DeallocateMethod = ECsSoundDeallocateMethod::Complete;
			//QueuedLifeTime = 0.0f;
		}

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}