// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Cache/CsCache_SkeletalMeshActorImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"
// Anim
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"

const FName NCsSkeletalMeshActor::NCache::FImpl::Name = FName("NCsSkeletalMeshActor::NCache::FImpl");

namespace NCsSkeletalMeshActor
{
	namespace NCache
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NCache::FImpl, Allocate);
				}
			}
		}

		FImpl::FImpl() :
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
			ElapsedTime()
			// SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsSkeletalMeshActor::NCache::ICache SkeletalMeshCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<SkeletalMeshCacheType>(static_cast<SkeletalMeshCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledCacheType (NCsPooledObject::NCache::ICache)
		#pragma region

		#define PayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PayloadType* Payload)
		{
		#undef PayloadType

			using namespace NImpl::NCached;

			const FString& Context = Str::Allocate;

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = true;
			State	   = ECsPooledObjectState::Active;
			UpdateType = Payload->GetUpdateType();
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			// SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache)
			typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
			typedef NCsSkeletalMeshActor::NPayload::IPayload SkeletalMeshPayloadType;

			SkeletalMeshPayloadType* SkeletalMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<SkeletalMeshPayloadType>(Context, Payload);

			typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

			if (ParamsType* Params = SkeletalMeshPayload->GetParams())
			{
				// OneShot - Anim Sequence
				{
					typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ShotType;

					if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
					{
						UAnimSequence* Anim = Shot->GetAnim();

						LifeTime = (1.0f / Anim->RateScale) * Anim->SequenceLength;
					}
				}
				// OneShot - Anim Montage
				{
					typedef NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot ShotType;

					if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
					{
						UAnimMontage* Anim = Shot->GetAnim();

						LifeTime = (1.0f / Shot->GetPlayRate()) * Anim->GetSectionLength(0);
					}
				}
			}
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::QueueDeallocate()
		{
			bQueueDeallocate = true;
		}

		bool FImpl::ShouldDeallocate() const
		{
			return bQueueDeallocate;
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
			State = ECsPooledObjectState::Inactive;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator.Reset();
			Owner.Reset();
			Parent.Reset();
			WarmUpTime = 0.0f;
			LifeTime = 0.0f;
			StartTime.Reset();
			ElapsedTime.Reset();
			// SkeletalMeshCacheType (NCsSkeletalMeshActor::NCache::ICache)
		}

		#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

		void FImpl::Update(const FCsDeltaTime& DeltaTime)
		{
			ElapsedTime += DeltaTime;
		}
	}
}