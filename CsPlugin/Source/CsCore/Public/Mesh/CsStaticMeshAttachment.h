// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsStaticMeshAttachment.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMeshAttachment
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FCsStaticMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FCsTArrayMaterialInterface Materials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FName Bone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	ECsAttachmentTransformRules Rules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FVector Scale;

public:

	FCsStaticMeshAttachment() :
		Mesh(),
		Materials(),
		Bone(NAME_None),
		Rules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Location(0.0f),
		Rotation(0.0f),
		Scale(1.0f)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};