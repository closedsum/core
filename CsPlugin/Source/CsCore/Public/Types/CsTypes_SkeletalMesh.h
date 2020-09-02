// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_SkeletalMesh.generated.h"
#pragma once

// FCsSkeletalMesh
#pragma region

class USkeletalMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	UPROPERTY(Transient)
	USkeletalMesh* Mesh_Internal;

public:
	FCsSkeletalMesh() :
		Mesh(nullptr),
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr)
	{
	}

	FORCEINLINE bool operator==(const FCsSkeletalMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	FORCEINLINE bool operator!=(const FCsSkeletalMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE USkeletalMesh* Get() const
	{
		return Mesh_Internal;
	}
};
#pragma endregion FCsSkeletalMesh