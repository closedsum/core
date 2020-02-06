// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Spawner/Script/CsScriptSpawner.h"
#include "CsCore.h"

UCsScriptSpawner::UCsScriptSpawner(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsScriptSpawner
#pragma region

	// ICsSpawner
#pragma region

ICsSpawnedObject* ICsScriptSpawner::Spawn()
{
	return (ICsSpawnedObject*)ICsScriptSpawner::Execute_Script_Spawn(_getUObject()).GetInterface();
}

#pragma endregion ICsSpawner

#pragma endregion ICsScriptSpawner