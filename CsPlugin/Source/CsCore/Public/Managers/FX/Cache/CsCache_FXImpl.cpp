// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Cache/CsCache_FXImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/FX/CsLibrary_FX.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "NiagaraComponent.h"
// Component
#include "Components/SceneComponent.h"

const FName NCsFX::NCache::FImpl::Name = FName("NCsFX::NCache::FImpl");

namespace NCsFX
{
	namespace NCache
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NCache::FImpl, Allocate);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NCache::FImpl, ShouldDeallocate);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NCache::FImpl, Update);
				}
			}
		}

		#define DeallocateMethodType NCsFX::EDeallocateMethod

		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledCacheType (NCsPooledObject::NCache::ICache)
			Index(INDEX_NONE),
			bAllocated(false),
			bQueueDeallocate(false),
			State(ECsPooledObjectState::Inactive),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(),
			Owner(),
			Parent(),
			WarmUpTime(0.0f),
			LifeTime(0.0f),
			StartTime(),
			ElapsedTime(),
			// FXCacheType (NCsFX::NCache::ICache)
			FXComponent(nullptr),
			DeallocateMethod(DeallocateMethodType::Complete),
			QueuedLifeTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsFX::NCache::ICache FXCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<FXCacheType>(static_cast<FXCacheType*>(this));
		}

		#undef DeallocateMethodType

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// NCsPooledObject::NCache::ICache
		#pragma region
		
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PooledPayloadType* Payload)
		{
		#undef PooledPayloadType

			using namespace NCsFX::NCache::NImpl::NCached;

			const FString& Context = Str::Allocate;

			// NCsPooledObject::NCache::ICache
			bAllocated = true;
			State	   = ECsPooledObjectState::Active;
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// NCsFX::NCache::ICache
			typedef NCsFX::NPayload::IPayload FXPayloadType;
			typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

			FXPayloadType* FXPayload = PooledPayloadLibrary::GetInterfaceChecked<FXPayloadType>(Context, Payload);

			DeallocateMethod = FXPayload->GetDeallocateMethod();
			QueuedLifeTime   = FXPayload->GetLifeTime();
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			bQueueDeallocate = true;
			// Deactivate FX Component
			checkf(FXComponent, TEXT("NCsFX::NCache::FImpl::QueueDeallocate: FXComponent is NULL."));

			FXComponent->Deactivate();

			// Transition to LifeTime
			// This is to hopefully prevent the GameThread from stalling when
			// Deactivating the System.
			typedef NCsFX::EDeallocateMethod DeallocateMethodType;

			// Reset ElapsedTime
			ElapsedTime.Reset();
			// Set LifeTime
			LifeTime = DeallocateMethod == DeallocateMethodType::LifeTime ? QueuedLifeTime : 1.0f;

			DeallocateMethod = DeallocateMethodType::LifeTime;
		}

		bool FImpl::ShouldDeallocate() const
		{
			return false;
		}

		bool FImpl::HasLifeTimeExpired()
		{
			return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
		}

		void FImpl::Reset()
		{
			// NCsPooledObject::NCache::ICache
			bAllocated = false;
			bQueueDeallocate = false;
			State = ECsPooledObjectState::Inactive;
			Instigator.Reset();
			Owner.Reset();
			Parent.Reset();
			WarmUpTime = 0.0f;
			LifeTime = 0.0f;
			StartTime.Reset();
			ElapsedTime.Reset();
			// NCsFX::NCache::ICache
			FXComponent = nullptr;
		}

		#pragma endregion NCsPooledObject::NCache::ICache

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			using namespace NCsFX::NCache::NImpl::NCached;

			const FString& Context = Str::Update;

			typedef NCsFX::FLibrary FXLibrary;
			typedef NCsFX::EDeallocateMethod DeallocateMethodType;

			// Complete
			if (DeallocateMethod == DeallocateMethodType::Complete)
			{
				// If Complete, transition to LifeTime
				// This is to hopefully prevent the GameThread from stalling when
				// Deactivating the System.
				if (FXLibrary::IsCompleteChecked(Context, FXComponent))
				{
					DeallocateMethod = DeallocateMethodType::LifeTime;

					// Reset ElapsedTime
					ElapsedTime.Reset();
					// Set LifeTime
					LifeTime = 1.0f;
				}
			}

			ElapsedTime += DeltaTime;
		}
	}
}