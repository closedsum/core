// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_SkeletalMesh.generated.h"
#pragma once

// FCsSkeletalMesh
#pragma region

class USkeletalMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Skeletal Mesh")
	USkeletalMesh* Mesh_Internal;

public:

	FCsSkeletalMesh() :
		Mesh(nullptr),
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the USkeletalMesh asset.
	*
	* return Skeletal Mesh
	*/
	FORCEINLINE USkeletalMesh* Get() const { return Mesh_Internal; }

	/**
	* Get the pointer to the Hard reference to the USkeletalMesh asset.
	*
	* return Skeletal Mesh
	*/
	FORCEINLINE USkeletalMesh** GetPtr() { return &Mesh_Internal; }

	/**
	* Get the Hard reference to the USkeletalMesh asset.
	*
	* @param Context	The calling context.
	* return			Skeletal Mesh
	*/
	FORCEINLINE USkeletalMesh* GetChecked(const FString& Context) const
	{ 
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("%s: Mesh is NULL."), *Context);

		checkf(Mesh_Internal, TEXT("%s: Mesh has NOT been loaded from Path @ %s."), *Context, *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal; 
	}

	/**
	* Get the Hard reference to the USkeletalMesh asset.
	*
	* return Skeletal Mesh
	*/
	FORCEINLINE USkeletalMesh* GetChecked() const
	{
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("FCsSkeletalMesh::GetChecked: Mesh is NULL."));

		checkf(Mesh_Internal, TEXT("FCsSkeletalMesh::GetChecked: Mesh has NOT been loaded from Path @ %s."), *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal;
	}

	USkeletalMesh* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Mesh.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mesh is NULL."), *Context));
			return nullptr;
		}

		if (!Mesh_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mesh has NOT been loaded from Path @ %s."), *Context, *(Mesh.ToSoftObjectPath().ToString())));
		}
		return Mesh_Internal;
	}

	USkeletalMesh* GetSafe()
	{
		if (!Mesh.ToSoftObjectPath().IsValid())
			return nullptr;
		return Mesh_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};
#pragma endregion FCsSkeletalMesh