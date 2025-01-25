// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsCache_ProjectileImpl.h"

// Types
#include "CsMacro_Interface.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Data
#include "Data/CsData_Projectile.h"

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NCache::NImpl::FImpl);

namespace NCsProjectile
{
	namespace NCache
	{	
		namespace NImpl
		{
			FImpl::FImpl() :
				// ICsGetInterfaceMap
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
				ElapsedTime(),
				Data(nullptr)
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

			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using DataType = NCsProjectile::NData::IData;

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			#pragma region

			void FImpl::Allocate(PooledPayloadType* Payload)
			{
				bAllocated = true;
				State	   = StateType::Active;
				UpdateType = Payload->GetUpdateType();
				Instigator = Payload->GetInstigator();
				Owner	   = Payload->GetOwner();
				Parent	   = Payload->GetParent();
				StartTime  = Payload->GetTime();
			}

			void FImpl::Deallocate()
			{
				Reset();
			}

			bool FImpl::HasLifeTimeExpired() const
			{
				return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
			}

			void FImpl::Reset()
			{
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
			}

			#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

			void FImpl::Update(const FCsDeltaTime& DeltaTime)
			{
				ElapsedTime += DeltaTime;
			}

			void FImpl::SetData(DataType* InData)
			{
				Data	 = InData;
				LifeTime = Data->GetLifeTime();
			}
		}
	}
}