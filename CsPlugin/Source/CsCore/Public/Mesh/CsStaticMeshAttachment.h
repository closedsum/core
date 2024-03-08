// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsStaticMeshAttachment.generated.h"

// NCsStaticMesh::NAttachment::FAttachment
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMesh, NAttachment, FAttachment)

class USceneComponent;
class UStaticMeshComponent;
struct FCsStaticMeshActorPooled;

USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMeshAttachment
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FCsStaticMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FCsTArrayMaterialInterface Materials;

	/** Whether to generate Material Instance Dynamic(s) or MIDs for
		the Materials applied to Mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	bool bGenerateMIDs;

	/** Valid if the StaticMeshComponent is attached to a Parent object or when an StaticMeshActor object is
		allocated, the Parent field of the payload is set. If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FCsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the StaticMeshComponent is attached to a Parent object.
		Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FName Bone;

	/** Which of the components of Transform to apply to the StaticMeshComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the StaticMeshComponent.
		If the StaticMeshComponent is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FTransform3f Transform;

	/** Controls whether the StaticMeshComponent should cast a shadow or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bCastShadow;

	/** Whether the StaticMeshComponent receives decals. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bReceivesDecals;
	
	/** Whether to render the StatisMeshComponent in the depth only pass.
		This should generally be true for all objects, and let the renderer make decisions about whether to render objects in the depth only pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bUseAsOccluder;

	/** If true, the StatisMeshComponent will be rendered in the CustomDepth pass (usually used for outlines) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bRenderCustomDepth;

	/** Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (UIMin = "0", ClampMin = "0", UIMax = "255", ClampMax = "255"))
	int32 CustomDepthStencilValue;

	/** Any Tags to applied to the StaticMeshComponent (i.e. appended to ComponentTags). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	TArray<FName> Tags;

public:

	FCsStaticMeshAttachment() :
		Mesh(),
		Materials(),
		bGenerateMIDs(false),
		AttachmentTransformRules(FCsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform3f::Identity),
		bCastShadow(false),
		bReceivesDecals(false),
		bUseAsOccluder(false),
		bRenderCustomDepth(false),
		CustomDepthStencilValue(0),
		Tags()
	{
	}

#define AttachmentType NCsStaticMesh::NAttachment::FAttachment
	void CopyToAttachment(AttachmentType* Attachment);
	void CopyToAttachmentAsValue(AttachmentType* Attachment) const;
#undef AttachmentType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsTransformValidChecked(const FString& Context) const;
	bool IsTransformValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
	bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const;
};

class UStaticMesh;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class USceneComponent;
class UStaticMeshComponent;
struct FCsStaticMeshActorPooled;

namespace NCsStaticMesh
{
	namespace NAttachment
	{
		struct CSCORE_API FAttachment
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Mesh, UStaticMesh*)
			CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)

			/** Whether to generate Material Instance Dynamic(s) or MIDs for
				the Materials applied to Mesh. */
			CS_DECLARE_MEMBER_WITH_PROXY(bGenerateMIDs, bool)

			/** Valid if the StaticMeshComponent is attached to a Parent object or when an StaticMeshActor object is
				allocated, the Parent field of the payload is set. If the Parent object is NULL,
				the Sound will NOT be attached. */
			CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)

			/** Valid only when the StaticMeshComponent is attached to a Parent object.
				Bone or Socket to attach to. */
			CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)

			/** Which of the components of Transform to apply to the StaticMeshComponent. */
			CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)

			/** The Transform to apply to the StaticMeshComponent.
				If the StaticMeshComponent is attached to a parent object, the Transform is applied as a Relative Transform
				after the attachment.
				Else, the Transform is applied as a World Transform. */
			CS_DECLARE_MEMBER_WITH_PROXY(Transform, FTransform3f)

			/** Controls whether the StaticMeshComponent should cast a shadow or not. */
			CS_DECLARE_MEMBER_WITH_PROXY(bCastShadow, bool)

			/** Whether the StaticMeshComponent receives decals. */
			CS_DECLARE_MEMBER_WITH_PROXY(bReceivesDecals, bool)

			/** Whether to render the StatisMeshComponent in the depth only pass.
				This should generally be true for all objects, and let the renderer make decisions about whether to render objects in the depth only pass. */
			CS_DECLARE_MEMBER_WITH_PROXY(bUseAsOccluder, bool)

			/** If true, the StatisMeshComponent will be rendered in the CustomDepth pass (usually used for outlines) */
			CS_DECLARE_MEMBER_WITH_PROXY(bRenderCustomDepth, bool)

			/** Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3) */
			CS_DECLARE_MEMBER_WITH_PROXY(CustomDepthStencilValue, int32)

			/** Any Tags to applied to the StaticMeshComponent (i.e. appended to ComponentTags). */
			CS_DECLARE_MEMBER_WITH_PROXY(Tags, TArray<FName>)

		public:

			FAttachment() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Materials),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bGenerateMIDs, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::SnapToTargetNotIncludingScale),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 7), // NCsTransformRules::All
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Transform, FTransform3f::Identity),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bCastShadow, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bReceivesDecals, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bUseAsOccluder, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bRenderCustomDepth, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(CustomDepthStencilValue, 0),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Tags)
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
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, UStaticMesh)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bGenerateMIDs, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform3f)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCastShadow, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bReceivesDecals, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bUseAsOccluder, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bRenderCustomDepth, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CustomDepthStencilValue, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Tags, TArray<FName>)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			bool IsTransformValidChecked(const FString& Context) const;
			bool IsTransformValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, const TArray<UMaterialInterface*>& OtherMaterials) const;
			void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
			bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void AttachOnlyTransformChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;

			void AttachAndActivateChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, const TArray<UMaterialInterface*>& OtherMaterials, TArray<UMaterialInstanceDynamic*>& OutMIDs) const;
			void AttachAndActivateChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, TArray<UMaterialInstanceDynamic*>& OutMIDs) const;

			FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent, const TArray<UMaterialInterface*>& OtherMaterials) const;
			FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const;
		};
	}
}