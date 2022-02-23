// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

	/** Valid if the StaticMeshComponent is attached to a Parent object or when an StaticMeshActor object is
		allocated, the Parent field of the payload is set. If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the StaticMeshComponent is attached to a Parent object.
		Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FName Bone;

	/** Which of the components of Transform to apply to the StaticMeshComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the StaticMeshComponent.
		If the StaticMeshComponent is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FTransform Transform;

public:

	FCsStaticMeshAttachment() :
		Mesh(),
		Materials(),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity)
	{
	}

#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

	void CopyToAttachment(AttachmentType* Attachment);
	void CopyToAttachmentAsValue(AttachmentType* Attachment) const;

#undef AttachmentType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
	bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const;
};

class UStaticMesh;
class UMaterialInterface;
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
			CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, ECsAttachmentTransformRules)
			CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)
			CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)
			CS_DECLARE_MEMBER_WITH_PROXY(Transform, FTransform)

		public:

			FAttachment() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Materials),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 7), // NCsTransformRules::All
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Transform, FTransform::Identity)
			{
				CS_CTOR_SET_MEMBER_PROXY(Mesh);
				CS_CTOR_SET_MEMBER_PROXY(Materials);
				CS_CTOR_SET_MEMBER_PROXY(AttachmentTransformRules);
				CS_CTOR_SET_MEMBER_PROXY(Bone);
				CS_CTOR_SET_MEMBER_PROXY(TransformRules);
				CS_CTOR_SET_MEMBER_PROXY(Transform);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, UStaticMesh)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, ECsAttachmentTransformRules)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
			bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const UObject* WorldContext, USceneComponent* Parent) const;
		};
	}
}