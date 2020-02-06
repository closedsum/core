// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

	ICsSpawnedObject* Spawn();

#pragma endregion ICsSpawner

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptSpawner", meta = (DisplayName = "Spawn"))
	TScriptInterface<ICsSpawnedObject> Script_Spawn();
};