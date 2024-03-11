// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)
			Mesh(nullptr),
			Materials(),
			bGenerateMIDs(false),
			DeallocateMethod(DeallocateMethodType::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform3f::Identity),
			bCastShadow(false),
			bReceivesDecals(false),
			bUseAsOccluder(false),
			bRenderCustomDepth(false),
			CustomDepthStencilValue(0),
			bSlavePoseComponent(false),
			Tags(),
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
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();

			// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)
			Mesh = nullptr;
			Materials.Reset(Materials.Max());
			bGenerateMIDs = false;
			DeallocateMethod = DeallocateMethodType::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform3f::Identity;
			bCastShadow = false;
			bReceivesDecals = false;
			bUseAsOccluder = false;
			bRenderCustomDepth = false;
			CustomDepthStencilValue = 0;
			bSlavePoseComponent = false;
			Tags.Reset(Tags.Max());
			Params = nullptr;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		#undef DeallocateMethodType
	}
}