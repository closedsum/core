// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

void ICsScriptSpawner::Spawn()
{
	ICsScriptSpawner::Execute_Script_Spawn(_getUObject());
}

#pragma endregion ICsSpawner

#pragma endregion ICsScriptSpawner