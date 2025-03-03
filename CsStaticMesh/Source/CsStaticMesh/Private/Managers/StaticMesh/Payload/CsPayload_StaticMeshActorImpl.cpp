// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsStaticMeshActor::NPayload::NImpl::FImpl);

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		namespace NImpl
		{
			FImpl::FImpl() :
				InterfaceMap(nullptr),
				// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
				bAllocated(false),
				UpdateType(NCsPooledObject::EUpdate::Manager),
				Instigator(nullptr),
				Owner(nullptr),
				Parent(nullptr),
				Time(),
				PreserveChangesFromDefaultMask(0),
				// PayloadType (NCsStaticMeshActor::NPayload::IPayload)
				Mesh(nullptr),
				Materials(),
				bGenerateMIDs(),
				DeallocateMethod(DeallocateMethodType::Complete),
				LifeTime(0.0f),
				AttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
				Bone(NAME_None),
				TransformRules(0),
				Transform(FTransform::Identity),
				bCastShadow(false),
				bReceivesDecals(false),
				bUseAsOccluder(false),
				bRenderCustomDepth(false),
				CustomDepthStencilValue(0),
				Tags()
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(PooledPayloadType);
				CS_INTERFACE_MAP_ADD(PayloadType);
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

				PreserveChangesFromDefaultMask = 0;

				// PayloadType (NCsStaticMeshActor::NPayload::IPayload)
				Mesh = nullptr;
				Materials.Reset(Materials.Max());
				bGenerateMIDs = false;
				DeallocateMethod = DeallocateMethodType::Complete;
				LifeTime = 0.0f;
				AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
				Bone = NAME_None;
				TransformRules = 0;
				Transform = FTransform::Identity;
				bCastShadow = false;
				bReceivesDecals = false;
				bUseAsOccluder = false;
				bRenderCustomDepth = false;
				CustomDepthStencilValue = 0;
				Tags.Reset(Tags.Max());
			}

			#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		}
	}
}