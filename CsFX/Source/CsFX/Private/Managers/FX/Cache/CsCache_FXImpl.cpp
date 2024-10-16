// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Cache/CsCache_FXImpl.h"

// Types
#include "CsMacro_Misc.h"
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

			CSFX_API CS_ADD_TO_ENUM_MAP(None);
			CSFX_API CS_ADD_TO_ENUM_MAP(Complete);
			CSFX_API CS_ADD_TO_ENUM_MAP(LifeTime);
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

		#define USING_NS_CACHED using namespace NCsFX::NCache::NImpl::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsFX::NCache::NImpl::NCached; \
			const FString& Context = Str::__FunctionName

		using DeallocateMethodType = NCsFX::EDeallocateMethod;
		using PooledPayloadType = NCsPooledObject::NPayload::IPayload;

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
			bHideOnQueueDeallocate(false),
			DeathTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			InterfaceMap->Add<CsPooledObjectCacheType>(static_cast<CsPooledObjectCacheType*>(this));
			InterfaceMap->Add<CsFXCacheType>(static_cast<CsFXCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledCacheType (NCsPooledObject::NCache::ICache)
		#pragma region
		
		void FImpl::Allocate(PooledPayloadType* Payload)
		{
			SET_CONTEXT(Allocate);

			// CsPooledObjectCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = true;
			State	   = NCsPooledObject::EState::Active;
			UpdateType = Payload->GetUpdateType();
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// CsFXCacheType (NCsFX::NCache::ICache)
			CsFXPayloadType* FXPayload = CsPooledObjectPayloadLibrary::GetInterfaceChecked<CsFXPayloadType>(Context, Payload);

			DeallocateMethod = FXPayload->GetDeallocateMethod();
			LifeTime		 = FXPayload->GetLifeTime();
			DeathTime		 = FXPayload->GetDeathTime();

			bHideOnQueueDeallocate = FXPayload->ShouldHideOnQueueDeallocate();
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			// NOTE: FUTURE: Currently this extra check is added to prevent a crash when exiting the game.
			//				 Look into a more graceful way the FX can be deallocated.
			if (!bAllocated)
				return;
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

		bool FImpl::HasLifeTimeExpired() const
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

			DeallocateMethod = DeallocateMethodType::Complete;
			DeallocateState = EDeallocateState::None;
			bHideOnQueueDeallocate = false;
			DeathTime = 0.0f;
		}

		#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			SET_CONTEXT(Update);

			// Complete
			if (DeallocateMethod == DeallocateMethodType::Complete)
			{
				// None | Complete
				if (DeallocateState == EDeallocateState::None ||
					DeallocateState == EDeallocateState::Complete)
				{
					// (None | Complete) -> DeathTime
					if (DeathTime > 0.0f)
					{
						// Reset ElapsedTime
						ElapsedTime.Reset();

						DeallocateState = EDeallocateState::DeathTime;
					}
					// (None | Complete) -> LifeTime (graceful deallocate)
					
					// If Complete, transition to EDeallocateState::LifeTime
					// This is to hopefully prevent the GameThread from stalling when
					// Deactivating the System.
					else
					if (CsFXLibrary::IsReadyToRunChecked(Context, FXComponent) &&
						CsFXLibrary::IsCompleteChecked(Context, FXComponent))
					{
						// Reset ElapsedTime
						ElapsedTime.Reset();
						// Set LifeTime
						LifeTime = 1.0f;

						DeallocateState = EDeallocateState::LifeTime;
					}
				}
				// DeathTime
				else
				if (DeallocateState == EDeallocateState::DeathTime)
				{
					// DeathTime -> LifeTime (graceful deallocate)
					if (ElapsedTime.Time >= DeathTime)
					{
						// TODO: HACK: In Editor there instances when an FX doesn't compile its Shaders until its running?
						//			   The FX is "ready" but the instance is never created.
					#if WITH_EDITOR
						if (!CsFXLibrary::SafeHasSystemInstance(Context, FXComponent, nullptr) ||
							CsFXLibrary::IsInactiveChecked(Context, FXComponent) ||
							CsFXLibrary::IsCompleteChecked(Context, FXComponent))
					#else
						if (CsFXLibrary::IsInactiveChecked(Context, FXComponent) ||
							CsFXLibrary::IsCompleteChecked(Context, FXComponent))
					#endif // #if WITH_EDITOR
						{
							// Reset ElapsedTime
							ElapsedTime.Reset();
							// Set LifeTime
							LifeTime = 1.0f;

							DeallocateState = EDeallocateState::LifeTime;
						}
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
					// None -> (DeathTime or Complete)
					if (HasLifeTimeExpired())
					{
						// Deactivate FX Component
						checkf(FXComponent, TEXT("%s: FXComponent is NULL."), *Context);

						FXComponent->Deactivate();

						LifeTime = 0.0f;

						// None -> DeathTime
						if (DeathTime > 0.0f)
						{
							// Reset ElapsedTime
							ElapsedTime.Reset();

							DeallocateState = EDeallocateState::DeathTime;
						}
						// None -> Complete
						else
						{
							DeallocateState = EDeallocateState::Complete;
						}
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

					// TODO: HACK: In Editor there instances when an FX doesn't compile its Shaders until its running?
					//			   The FX is "ready" but the instance is never created.
				#if WITH_EDITOR
					if (!CsFXLibrary::SafeHasSystemInstance(Context, FXComponent, nullptr) ||
						CsFXLibrary::IsCompleteChecked(Context, FXComponent))
				#else
					if (CsFXLibrary::IsCompleteChecked(Context, FXComponent))
				#endif // #if WITH_EDITOR
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

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}