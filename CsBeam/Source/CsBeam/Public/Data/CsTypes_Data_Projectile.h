// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_StaticMesh.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsTypes_Data_Projectile.generated.h"
#pragma once

// FCsPrjStaticMesh
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsStaticMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Scale;

public:

	FCsPrjStaticMesh() :
		Mesh(),
		Scale(1.0f)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsPrjStaticMesh