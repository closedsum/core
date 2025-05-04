// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_AI.h"

// AI
#include "AISystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_AI)

// Cached
#pragma region

#pragma endregion Cached

UCsScriptLibrary_AI::UCsScriptLibrary_AI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const UAISystem* UCsScriptLibrary_AI::GetAISystem()
{
	return GetDefault<UAISystem>();
}