// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsSkeletalMeshActor::NPayload::FImpl::Name = FName("NCsSkeletalMeshActor::NPayload::FImpl");;

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
		#define DeallocateMethodType NCsSkeletalMeshActor::EDeallocateMethod

		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)
			Mesh(nullptr),
			Materials(),
			DeallocateMethod(DeallocateMethodType::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity),
			bCastShadow(false),
			bReceivesDecals(false),
			bUseAsOccluder(false),
			Params(nullptr)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsSkeletalMeshActor::NPayload::IPayload SkeletalMeshPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<SkeletalMeshPayloadType>(static_cast<SkeletalMeshPayloadType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region

		void FImpl::Reset()
		{
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();

			// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)
			Mesh = nullptr;
			Materials.Reset(Materials.Max());
			DeallocateMethod = DeallocateMethodType::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;
			bCastShadow = false;
			bReceivesDecals = false;
			bUseAsOccluder = false;
			Params = nullptr;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		#undef DeallocateMethodType
	}
}