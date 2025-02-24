// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Managers/Sound/Cache/CsCache_Sound.h"
#include "Containers/CsWeakObjectPtr.h"

class UObject;
struct FCsInterfaceMap;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsSound::EDeallocateMethod
CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_1(NCsSound, EDeallocateMethod)

class UAudioComponent;
class USoundAttenuation;

namespace NCsSound
{
	namespace NCache
	{
		namespace NImpl
		{
			using PooledCacheType = NCsPooledObject::NCache::ICache;
			using CacheType = NCsSound::NCache::ICache;

			/**
			* Basic implementation for Cache implementing the interfaces:
			* PooledCacheType (NCsPooledObject::NCache::ICache) and 
			* SoundCacheType (NCsSound::NCache::ICache). This only supports 
			* a bare minimum functionality. For custom functionality create
			* another implementation
			*/
			struct CSSOUND_API FImpl final : public PooledCacheType,
											 public CacheType
			{
			public:

				static const FName Name;

			private:

				using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
				using StateType = NCsPooledObject::EState;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// PooledCacheType (CsPooledObject::NCache::ICache)

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

				// SoundCacheType (NCsSound::NCache::ICache)

				UAudioComponent* AudioComponent;

				EDeallocateMethod DeallocateMethod;

				float QueuedLifeTime;

			public:

				FImpl();

				~FImpl();

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
				{
					return InterfaceMap;
				}

			#pragma endregion ICsGetInterfaceMap

			// PooledCacheType (CsPooledObject::NCache::ICache)
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

			#pragma endregion PooledCacheType (CsPooledObject::NCache::ICache)

			public:

				FORCEINLINE void SetLifeTime(const float& InLifeTime) { LifeTime = InLifeTime; }

			// SoundCacheType (NCsSound::NCache::ICache)
			#pragma region
			public:

				FORCEINLINE UAudioComponent* GetAudioComponent() const { return AudioComponent; }

			#pragma endregion SoundCacheType (NCsSound::NCache::ICache)

			public:

				FORCEINLINE void SetAudioComponent(UAudioComponent* InAudioComponent) { AudioComponent = InAudioComponent; }

			public:

				void Update(const FCsDeltaTime& DeltaTime);
			};
		}
	}
}