// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Cache/CsCache_Beam.h"
// Container
#include "Containers/CsWeakObjectPtr.h"

class UObject;
struct FCsInterfaceMap;

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// DataType (NCsBeam::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)

namespace NCsBeam
{
	namespace NCache
	{
		namespace NImpl
		{
			using PooledCacheType = NCsPooledObject::NCache::ICache;
			using CacheType = NCsBeam::NCache::ICache;

			struct CSBEAM_API FImpl final : public PooledCacheType,
											public CacheType
			{
			public:

				static const FName Name;

			private:

				using DataType = NCsBeam::NData::IData;
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

			// CacheType (NCsBeam::NCache::ICache)
			#pragma region
			public:

			#pragma endregion CacheType (NCsBeam::NCache::ICache)

			public:

				void Update(const FCsDeltaTime& DeltaTime);

				void SetData(DataType* InData);
			};
		}
	}
}