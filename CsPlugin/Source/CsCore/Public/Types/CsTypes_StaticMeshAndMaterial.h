// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsTypes_StaticMeshAndMaterial.generated.h"

// FCsStaticMeshAndMaterial
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMeshAndMaterial
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FCsStaticMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh")
	FCsMaterialInterface Material;

public:

	FCsStaticMeshAndMaterial() :
		Mesh(),
		Material()
	{
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(Mesh.IsValidChecked(Context));
		check(Material.IsValidChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Mesh.IsValid(Context, Log))
			return false;
		if (!Material.IsValid(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsStaticMeshAndMaterial