// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"
// Pool
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
// WidgetActor
#include "Managers/WidgetActor/Cache/CsCache_WidgetActor.h"
// Container
#include "Containers/CsWeakObjectPtr.h"

class UObject;
struct FCsInterfaceMap;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class UCsWidgetComponent;

namespace NCsWidgetActor
{
	namespace NCache
	{
		namespace NImpl
		{
			using PooledCacheType = NCsPooledObject::NCache::ICache;
			using CacheType = NCsWidgetActor::NCache::ICache;
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;

			/**
			* Basic implementation for Cache implementing the interfaces:
			* PooledCacheType (NCsPooledObject::NCache::ICache) and 
			* WidgetActorCacheType (NCsWidgetActor::NCache::ICache). This only supports 
			* a bare minimum functionality. For custom functionality create
			* another implementation
			*/
			struct CSUI_API FImpl final : public PooledCacheType,
										  public CacheType
			{
			public:

				static const FName Name;

			private:

				using PooledStateType = NCsPooledObject::EState;
				using PooledUpdateType = NCsPooledObject::EUpdate;
				using DeallocateMethodType = ECsWidgetActorDeallocateMethod;

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// PooledCacheType (NCsPooledObject::NCache::ICache)

				int32 Index;

				bool bAllocated;

				bool bQueueDeallocate;

				PooledStateType State;

				PooledUpdateType UpdateType;

				TCsWeakObjectPtr<UObject> Instigator;

				TCsWeakObjectPtr<UObject> Owner;

				TCsWeakObjectPtr<UObject> Parent;

				float WarmUpTime;

				float LifeTime;

				FCsTime StartTime;

				FCsDeltaTime ElapsedTime;

				// CacheType (NCsWidgetActor::NCache::ICache)

				// TODO:

				DeallocateMethodType DeallocateMethod;

				float QueuedLifeTime;

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

				FORCEINLINE const PooledStateType& GetState() const { return State; }
				FORCEINLINE const PooledUpdateType& GetUpdateType() const { return UpdateType; }
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

			// CacheType (NCsWidgetActor::NCache::ICache)
			#pragma region
			public:

			#pragma endregion CacheType (NCsWidgetActor::NCache::ICache)

			public:

				void Update(const FCsDeltaTime& DeltaTime);

				//void SetData(ICsData_Projectile* InData);
			};
		}
	}
}