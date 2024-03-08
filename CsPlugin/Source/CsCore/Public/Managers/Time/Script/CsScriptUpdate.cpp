// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/Script/CsScriptUpdate.h"
#include "CsCore.h"

UCsScriptUpdate::UCsScriptUpdate(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsScriptUpdate
#pragma region

	// ICsUpdate
#pragma region

void ICsScriptUpdate::Update(const FCsDeltaTime& DeltaTime)
{
	ICsScriptUpdate::Execute_Script_Update(_getUObject(), DeltaTime);
}

#pragma endregion ICsUpdate

#pragma endregion ICsScriptUpdate