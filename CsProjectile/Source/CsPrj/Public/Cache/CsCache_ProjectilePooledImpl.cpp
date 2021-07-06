// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsCache_ProjectilePooledImpl.h"

#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Containers/CsInterfaceMap.h"
// Data
#include "Data/CsData_Projectile.h"

const FName NCsProjectile::NCache::FImplPooled::Name = FName("NCsProjectile::NCache::FImplPooled");

namespace NCsProjectile
{
	namespace NCache
	{
		FImplPooled::FImplPooled() :
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
			Data(nullptr)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImplPooled>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsProjectile::NCache::ICache ProjectileCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<ProjectileCacheType>(static_cast<ProjectileCacheType*>(this));
		}

		FImplPooled::~FImplPooled()
		{
			delete InterfaceMap;
		}

		// PooledCacheType (NCsPooledObject::NCache::ICache)s
		#pragma region

		#define PayloadType NCsPooledObject::NPayload::IPayload
		void FImplPooled::Allocate(PayloadType* Payload)
		{
		#undef PayloadType

			bAllocated = true;
			State	   = ECsPooledObjectState::Active;
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();
		}

		void FImplPooled::Deallocate()
		{
			Reset();
		}

		bool FImplPooled::HasLifeTimeExpired()
		{
			return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
		}

		void FImplPooled::Reset()
		{
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
		}

		#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

		void FImplPooled::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}

		#define DataType NCsProjectile::NData::IData
		void FImplPooled::SetData(DataType* InData)
		{
		#undef DataType

			Data	 = InData;
			LifeTime = Data->GetLifeTime();
		}
	}
}