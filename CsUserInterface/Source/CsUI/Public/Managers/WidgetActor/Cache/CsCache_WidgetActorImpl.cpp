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

const FName NCsWidgetActor::NCache::FImpl::Name = FName("NCsWidgetActor::NCache::FImpl");

namespace NCsWidgetActor
{
	namespace NCache
	{
		namespace NImplCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidgetActor::NCache::FImpl, Allocate);
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
			DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
			QueuedLifeTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
			InterfaceMap->Add<NCsWidgetActor::NCache::ICache>(static_cast<NCsWidgetActor::NCache::ICache*>(this));
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

			const FString& Context = Str::Allocate;

			// NCsPooledObject::NCache::ICache
			bAllocated = true;
			State	   = ECsPooledObjectState::Active;
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// NCsWidgetActor::NPayload::IPayload
			NCsWidgetActor::NPayload::IPayload* WidgetPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<NCsWidgetActor::NPayload::IPayload>(Context, Payload);

			DeallocateMethod = WidgetPayload->GetDeallocateMethod();
			QueuedLifeTime   = WidgetPayload->GetLifeTime();
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
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

		bool FImpl::ShouldDeallocate() const
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
			// ICsCache_WidgetActor
			DeallocateMethod = ECsWidgetActorDeallocateMethod::ECsWidgetActorDeallocateMethod_MAX;
			QueuedLifeTime = 0.0f;
		}

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}