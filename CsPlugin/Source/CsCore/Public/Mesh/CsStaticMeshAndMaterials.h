// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsStaticMeshAndMaterials.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMeshAndMaterials
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FCsStaticMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Mesh")
	FCsTArrayMaterialInterface Materials;

public:
	FCsStaticMeshAndMaterials() :
		Mesh(),
		Materials()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};