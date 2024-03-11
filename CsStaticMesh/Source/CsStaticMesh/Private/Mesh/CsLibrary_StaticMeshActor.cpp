// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Mesh/CsLibrary_StaticMeshActor.h"

// Library
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"
	// Payload
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"
// Components
#include "Components/SceneComponent.h"

namespace NCsStaticMesh
{
	namespace NActor
	{
		namespace NPooled
		{
			#define StaticMeshManagerLibrary NCsStaticMeshActor::NManager::FLibrary
			#define PayloadLibrary NCsStaticMeshActor::NPayload::FLibrary
			#define PayloadType NCsStaticMeshActor::NPayload::IPayload

			FCsStaticMeshActorPooled* FLibrary::AttachChecked(const FString& Context, const FCsStaticMeshAttachment& Attachment, const UObject* WorldContext, USceneComponent* Parent)
			{
				CS_IS_PTR_NULL_CHECKED(Parent)
				CS_IS_VALID_CHECKED(Attachment);

				typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

				const FECsStaticMeshActor& DefaultType = NCsStaticMeshActor::GetDefault();

				PayloadType* Payload		 = StaticMeshManagerLibrary::AllocatePayloadChecked(Context, WorldContext, DefaultType);
				PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

				PayloadImpl->Parent = Parent;
				PayloadImpl->Mesh   = Attachment.Mesh.GetChecked(Context);
				PayloadImpl->SetMaterials(Attachment.Materials.GetChecked(Context));
				PayloadImpl->bGenerateMIDs  = Attachment.bGenerateMIDs;
				PayloadImpl->AttachmentTransformRules = Attachment.AttachmentTransformRules.ToRule();
				PayloadImpl->Bone			= Attachment.Bone;
				PayloadImpl->TransformRules = Attachment.TransformRules;
				PayloadImpl->Transform		= Attachment.Transform;
				PayloadImpl->bCastShadow	= Attachment.bCastShadow;
				PayloadImpl->bReceivesDecals = Attachment.bReceivesDecals;
				PayloadImpl->bUseAsOccluder = Attachment.bUseAsOccluder;
				PayloadImpl->bRenderCustomDepth = Attachment.bRenderCustomDepth;
				PayloadImpl->CustomDepthStencilValue = Attachment.CustomDepthStencilValue;
				PayloadImpl->Tags.Reset(FMath::Max(PayloadImpl->Tags.Max(), Attachment.Tags.Num()));
				PayloadImpl->Tags.Append(Attachment.Tags);

				const FCsStaticMeshActorPooled* Object = StaticMeshManagerLibrary::SpawnChecked(Context, WorldContext, DefaultType, Payload);

				return const_cast<FCsStaticMeshActorPooled*>(Object);
			}

			#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

			FCsStaticMeshActorPooled* FLibrary::AttachChecked(const FString& Context, const AttachmentType& Attachment, const UObject* WorldContext, USceneComponent* Parent, const TArray<UMaterialInterface*>& OtherMaterials)
			{
				CS_IS_PTR_NULL_CHECKED(Parent)
				CS_IS_TARRAY_EMPTY_CHECKED(OtherMaterials, UMaterialInterface*)
				CS_IS_TARRAY_ANY_NULL_CHECKED(OtherMaterials, UMaterialInterface)
				CS_IS_VALID_CHECKED(Attachment);

				typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

				const FECsStaticMeshActor& DefaultType = NCsStaticMeshActor::GetDefault();

				PayloadType* Payload		 = StaticMeshManagerLibrary::AllocatePayloadChecked(Context, WorldContext, DefaultType);
				PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

				PayloadImpl->Parent = Parent;
				PayloadImpl->Mesh   = Attachment.GetMesh();
				PayloadImpl->SetMaterials(OtherMaterials);
				PayloadImpl->bGenerateMIDs  = Attachment.GetbGenerateMIDs();
				PayloadImpl->AttachmentTransformRules = Attachment.GetAttachmentTransformRules();
				PayloadImpl->Bone			= Attachment.GetBone();
				PayloadImpl->TransformRules = Attachment.GetTransformRules();
				PayloadImpl->Transform		= Attachment.GetTransform();
				PayloadImpl->bCastShadow	= Attachment.GetbCastShadow();
				PayloadImpl->bReceivesDecals = Attachment.GetbReceivesDecals();
				PayloadImpl->bUseAsOccluder = Attachment.GetbUseAsOccluder();
				PayloadImpl->bRenderCustomDepth = Attachment.GetbRenderCustomDepth();
				PayloadImpl->CustomDepthStencilValue = Attachment.GetCustomDepthStencilValue();
				PayloadImpl->Tags.Reset(FMath::Max(PayloadImpl->Tags.Max(), Attachment.GetTags().Num()));
				PayloadImpl->Tags.Append(Attachment.GetTags());

				const FCsStaticMeshActorPooled* Object = StaticMeshManagerLibrary::SpawnChecked(Context, WorldContext, DefaultType, Payload);

				return const_cast<FCsStaticMeshActorPooled*>(Object);
			}

			FCsStaticMeshActorPooled* FLibrary::AttachChecked(const FString& Context, const AttachmentType& Attachment, const UObject* WorldContext, USceneComponent* Parent)
			{
				return AttachChecked(Context, Attachment, WorldContext, Parent, Attachment.GetMaterials());
			}

			#undef AttachmentType

			#undef StaticMeshManagerLibrary
			#undef PayloadLibrary
			#undef PayloadType
		}
	}
}