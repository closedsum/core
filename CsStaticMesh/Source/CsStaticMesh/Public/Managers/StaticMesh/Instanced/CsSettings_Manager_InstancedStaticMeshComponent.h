// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsStaticMeshLog.h"

#include "CsSettings_Manager_InstancedStaticMeshComponent.generated.h"

// FCsSettings_Manager_InstancedStaticMeshComponent
#pragma region

USTRUCT(BlueprintType)
struct CSSTATICMESH_API FCsSettings_Manager_InstancedStaticMeshComponent
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Static Mesh|Instanced", meta = (UIMin = "4", ClampMin = "4"))
	int32 PoolSize;

	FCsSettings_Manager_InstancedStaticMeshComponent() :
		PoolSize(256)
	{
	}

	static const FCsSettings_Manager_InstancedStaticMeshComponent& Get();

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStaticMesh::FLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_InstancedStaticMeshComponent