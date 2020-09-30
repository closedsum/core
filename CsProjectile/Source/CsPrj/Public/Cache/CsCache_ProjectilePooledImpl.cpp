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
			Data(nullptr)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImplPooled::Name);

			InterfaceMap->Add<NCsPooledObject::NCache::ICache>(static_cast<NCsPooledObject::NCache::ICache*>(this));
			InterfaceMap->Add<NCsProjectile::NCache::ICache>(static_cast<NCsProjectile::NCache::ICache*>(this));
		}

		FImplPooled::~FImplPooled()
		{
			delete InterfaceMap;
		}

		// NCsPooledObject::NCache::ICache
		#pragma region

		void FImplPooled::Allocate(NCsPooledObject::NPayload::IPayload* Payload)
		{
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
			if (LifeTime > 0.0f)
			{
				return ElapsedTime.Time > LifeTime;
			}
			return false;
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

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImplPooled::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}

		void FImplPooled::SetData(ICsData_Projectile* InData)
		{
			Data	 = InData;
			LifeTime = Data->GetLifeTime();
		}
	}
}