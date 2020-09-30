// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Cache/CsCache_Projectile.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsPooledObject {
	namespace NPayload {
		struct IPayload; } }

class ICsData_Projectile;

namespace NCsProjectile
{
	namespace NCache
	{
		struct CSPRJ_API FImplPooled final : public NCsPooledObject::NCache::ICache,
											 public NCsProjectile::NCache::ICache
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

			int32 Index;

			bool bAllocated;

			bool bQueueDeallocate;

			ECsPooledObjectState State;

			ECsPooledObjectUpdate UpdateType;

			TCsWeakObjectPtr<UObject> Instigator;

			TCsWeakObjectPtr<UObject> Owner;

			TCsWeakObjectPtr<UObject> Parent;

			float WarmUpTime;

			float LifeTime;

			FCsTime StartTime;

			FCsDeltaTime ElapsedTime;

			ICsData_Projectile* Data;

		public:

			FImplPooled();

			~FImplPooled();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		// NCsPooledObject::NCache::ICache
		#pragma region
		public:

			FORCEINLINE void Init(const int32& InIndex)
			{
				Index = InIndex;
			}

			FORCEINLINE const int32& GetIndex() const
			{
				return Index;
			}

			void Allocate(NCsPooledObject::NPayload::IPayload* Payload);

			FORCEINLINE const bool& IsAllocated() const
			{
				return bAllocated;
			}

			void Deallocate();

			FORCEINLINE void QueueDeallocate()
			{
				bQueueDeallocate = true;
			}

			FORCEINLINE bool ShouldDeallocate() const
			{
				return bQueueDeallocate;
			}

			FORCEINLINE const ECsPooledObjectState& GetState() const
			{
				return State;
			}

			FORCEINLINE const ECsPooledObjectUpdate& GetUpdateType() const
			{
				return UpdateType;
			}

			FORCEINLINE UObject* GetInstigator() const
			{
				return Instigator.Get();
			}

			FORCEINLINE UObject* GetOwner() const
			{
				return Owner.Get();
			}

			FORCEINLINE UObject* GetParent() const
			{
				return Parent.Get();
			}

			FORCEINLINE const float& GetWarmUpTime() const
			{
				return WarmUpTime;
			}

			FORCEINLINE const float& GetLifeTime() const
			{
				return LifeTime;
			}

			FORCEINLINE const FCsTime& GetStartTime() const
			{
				return StartTime;
			}

			FORCEINLINE const FCsDeltaTime& GetElapsedTime() const
			{
				return ElapsedTime;
			}

			bool HasLifeTimeExpired();

			void Reset();

		#pragma endregion NCsPooledObject::NCache::ICache

		// NCsProjectile::NCache::ICache
		#pragma region
		public:

		#pragma endregion NCsProjectile::NCache::ICache

		public:

			void Update(const FCsDeltaTime& DeltaTime);

			void SetData(ICsData_Projectile* InData);
		};
	}
}