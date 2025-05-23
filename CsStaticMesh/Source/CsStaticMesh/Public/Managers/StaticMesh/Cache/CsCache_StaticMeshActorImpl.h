// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Managers/StaticMesh/Cache/CsCache_StaticMeshActor.h"
// Types
#include "CsMacro_Cached.h"
// Container
#include "Containers/CsWeakObjectPtr.h"

class UObject;
struct FCsInterfaceMap;

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsStaticMeshActor, NCache, NImpl, Impl)

namespace NCsStaticMeshActor
{
	namespace NCache
	{
		namespace NImpl
		{
			using PooledCacheType = NCsPooledObject::NCache::ICache;
			using CacheType = NCsStaticMeshActor::NCache::ICache;

			/**
			* Basic implementation for Cache implementing the interfaces:
			* PooledCacheType (NCsPooledObject::NCache::ICache) and 
			* StaticMeshCacheType (NCsStaticMeshActor::NCache::ICache). This only supports 
			* a bare minimum functionality. For custom functionality create
			* another implementation
			*/
			struct CSSTATICMESH_API FImpl final : public PooledCacheType,
												  public CacheType
			{
			public:

				static const FName Name;

			private:

				using StateType = NCsPooledObject::EState;
				using PooledPayloadType = NCsPooledObject::NPayload::IPayload;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsStaticMeshActor, NCache, NImpl, Impl);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// PooledCacheType (NCsPooledObject::NCache::ICache)

				int32 Index;

				bool bAllocated;

				bool bQueueDeallocate;

				StateType State;

				NCsPooledObject::EUpdate UpdateType;

				TCsWeakObjectPtr<UObject> Instigator;

				TCsWeakObjectPtr<UObject> Owner;

				TCsWeakObjectPtr<UObject> Parent;

				float WarmUpTime;

				float LifeTime;

				FCsTime StartTime;

				FCsDeltaTime ElapsedTime;

				// CacheType (NCsStaticMeshActor::NCache::ICache)

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

				void Allocate(PooledPayloadType* Payload);

				FORCEINLINE const bool& IsAllocated() const { return bAllocated; }

				void Deallocate();

				void QueueDeallocate();

				bool ShouldDeallocate() const;

				FORCEINLINE const StateType& GetState() const { return State; }
				FORCEINLINE const NCsPooledObject::EUpdate& GetUpdateType() const { return UpdateType; }
				FORCEINLINE UObject* GetInstigator() const { return Instigator.Get(); }
				FORCEINLINE UObject* GetOwner() const { return Owner.Get(); }
				FORCEINLINE UObject* GetParent() const { return Parent.Get(); }
				FORCEINLINE const float& GetWarmUpTime() const { return WarmUpTime; }
				FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
				FORCEINLINE const FCsTime& GetStartTime() const { return StartTime; }
				FORCEINLINE const FCsDeltaTime& GetElapsedTime() const { return ElapsedTime; }

				bool HasLifeTimeExpired() const;

				void Reset();

			#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

			public:

				FORCEINLINE void SetLifeTime(const float& InLifeTime) { LifeTime = InLifeTime; }

			// CacheType (NCsStaticMeshActor::NCache::ICache)
			#pragma region
			public:

			#pragma endregion CacheType (NCsStaticMeshActor::NCache::ICache)

			public:

				void Update(const FCsDeltaTime& DeltaTime);
			};
		}
	}
}