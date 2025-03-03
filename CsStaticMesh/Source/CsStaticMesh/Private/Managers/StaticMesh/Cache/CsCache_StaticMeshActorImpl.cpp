// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Cache/CsCache_StaticMeshActorImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsStaticMeshActor::NCache::NImpl::FImpl);

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsStaticMeshActor, NCache, NImpl, Impl)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsStaticMeshActor::NCache::NImpl::FImpl, Allocate)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

namespace NCsStaticMeshActor
{
	namespace NCache
	{
		namespace NImpl
		{
			FImpl::FImpl() :
				InterfaceMap(nullptr),
				// PooledCacheType (NCsPooledObject::NCache::ICache)
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
				ElapsedTime()
				// StaticMeshCacheType (NCsStaticMeshActor::NCache::ICache)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(PooledCacheType);
				CS_INTERFACE_MAP_ADD(CacheType);
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			}

			using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
			using PayloadType = NCsStaticMeshActor::NPayload::IPayload;

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			#pragma region

			void FImpl::Allocate(PooledPayloadType* Payload)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Allocate);

				// PooledCacheType (NCsPooledObject::NCache::ICache)
				bAllocated = true;
				State	   = NCsPooledObject::EState::Active;
				UpdateType = Payload->GetUpdateType();
				Instigator = Payload->GetInstigator();
				Owner	   = Payload->GetOwner();
				Parent	   = Payload->GetParent();
				StartTime  = Payload->GetTime();

				// CacheType (NCsStaticMeshActor::NCache::ICache)
				PayloadType* StaticMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

				LifeTime = StaticMeshPayload->GetLifeTime();
			}

			void FImpl::Deallocate()
			{
				Reset();
			}

			void FImpl::QueueDeallocate()
			{
				bQueueDeallocate = true;
			}

			bool FImpl::ShouldDeallocate() const
			{
				return bQueueDeallocate;
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
				State = StateType::Inactive;
				UpdateType = NCsPooledObject::EUpdate::Manager;
				Instigator.Reset();
				Owner.Reset();
				Parent.Reset();
				WarmUpTime = 0.0f;
				LifeTime = 0.0f;
				StartTime.Reset();
				ElapsedTime.Reset();
				// StaticMeshCacheType (NCsStaticMeshActor::NCache::ICache)
			}

			#pragma endregion NCsPooledObject::NCache::ICache

			void FImpl::Update(const FCsDeltaTime& DeltaTime)
			{
				ElapsedTime += DeltaTime;
			}
		}
	}
}