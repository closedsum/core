// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsStaticMeshActor::NPayload::FImpl::Name = FName("NCsStaticMeshActor::NPayload::FImpl");;

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// NCsPooledObject::NPayload::IPayload
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// NCsStaticMeshActor::NPayload::IPayload
			Mesh(nullptr),
			DeallocateMethod(ECsStaticMeshActorDeallocateMethod::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsStaticMeshActor::NPayload::IPayload>(static_cast<NCsStaticMeshActor::NPayload::IPayload*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// NCsPooledObject::NPayload::IPayload
		#pragma region

		void FImpl::Reset()
		{
			// NCsPooledObject::NPayload::IPayload
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();

			// NCsStaticMeshActor::NPayload::IPayload
			Mesh = nullptr;
			DeallocateMethod = ECsStaticMeshActorDeallocateMethod::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}