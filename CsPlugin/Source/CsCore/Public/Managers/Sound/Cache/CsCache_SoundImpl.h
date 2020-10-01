// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Managers/Sound/Cache/CsCache_Sound.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsPooledObject {
	namespace NPayload {
		struct IPayload; } }

class UAudioComponent;
class USoundAttenuation;

namespace NCsSound
{
	namespace NCache
	{
		/**
		* Basic implementation for Cache implementing the interfaces:
		* NCsPooledObject::NCache::ICache and NCsSound::NCache::ICache. This only supports 
		* a bare minimum functionality. For custom functionality create
		* another implementation
		*/
		struct CSCORE_API FImpl final : public NCsPooledObject::NCache::ICache,
										public NCsSound::NCache::ICache
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// NCsPooledObject::NCache::ICache

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

			// NCsSound::NCache::ICache

			UAudioComponent* AudioComponent;

			ECsSoundDeallocateMethod DeallocateMethod;

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

			void QueueDeallocate();

			bool ShouldDeallocate() const;

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

		public:

			FORCEINLINE void SetLifeTime(const float& InLifeTime)
			{
				LifeTime = InLifeTime;
			}

		// NCsSound::NCache::ICache
		#pragma region
		public:

			FORCEINLINE UAudioComponent* GetAudioComponent() const
			{
				return AudioComponent;
			}

		#pragma endregion NCsSound::NCache::ICache

		public:

			FORCEINLINE void SetAudioComponent(UAudioComponent* InAudioComponent)
			{
				AudioComponent = InAudioComponent;
			}

		public:

			void Update(const FCsDeltaTime& DeltaTime);
		};
	}
}