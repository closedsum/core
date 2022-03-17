// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Cache/CsCache_WeaponImpl.h"

// Data
#include "Data/CsData_Weapon.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NCache::FImpl::Name = FName("NCsWeapon::NCache::FImpl");

namespace NCsWeapon
{
	namespace NCache
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledCacheType (NCsPooledObject::NCache::ICache)
			Index(INDEX_NONE),
			bAllocated(false),
			bQueueDeallocate(false),
			State(NCsPooledObject::EState::Inactive),
			UpdateType(NCsPooledObject::EUpdate::Owner),
			Instigator(),
			Owner(),
			Parent(),
			WarmUpTime(0.0f),
			LifeTime(0.0f),
			StartTime(),
			ElapsedTime()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsWeapon::NCache::ICache WeaponCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<WeaponCacheType>(static_cast<WeaponCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledCacheType (NCsPooledObject::NCache::ICache)s
		#pragma region

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PooledPayloadType* Payload)
		{
		#undef PooledPayloadType

			bAllocated = true;
			State	   = NCsPooledObject::EState::Active;
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

		bool FImpl::HasLifeTimeExpired()
		{
			if (LifeTime > 0.0f)
			{
				return ElapsedTime.Time > LifeTime;
			}
			return false;
		}

		void FImpl::Reset()
		{
			bAllocated = false;
			bQueueDeallocate = false;
			State = NCsPooledObject::EState::Inactive;
			UpdateType = NCsPooledObject::EUpdate::Owner;
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
	}
}