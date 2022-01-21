// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Debug/CsTypes_Debug.h"

#include "CsTypes_Debug_SpawnerParams.generated.h"
#pragma once

// FCsSpawnerPointDebugDraw
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerPointDebugDraw
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsDebugDrawLineAndPoint SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsDebugDrawLineAndPoint OnPreSpawnObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsDebugDrawLineAndPoint OnSpawnObject;

	FCsSpawnerPointDebugDraw()
	{

	}
};

#pragma endregion FCsSpawnerPointDebugDraw