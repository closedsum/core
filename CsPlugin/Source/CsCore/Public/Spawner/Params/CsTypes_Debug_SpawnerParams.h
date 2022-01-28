// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Debug/CsTypes_Debug.h"

#include "CsTypes_Debug_SpawnerParams.generated.h"

// FCsSpawnerPointDebugDraw
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerPointDebugDraw
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params")
	FCsDebugDrawLineAndPoint SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params")
	FCsDebugDrawLineAndPoint OnPreSpawnObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params")
	FCsDebugDrawLineAndPoint OnSpawnObject;

	FCsSpawnerPointDebugDraw()
	{

	}
};

#pragma endregion FCsSpawnerPointDebugDraw