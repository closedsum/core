// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Cache/CsCache_Projectile.h"
#include "Containers/CsWeakObjectPtr.h"

class UObject;
struct FCsInterfaceMap;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)

namespace NCsProjectile
{
	namespace NCache
	{
		namespace NImpl
		{
			using PooledCacheType = NCsPooledObject::NCache::ICache;
			using CacheType = NCsProjectile::NCache::ICache;

			struct CSPRJ_API FImpl final : public PooledCacheType,
										   public CacheType
			{
			public:

				static const FName Name;

			private:

				using DataType = NCsProjectile::NData::IData;
				using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
				using StateType = NCsPooledObject::EState;

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

				DataType* Data;

			public:

				FImpl();
				~FImpl();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				FORCEINLINE void SetLifeTimeChecked(const FString& Context, const float& InLifeTime)
				{
					checkf(InLifeTime >= 0.0f, TEXT("%s: InLifeTime: %f is NOT >= 0.0f."), *Context, InLifeTime);

					LifeTime = InLifeTime;
				}

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

			// CacheType (NCsProjectile::NCache::ICache)
			#pragma region
			public:

			#pragma endregion CacheType (NCsProjectile::NCache::ICache)

			public:

				void Update(const FCsDeltaTime& DeltaTime);

				void SetData(DataType* InData);
			};
		}
	}
}