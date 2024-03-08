// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Spawner/CsSpawner.h"
#include "CsScriptSpawner.generated.h"

UINTERFACE(BlueprintType, MinimalApi)
class UCsScriptSpawner : public UCsSpawner
{
	GENERATED_UINTERFACE_BODY()
};

class ICsSpawnedObject;

class CSCORE_API ICsScriptSpawner : public ICsSpawner
{
	GENERATED_IINTERFACE_BODY()

// ICsSpawner
#pragma region
public:

	void Spawn();

#pragma endregion ICsSpawner

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptSpawner", meta = (DisplayName = "Spawn"))
	void Script_Spawn();
};