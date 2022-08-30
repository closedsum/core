// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Material/CsTypes_Material.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsSkeletalMeshAttachment.generated.h"

// NCsSkeletalMesh::NAttachment::FAttachment
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMesh, NAttachment, FAttachment)

class USceneComponent;
class USkeletalMeshComponent;
struct FCsSkeletalMeshActorPooled;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMeshAttachment
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh")
	FCsSkeletalMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh")
	FCsTArrayMaterialInterface Materials;

	/** Whether to generate Material Instance Dynamic(s) or MIDs for
		the Materials applied to Mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh")
	bool bGenerateMIDs;

	/** Valid if the SkeletalMeshComponent is attached to a Parent object or when an SkeletalMeshActor object is
		allocated, the Parent field of the payload is set. If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh")
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the SkeletalMeshComponent is attached to a Parent object.
		Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh")
	FName Bone;

	/** Which of the components of Transform to apply to the SkeletalMeshComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh", meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the SkeletalMeshComponent.
		If the SkeletalMeshComponent is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	FTransform Transform;

	/** Controls whether the SkeletalMeshComponent should cast a shadow or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	bool bCastShadow;

	/** Whether the SkeletalMeshComponent receives decals. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	bool bReceivesDecals;
	
	/** Whether to render the SkeletalMeshComponent in the depth only pass.
		This should generally be true for all objects, and let the renderer make decisions about whether to render objects in the depth only pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	bool bUseAsOccluder;

	/** If true, the SkeletalMeshComponent will be rendered in the CustomDepth pass (usually used for outlines) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	bool bRenderCustomDepth;

	/** Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh", meta = (UIMin = "0", ClampMin = "0", UIMax = "255", ClampMax = "255"))
	int32 CustomDepthStencilValue;

	/** Any Tags to applied to the SkeletalMeshComponent (i.e. appended to ComponentTags). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	TArray<FName> Tags;

	/** Whether the SkeletalMeshComponent has another component as a MasterPoseComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh")
	bool bSlavePoseComponent;

public:

	FCsSkeletalMeshAttachment() :
		Mesh(),
		Materials(),
		bGenerateMIDs(false),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity),
		bCastShadow(false),
		bReceivesDecals(false),
		bUseAsOccluder(false),
		bRenderCustomDepth(false),
		CustomDepthStencilValue(0),
		Tags(),
		bSlavePoseComponent(false)
	{
	}

#define AttachmentType NCsSkeletalMesh::NAttachment::FAttachment
	void CopyToAttachment(AttachmentType* Attachment);
	void CopyToAttachmentAsValue(AttachmentType* Attachment) const;
#undef AttachmentType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void AttachChecked(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child) const;
	bool AttachSafe(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FCsSkeletalMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const;
};

class USkeletalMesh;
class UMaterialInterface;
class UMaterialInstanceDynamic;
struct FCsSkeletalMeshActorPooled;

namespace NCsSkeletalMesh
{
	namespace NAttachment
	{
		struct CSCORE_API FAttachment
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Mesh, USkeletalMesh*)
			CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)

			/** Whether to generate Material Instance Dynamic(s) or MIDs for
				the Materials applied to Mesh. */
			CS_DECLARE_MEMBER_WITH_PROXY(bGenerateMIDs, bool)

			/** Valid if the SkeletalMeshComponent is attached to a Parent object or when an SkeletalMeshActor object is
				allocated, the Parent field of the payload is set. If the Parent object is NULL,
				the Sound will NOT be attached. */
			CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, ECsAttachmentTransformRules)

			/** Valid only when the SkeletalMeshComponent is attached to a Parent object.
				Bone or Socket to attach to. */
			CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)

			/** Which of the components of Transform to apply to the SkeletalMeshComponent. */
			CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)

			/** The Transform to apply to the SkeletalMeshComponent.
				If the SkeletalMeshComponent is attached to a parent object, the Transform is applied as a Relative Transform
				after the attachment.
				Else, the Transform is applied as a World Transform. */
			CS_DECLARE_MEMBER_WITH_PROXY(Transform, FTransform)

			/** Controls whether the SkeletalMeshComponent should cast a shadow or not. */
			CS_DECLARE_MEMBER_WITH_PROXY(bCastShadow, bool)

			/** Whether the SkeletalMeshComponent receives decals. */
			CS_DECLARE_MEMBER_WITH_PROXY(bReceivesDecals, bool)

			/** Whether to render the SkeletalMeshComponent in the depth only pass.
				This should generally be true for all objects, and let the renderer make decisions about whether to render objects in the depth only pass. */
			CS_DECLARE_MEMBER_WITH_PROXY(bUseAsOccluder, bool)

			/** If true, the SkeletalMeshComponent will be rendered in the CustomDepth pass (usually used for outlines) */
			CS_DECLARE_MEMBER_WITH_PROXY(bRenderCustomDepth, bool)

			/** Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3) */
			CS_DECLARE_MEMBER_WITH_PROXY(CustomDepthStencilValue, int32)

			/** Any Tags to applied to the SkeletalMeshComponent (i.e. appended to ComponentTags). */
			CS_DECLARE_MEMBER_WITH_PROXY(Tags, TArray<FName>)

			/** Whether the SkeletalMeshComponent has another component as a MasterPoseComponent. */
			CS_DECLARE_MEMBER_WITH_PROXY(bSlavePoseComponent, bool)

		public:

			FAttachment() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Materials),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bGenerateMIDs, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 7), // NCsTransformRules::All
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Transform, FTransform::Identity),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bCastShadow, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bReceivesDecals, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bUseAsOccluder, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bRenderCustomDepth, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(CustomDepthStencilValue, 0),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Tags),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bSlavePoseComponent, false)
			{
				CS_CTOR_SET_MEMBER_PROXY(Mesh);
				CS_CTOR_SET_MEMBER_PROXY(Materials);
				CS_CTOR_SET_MEMBER_PROXY(bGenerateMIDs);
				CS_CTOR_SET_MEMBER_PROXY(AttachmentTransformRules);
				CS_CTOR_SET_MEMBER_PROXY(Bone);
				CS_CTOR_SET_MEMBER_PROXY(TransformRules);
				CS_CTOR_SET_MEMBER_PROXY(Transform);
				CS_CTOR_SET_MEMBER_PROXY(bCastShadow);
				CS_CTOR_SET_MEMBER_PROXY(bReceivesDecals);
				CS_CTOR_SET_MEMBER_PROXY(bUseAsOccluder);
				CS_CTOR_SET_MEMBER_PROXY(bRenderCustomDepth);
				CS_CTOR_SET_MEMBER_PROXY(CustomDepthStencilValue);
				CS_CTOR_SET_MEMBER_PROXY(Tags);
				CS_CTOR_SET_MEMBER_PROXY(bSlavePoseComponent);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, USkeletalMesh)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bGenerateMIDs, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, ECsAttachmentTransformRules)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCastShadow, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bReceivesDecals, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bUseAsOccluder, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bRenderCustomDepth, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CustomDepthStencilValue, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Tags, TArray<FName>)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSlavePoseComponent, bool)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void AttachChecked(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child) const;
			bool AttachSafe(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void AttachAndActivateChecked(const FString& Context, USceneComponent* Parent, USkeletalMeshComponent* Child, TArray<UMaterialInstanceDynamic*>& OutMIDs) const;

			FCsSkeletalMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const;
		};
	}
}