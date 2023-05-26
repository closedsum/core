// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Cache/CsCache_StaticMeshActorImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"

const FName NCsStaticMeshActor::NCache::FImpl::Name = FName("NCsStaticMeshActor::NCache::FImpl");

namespace NCsStaticMeshActor
{
	namespace NCache
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NCache::FImpl, Allocate);
				}
			}
		}

		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// PooledCacheType (NCsPooledObject::NCache::ICache)
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
			ElapsedTime()
			// StaticMeshCacheType (NCsStaticMeshActor::NCache::ICache)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsStaticMeshActor::NCache::ICache StaticMeshCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<StaticMeshCacheType>(static_cast<StaticMeshCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledCacheType (NCsPooledObject::NCache::ICache)
		#pragma region

		#define PayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PayloadType* Payload)
		{
		#undef PayloadType

			using namespace NImpl::NCached;

			const FString& Context = Str::Allocate;

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = true;
			State	   = NCsPooledObject::EState::Active;
			UpdateType = Payload->GetUpdateType();
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// StaticMeshCacheType (NCsStaticMeshActor::NCache::ICache)
			typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
			typedef NCsStaticMeshActor::NPayload::IPayload StaticMeshPayloadType;

			StaticMeshPayloadType* StaticMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<StaticMeshPayloadType>(Context, Payload);

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

		bool FImpl::HasLifeTimeExpired()
		{
			return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
		}

		void FImpl::Reset()
		{
			// PooledCacheType (NCsPooledObject::NCache::ICache)
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
			// StaticMeshCacheType (NCsStaticMeshActor::NCache::ICache)
		}

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}