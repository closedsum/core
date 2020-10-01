// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Cache/CsCache_FXImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "NiagaraComponent.h"
// Component
#include "Components/SceneComponent.h"

const FName NCsFX::NCache::FImpl::Name = FName("NCsFX::NCache::FImpl");

namespace NCsFX
{
	namespace NCache
	{
		namespace NImplCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NCache::FImpl, Allocate);
			}
		}

		FImpl::FImpl() :
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

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
			InterfaceMap->Add<NCsFX::NCache::ICache>(static_cast<NCsFX::NCache::ICache*>(this));
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

			// NCsFX::NCache::ICache
			NCsFX::NPayload::IPayload* FXPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<NCsFX::NPayload::IPayload>(Str::Allocate, Payload);

			DeallocateMethod = FXPayload->GetDeallocateMethod();
			QueuedLifeTime   = FXPayload->GetLifeTime();
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			bQueueDeallocate = true;
			// Deactivate FX Component
			checkf(FXComponent, TEXT("NCsFX::NCache::FImpl::QueueDeallocate: FXComponent is NULL."));

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

		bool FImpl::ShouldDeallocate() const
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
					checkf(FXComponent, TEXT("NCsFX::NCache::FImpl::ShouldDeallocate: FXComponent is NULL."));

					FNiagaraSystemInstance* SystemInstance = FXComponent->GetSystemInstance();

					checkf(SystemInstance, TEXT("NCsFX::NCache::FImpl::ShouldDeallocate: SystemInstance is NULL on FXComponent: %s."), *(FXComponent->GetName()));

					const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

					return ExecutionState == ENiagaraExecutionState::Inactive ||
						   ExecutionState == ENiagaraExecutionState::Complete ||
						   ExecutionState == ENiagaraExecutionState::Disabled;
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
			// NCsFX::NCache::ICache
			FXComponent = nullptr;
		}

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}