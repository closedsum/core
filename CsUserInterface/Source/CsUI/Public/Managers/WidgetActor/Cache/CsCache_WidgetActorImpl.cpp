// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledCacheType (NCsPooledObject::NCache::ICache)
			Index(INDEX_NONE),
			bAllocated(false),
			bQueueDeallocate(false),
			State(ECsPooledObjectState::Inactive),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(),
			Owner(),
			Parent(),
			WarmUpTime(0.0f),
			LifeTime(0.0f),
			StartTime(),
			ElapsedTime(),
			// WidgetActorCacheType (NCsWidgetActor::NCache::ICache)
			DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
			QueuedLifeTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsWidgetActor::NCache::ICache WidgetActorCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<WidgetActorCacheType>(static_cast<WidgetActorCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledCacheType (NCsPooledObject::NCache::ICache)
		#pragma region

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PooledPayloadType* Payload)
		{
		#undef PooledPayloadType

			using namespace NImplCached;

			const FString& Context = Str::Allocate;

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = true;
			State	   = ECsPooledObjectState::Active;
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// WidgetActorCacheType (NCsWidgetActor::NPayload::IPayload)
			typedef NCsWidgetActor::NPayload::IPayload WidgetPayloadType;
			typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

			WidgetPayloadType* WidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<WidgetPayloadType>(Context, Payload);

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
			// PooledCacheType (NCsPooledObject::NCache::ICache)
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
			// WidgetActorCacheType (NCsWidgetActor::NPayload::IPayload)
			DeallocateMethod = ECsWidgetActorDeallocateMethod::ECsWidgetActorDeallocateMethod_MAX;
			QueuedLifeTime = 0.0f;
		}

		#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}