// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsStaticMeshComponentInfo.generated.h"

// NCsStaticMesh::NComponent::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMesh, NComponent, FInfo)

/**
* Container holding general information for a Static Mesh Component.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMeshComponentInfo
{
	GENERATED_USTRUCT_BODY()

	/** Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FCsStaticMesh Mesh;

	/** Materials */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FCsTArrayMaterialInterface Materials;

	/** Describes how the Component should be attached to the Parent Object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FCsAttachmentTransformRules AttachmentTransformRules;

	/** Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FName Bone;

	/** Which of the components of Transform to apply to the StaticMeshComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the StaticMeshComponent.
		This is applied as a Relative Transform. */
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

public:

	FCsStaticMeshComponentInfo() :
		Mesh(),
		Materials(),
		AttachmentTransformRules(FCsAttachmentTransformRules::KeepRelativeTransform),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform3f::Identity),
		bCastShadow(false),
		bReceivesDecals(false),
		bUseAsOccluder(false),
		bRenderCustomDepth(false),
		CustomDepthStencilValue(0)
	{
	}

#define InfoType NCsStaticMesh::NComponent::FInfo
	void CopyToInfo(InfoType* InInfo);
	void CopyToInfoAsValue(InfoType* InInfo) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

class UStaticMesh;
class UMaterialInterface;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

namespace NCsStaticMesh
{
	namespace NComponent
	{
		struct CSCORE_API FInfo
		{
		private:

			/** Mesh */
			CS_DECLARE_MEMBER_WITH_PROXY(Mesh, UStaticMesh*)
			/** Materials */
			CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
			/** Describes how the Component should be attached to the Parent Object. */
			CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
			/** Bone or Socket to attach to. */
			CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)
			/** Which of the components of Transform to apply to the StaticMeshComponent. */
			CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)
			/** The Transform to apply to the StaticMeshComponent.
				This is applied as a Relative Transform. */
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

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Materials),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::KeepRelativeTransform),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 7), // NCsTransformRules::All
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Transform, FTransform3f::Identity),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bCastShadow, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bReceivesDecals, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bUseAsOccluder, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bRenderCustomDepth, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(CustomDepthStencilValue, 0)
			{
				CS_CTOR_SET_MEMBER_PROXY(Mesh);
				CS_CTOR_SET_MEMBER_PROXY(Materials);
				CS_CTOR_SET_MEMBER_PROXY(AttachmentTransformRules);
				CS_CTOR_SET_MEMBER_PROXY(Bone);
				CS_CTOR_SET_MEMBER_PROXY(TransformRules);
				CS_CTOR_SET_MEMBER_PROXY(Transform);
				CS_CTOR_SET_MEMBER_PROXY(bCastShadow);
				CS_CTOR_SET_MEMBER_PROXY(bReceivesDecals);
				CS_CTOR_SET_MEMBER_PROXY(bUseAsOccluder);
				CS_CTOR_SET_MEMBER_PROXY(bRenderCustomDepth);
				CS_CTOR_SET_MEMBER_PROXY(CustomDepthStencilValue);
			}

			FORCEINLINE FInfo(FInfo& B) :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::KeepRelativeTransform)
			{
				SetMesh(B.GetMesh());
				SetMaterials(B.GetMaterials());
				SetAttachmentTransformRules(B.GetAttachmentTransformRules());
				SetBone(B.GetBone());
				SetTransformRules(B.GetTransformRules());
				SetTransform(B.GetTransform());
				SetbCastShadow(B.GetbCastShadow());
				SetbReceivesDecals(B.GetbReceivesDecals());
				SetbUseAsOccluder(B.GetbUseAsOccluder());
				SetbRenderCustomDepth(B.GetbRenderCustomDepth());
				SetCustomDepthStencilValue(B.GetCustomDepthStencilValue());
			}

			FORCEINLINE FInfo(const FInfo& B) :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::KeepRelativeTransform)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, UStaticMesh)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform3f)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCastShadow, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bReceivesDecals, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bUseAsOccluder, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bRenderCustomDepth, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CustomDepthStencilValue, int32)

			FORCEINLINE void Copy(const FInfo& B)
			{
				SetMesh(B.GetMesh());
				SetMaterials(B.GetMaterials());
				SetAttachmentTransformRules(B.GetAttachmentTransformRules());
				SetBone(B.GetBone());
				SetTransformRules(B.GetTransformRules());
				SetTransform(B.GetTransform());
				SetbCastShadow(B.GetbCastShadow());
				SetbReceivesDecals(B.GetbReceivesDecals());
				SetbUseAsOccluder(B.GetbUseAsOccluder());
				SetbRenderCustomDepth(B.GetbRenderCustomDepth());
				SetCustomDepthStencilValue(B.GetCustomDepthStencilValue());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void SetChecked(const FString& Context, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs) const;
		};
	}
}