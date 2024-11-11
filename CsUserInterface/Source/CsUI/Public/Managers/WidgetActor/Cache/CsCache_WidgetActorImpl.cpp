// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/Cache/CsCache_WidgetActorImpl.h"

// Types
#include "CsMacro_Interface.h"
#include "CsMacro_Misc.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
// Component
#include "Components/CsWidgetComponent.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWidgetActor::NCache::NImpl::FImpl);

namespace NCsWidgetActor
{
	namespace NCache
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidgetActor::NCache::FImpl, Allocate);
				}
			}

			using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
			using PayloadType = NCsWidgetActor::NPayload::IPayload;

			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// PooledCacheType (NCsPooledObject::NCache::ICache)
				Index(INDEX_NONE),
				bAllocated(false),
				bQueueDeallocate(false),
				State(PooledStateType::Inactive),
				UpdateType(PooledUpdateType::Manager),
				Instigator(),
				Owner(),
				Parent(),
				WarmUpTime(0.0f),
				LifeTime(0.0f),
				StartTime(),
				ElapsedTime(),
				// WidgetActorCacheType (NCsWidgetActor::NCache::ICache)
				DeallocateMethod(DeallocateMethodType::Complete),
				QueuedLifeTime(0.0f)
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
				InterfaceMap->Add<CacheType>(static_cast<CacheType*>(this));
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			}

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			#pragma region

			void FImpl::Allocate(PooledPayloadType* Payload)
			{
				using namespace NImpl::NCached;

				const FString& Context = Str::Allocate;

				// PooledCacheType (NCsPooledObject::NCache::ICache)
				bAllocated = true;
				State	   = PooledStateType::Active;
				UpdateType = Payload->GetUpdateType();
				Instigator = Payload->GetInstigator();
				Owner	   = Payload->GetOwner();
				Parent	   = Payload->GetParent();
				StartTime  = Payload->GetTime();

				// CacheType (NCsWidgetActor::NPayload::IPayload)

				PayloadType* WidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

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
				if (DeallocateMethod == DeallocateMethodType::LifeTime)
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
					if (DeallocateMethod == DeallocateMethodType::LifeTime)
					{
						return false;
					}
					return bQueueDeallocate;
				}
				return false;
			}

			bool FImpl::HasLifeTimeExpired() const
			{
				return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
			}

			void FImpl::Reset()
			{
				// PooledCacheType (NCsPooledObject::NCache::ICache)
				bAllocated = false;
				bQueueDeallocate = false;
				State = PooledStateType::Inactive;
				UpdateType = PooledUpdateType::Manager;
				Instigator.Reset();
				Owner.Reset();
				Parent.Reset();
				WarmUpTime = 0.0f;
				LifeTime = 0.0f;
				StartTime.Reset();
				ElapsedTime.Reset();
				// WidgetActorCacheType (NCsWidgetActor::NPayload::IPayload)
				DeallocateMethod = DeallocateMethodType::ECsWidgetActorDeallocateMethod_MAX;
				QueuedLifeTime = 0.0f;
			}

			#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

			void FImpl::Update(const FCsDeltaTime& DeltaTime)
			{
				ElapsedTime += DeltaTime;
			}
		}
	}
}