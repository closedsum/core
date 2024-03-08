// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Struct/CsTypes_StructOps.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_SkeletalMesh.generated.h"

// FCsSkeletalMesh
#pragma region

class USkeletalMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(BlueprintReadWrite, Category = "Skeletal Mesh", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("%s: Mesh's Path is NOT Valid."), *Context);
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
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("FCsSkeletalMesh::GetChecked: Mesh's Path is NOT Valid."));
		checkf(Mesh_Internal, TEXT("FCsSkeletalMesh::GetChecked: Mesh has NOT been loaded from Path @ %s."), *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal;
	}

	USkeletalMesh* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Mesh.ToSoftObjectPath().IsValid())
		{
			if (Log)
			{
				Log(FString::Printf(TEXT("%s: Mesh's Path is NOT Valid."), *Context));
			}
			return nullptr;
		}

		if (!Mesh_Internal)
		{
			if (Log)
			{
				Log(FString::Printf(TEXT("%s: Mesh has NOT been loaded from Path @ %s."), *Context, *(Mesh.ToSoftObjectPath().ToString())));
			}
		}
		return Mesh_Internal;
	}

	FORCEINLINE USkeletalMesh* GetSafe()
	{
		if (!Mesh.ToSoftObjectPath().IsValid())
			return nullptr;
		return Mesh_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsSkeletalMesh)
	CS_STRUCT_OPS_IS_VALID(FCsSkeletalMesh)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsSkeletalMesh)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsSkeletalMesh)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("%s: Mesh's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Mesh.ToSoftObjectPath().IsValid())
		{
			if (Log)
			{
				Log(FString::Printf(TEXT("%s: Mesh's Path is NOT Valid."), *Context));
			}
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsSkeletalMesh)

	FORCEINLINE void Unload()
	{
		Mesh.ResetWeakPtr();
		Mesh_Internal = nullptr;
	}
};

#pragma endregion FCsSkeletalMesh