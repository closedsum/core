// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
	namespace NDeallocateState
	{
		namespace Ref
		{
			typedef EMDeallocateState EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(None);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
			CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
		}
	}

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
			State(NCsPooledObject::EState::Inactive),
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
			DeallocateState(EDeallocateState::None),
			bHideOnQueueDeallocate(false)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

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

		// PooledCacheType (NCsPooledObject::NCache::ICache)
		#pragma region
		
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PooledPayloadType* Payload)
		{
		#undef PooledPayloadType

			using namespace NCsFX::NCache::NImpl::NCached;

			const FString& Context = Str::Allocate;

			// NCsPooledObject::NCache::ICache
			bAllocated = true;
			State	   = NCsPooledObject::EState::Active;
			UpdateType = Payload->GetUpdateType();
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// NCsFX::NCache::ICache
			typedef NCsFX::NPayload::IPayload FXPayloadType;
			typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

			FXPayloadType* FXPayload = PooledPayloadLibrary::GetInterfaceChecked<FXPayloadType>(Context, Payload);

			DeallocateMethod = FXPayload->GetDeallocateMethod();
			LifeTime		 = FXPayload->GetLifeTime();

			bHideOnQueueDeallocate = FXPayload->ShouldHideOnQueueDeallocate();
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			if (bQueueDeallocate)
				return;

			bQueueDeallocate = true;
			// Deactivate FX Component
			checkf(FXComponent, TEXT("NCsFX::NCache::FImpl::QueueDeallocate: FXComponent is NULL."));

			FXComponent->Deactivate();

			if (bHideOnQueueDeallocate)
			{
				FXComponent->SetHiddenInGame(true);
			}

			// Transition to EDeallocateState::Complete
			// This is to hopefully prevent the GameThread from stalling when
			// Deactivating the System.
			DeallocateState = EDeallocateState::Complete;
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
			// PooledCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = false;
			bQueueDeallocate = false;
			State = NCsPooledObject::EState::Inactive;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator.Reset();
			Owner.Reset();
			Parent.Reset();
			WarmUpTime = 0.0f;
			LifeTime = 0.0f;
			StartTime.Reset();
			ElapsedTime.Reset();
			// FXCacheType (NCsFX::NCache::ICache)
			FXComponent = nullptr;
			DeallocateState = EDeallocateState::None;
			bHideOnQueueDeallocate = false;
		}

		#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			using namespace NCsFX::NCache::NImpl::NCached;

			const FString& Context = Str::Update;

			typedef NCsFX::FLibrary FXLibrary;
			typedef NCsFX::EDeallocateMethod DeallocateMethodType;

			
			// Complete
			if (DeallocateMethod == DeallocateMethodType::Complete)
			{
				// None | Complete
				if (DeallocateState == EDeallocateState::None ||
					DeallocateState == EDeallocateState::Complete)
				{
					// (None | Complete) -> LifeTime
					
					// If Complete, transition to EDeallocateState::LifeTime
					// This is to hopefully prevent the GameThread from stalling when
					// Deactivating the System.
					if (FXLibrary::IsCompleteChecked(Context, FXComponent))
					{
						// Reset ElapsedTime
						ElapsedTime.Reset();
						// Set LifeTime
						LifeTime = 1.0f;

						DeallocateState = EDeallocateState::LifeTime;
					}
				}
			}

			ElapsedTime += DeltaTime;

			// LifeTime
			if (DeallocateMethod == DeallocateMethodType::LifeTime)
			{
				// None
				if (DeallocateState == EDeallocateState::None)
				{
					// None -> Complete
					if (HasLifeTimeExpired())
					{
						// Deactivate FX Component
						checkf(FXComponent, TEXT("%s: FXComponent is NULL."), *Context);

						FXComponent->Deactivate();

						LifeTime = 0.0f;

						DeallocateState = EDeallocateState::Complete;
					}
				}
				// Complete
				else
				if (DeallocateState == EDeallocateState::Complete)
				{
					// Complete -> Lifetime
					
					// If Complete, transition to EDeallocateState::LifeTime
					// This is to hopefully prevent the GameThread from stalling when
					// Deactivating the System.
					if (FXLibrary::IsCompleteChecked(Context, FXComponent))
					{
						// Reset ElapsedTime
						ElapsedTime.Reset();
						// Set LifeTime
						LifeTime = 1.0f;

						DeallocateState = EDeallocateState::LifeTime;
					}
					// Wait until System is "Complete"
					else
					{
						LifeTime = 0.0f;
					}
				}	
			}
		}
	}
}