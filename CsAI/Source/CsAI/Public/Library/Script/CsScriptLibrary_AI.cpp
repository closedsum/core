// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_AI.h"
#include "CsAI.h"

// AI
#include "AISystem.h"

// Cached
#pragma region

namespace NCsScriptLibraryAI
{
	namespace NCached
	{
		namespace Str
		{
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AI::UCsScriptLibrary_AI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const UAISystem* UCsScriptLibrary_AI::GetAISystem()
{
	return GetDefault<UAISystem>();
}