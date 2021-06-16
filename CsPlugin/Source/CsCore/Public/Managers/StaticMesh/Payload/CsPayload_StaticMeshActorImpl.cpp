// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsStaticMeshActor::NPayload::FImpl::Name = FName("NCsStaticMeshActor::NPayload::FImpl");;

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		#define DeallocateMethodType NCsStaticMeshActor::EDeallocateMethod

		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// StaticMeshPayloadType (NCsStaticMeshActor::NPayload::IPayload)
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
			bUseAsOccluder(false)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsStaticMeshActor::NPayload::IPayload StaticMeshPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<StaticMeshPayloadType>(static_cast<StaticMeshPayloadType*>(this));
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

			PreserveChangesFromDefaultMask = 0;

			// StaticMeshPayloadType (NCsStaticMeshActor::NPayload::IPayload)
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
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		#undef DeallocateMethodType
	}
}