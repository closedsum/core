// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Managers/SkeletalMesh/Cache/CsCache_SkeletalMeshActor.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsSkeletalMeshActor
{
	namespace NCache
	{
	#define PooledCacheType NCsPooledObject::NCache::ICache
	#define SkeletalMeshCacheType NCsSkeletalMeshActor::NCache::ICache

		/**
		* Basic implementation for Cache implementing the interfaces:
		* PooledCacheType (NCsPooledObject::NCache::ICache) and 
		* SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache). This only supports 
		* a bare minimum functionality. For custom functionality create
		* another implementation
		*/
		struct CSCORE_API FImpl final : public PooledCacheType,
										public SkeletalMeshCacheType
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// PooledCacheType (NCsPooledObject::NCache::ICache)

			int32 Index;

			bool bAllocated;

			bool bQueueDeallocate;

			ECsPooledObjectState State;

			NCsPooledObject::EUpdate UpdateType;

			TCsWeakObjectPtr<UObject> Instigator;

			TCsWeakObjectPtr<UObject> Owner;

			TCsWeakObjectPtr<UObject> Parent;

			float WarmUpTime;

			float LifeTime;

			FCsTime StartTime;

			FCsDeltaTime ElapsedTime;

			// SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache)

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

			FORCEINLINE void Init(const int32& InIndex) { Index = InIndex; }
			FORCEINLINE const int32& GetIndex() const { return Index; }

			void Allocate(NCsPooledObject::NPayload::IPayload* Payload);

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }

			void Deallocate();

			void QueueDeallocate();

			bool ShouldDeallocate() const;

			FORCEINLINE const ECsPooledObjectState& GetState() const { return State; }
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

		public:

			FORCEINLINE void SetLifeTime(const float& InLifeTime) { LifeTime = InLifeTime; }

		// SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache)
		#pragma region
		public:

		#pragma endregion SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache)

		public:

			void Update(const FCsDeltaTime& DeltaTime);
		};

	#undef PooledCacheType
	#undef SkeletalMeshCacheType
	}
}