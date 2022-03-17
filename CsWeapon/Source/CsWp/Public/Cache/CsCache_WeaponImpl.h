// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Pool
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
// Weapon
#include "Cache/CsCache_Weapon.h"
// Container
#include "Containers/CsWeakObjectPtr.h"

class UObject;
struct FCsInterfaceMap;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsWeapon
{
	namespace NCache
	{
	#define PooledCacheType NCsPooledObject::NCache::ICache
	#define WeaponCacheType NCsWeapon::NCache::ICache

		struct CSWP_API FImpl final : public PooledCacheType,
									  public WeaponCacheType
		{
		public:

			static const FName Name;

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// PooledCacheType (NCsPooledObject::NCache::ICache)

			int32 Index;

			bool bAllocated;

			bool bQueueDeallocate;

			NCsPooledObject::EState State;

			NCsPooledObject::EUpdate UpdateType;

			TCsWeakObjectPtr<UObject> Instigator;

			TCsWeakObjectPtr<UObject> Owner;

			TCsWeakObjectPtr<UObject> Parent;

			float WarmUpTime;

			float LifeTime;

			FCsTime StartTime;

			FCsDeltaTime ElapsedTime;

			// WeaponCacheType (NCsWeapon::NCache::ICache)

		public:

			FImpl();
			~FImpl();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// PooledCacheType (NCsPooledObject::NCache::ICache)
		#pragma region
		public:

			FORCEINLINE void Init(const int32& InIndex){ Index = InIndex; }
			FORCEINLINE const int32& GetIndex() const { return Index; }

			void Allocate(PooledPayloadType* Payload);

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }

			void Deallocate();

			FORCEINLINE void QueueDeallocate(){ bQueueDeallocate = true; }
			FORCEINLINE bool ShouldDeallocate() const { return bQueueDeallocate; }
			FORCEINLINE const NCsPooledObject::EState& GetState() const { return State; }
			FORCEINLINE const NCsPooledObject::EUpdate& GetUpdateType() const { return UpdateType; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator.Get(); }
			FORCEINLINE UObject* GetOwner() const { return Owner.Get(); }
			FORCEINLINE UObject* GetParent() const { return Parent.Get(); }
			FORCEINLINE const float& GetWarmUpTime() const { return WarmUpTime; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const FCsTime& GetStartTime() const { return StartTime; }
			FORCEINLINE const FCsDeltaTime& GetElapsedTime() const { return ElapsedTime; }

			bool HasLifeTimeExpired();

			void Reset();

		#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

		// WeaponCacheType (NCsWeapon::NCache::ICache)
		#pragma region
		public:

		#pragma endregion WeaponCacheType (NCsWeapon::NCache::ICache)

		public:

			void Update(const FCsDeltaTime& DeltaTime);

		#undef PooledPayloadType
		};

#undef PooledCacheType
#undef WeaponCacheType
	}
}