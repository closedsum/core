// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Data_Projectile.generated.h"
#pragma once

// FCsPrjStaticMesh
#pragma region

class UStaticMesh;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	UPROPERTY(Transient)
	UStaticMesh* Mesh_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Scale;

public:
	FCsPrjStaticMesh() :
		Mesh(nullptr),
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr),
		Scale(1.0f)
	{
	}

	FORCEINLINE UStaticMesh* Get() const
	{
		return Mesh_Internal;
	}

	FORCEINLINE bool operator==(const FCsPrjStaticMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	FORCEINLINE bool operator!=(const FCsPrjStaticMesh& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsPrjStaticMesh