// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsTypes_StaticMesh.generated.h"

// FCsStaticMesh
#pragma region

class UStaticMesh;

USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
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

	/**
	* Get the Hard reference to the UStaticMesh asset.
	*
	* return Skeletal Mesh
	*/
	FORCEINLINE UStaticMesh* Get() const { return Mesh_Internal; }

	/**
	* Get the pointer to the Hard reference to the UStaticMesh asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UStaticMesh** GetPtr() { return &Mesh_Internal; }

	/**
	* Get the Hard reference to the UStaticMesh asset.
	*
	* @param Context	The calling context.
	* return			Static Mesh
	*/
	FORCEINLINE UStaticMesh* GetChecked(const FString& Context) const
	{
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("%s: Mesh is NULL."), *Context);

		checkf(Mesh_Internal, TEXT("%s: Mesh has NOT been loaded from Path @ %s."), *Context, *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal;
	}

	/**
	* Get the Hard reference to the UStaticMesh asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UStaticMesh* GetChecked() const
	{
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("FCsStaticMesh::GetChecked: Mesh is NULL."));

		checkf(Mesh_Internal, TEXT("FCsStaticMesh::GetChecked: Mesh has NOT been loaded from Path @ %s."), *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal;
	}

	/**
	* Safely get the Hard reference to the UStaticMesh asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Static Mesh
	*/
	UStaticMesh* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Mesh.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mesh is NULL."), *Context));
			return nullptr;
		}

		if (!Mesh_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mesh has NOT been loaded from Path @ %s."), *Context, *(Mesh.ToSoftObjectPath().ToString())));
		}
		return Mesh_Internal;
	}

	/**
	* Safely get the Hard reference to the UStaticMesh asset.
	*
	* return Static Mesh
	*/
	UStaticMesh* GetSafe()
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

#pragma endregion FCsStaticMesh