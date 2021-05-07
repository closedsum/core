// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Managers/FX/Cache/CsCache_FX.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

namespace NCsFX
{
	enum class EDeallocateState : uint8
	{
		None,
		Complete,
		LifeTime
	};

	namespace NCache
	{
	#define PooledCacheType NCsPooledObject::NCache::ICache
	#define FXCacheType NCsFX::NCache::ICache

		/**
		* Basic implementation for Cache implementing the interfaces:
		* PooledCacheType (NCsPooledObject::NCache::ICache) and 
		* FXCacheType (NCsFX::NCache::ICache). This only supports 
		* a bare minimum functionality. For custom functionality create
		* another implementation
		*/
		struct CSCORE_API FImpl final : public PooledCacheType,
										public FXCacheType
		{
		public:

			static const FName Name;

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		#define DeallocateMethodType NCsFX::EDeallocateMethod

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

			// FXCacheType (NCsFX::NCache::ICache)

			UNiagaraComponent* FXComponent;

			DeallocateMethodType DeallocateMethod;

			EDeallocateState DeallocateState;

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

		// FXCacheType (NCsFX::NCache::ICache)
		#pragma region
		public:

			FORCEINLINE UNiagaraComponent* GetFXComponent() const { return FXComponent; }

		#pragma endregion FXCacheType (NCsFX::NCache::ICache)

		public:

			FORCEINLINE void SetFXComponent(UNiagaraComponent* InFXComponent) { FXComponent = InFXComponent; }

		public:

			void Update(const FCsDeltaTime& DeltaTime);

			//void SetData(ICsData_Projectile* InData);

		#undef PooledPayloadType
		#undef DeallocateMethodType
		};

	#undef PooledCacheType
	#undef FXCacheType
	}
}