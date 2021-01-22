// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_StaticMesh.generated.h"
#pragma once

// FCsStaticMesh
#pragma region

class UStaticMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	UPROPERTY(Transient)
	UStaticMesh* Mesh_Internal;

public:
	FCsStaticMesh() :
		Mesh(nullptr),
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr)
	{
	}

	FORCEINLINE bool operator==(const FCsStaticMesh& B) const
	{
		return Mesh == B.Mesh && Mesh_LoadFlags == B.Mesh_LoadFlags && Mesh_Internal == B.Mesh_Internal;
	}

	FORCEINLINE bool operator!=(const FCsStaticMesh& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UStaticMesh* Get() const { return Mesh_Internal; }

	FORCEINLINE UStaticMesh** GetPtr() { return &Mesh_Internal; }

	FORCEINLINE UStaticMesh* GetChecked(const FString& Context) const 
	{
		checkf(Mesh_Internal, TEXT("%s: Mesh_Internal is NULL."), *Context);

		return Mesh_Internal;
	}
};

#pragma endregion FCsStaticMesh