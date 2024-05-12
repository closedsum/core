// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Start/CsScriptStartPlay.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptStartPlay)

UCsScriptStartPlay::UCsScriptStartPlay(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsStartPlay
#pragma region

void ICsScriptStartPlay::StartPlay()
{
	ICsScriptStartPlay::Execute_Script_StartPlay(_getUObject());
}

bool ICsScriptStartPlay::HasStartedPlay() const
{
	return ICsScriptStartPlay::Execute_Script_HasStartedPlay(_getUObject());
}

#pragma endregion ICsStartPlay
