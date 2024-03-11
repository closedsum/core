
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/Types/Script/CsScriptLibrary_BehaviorTree_Types.h"
#include "CsAI.h"

// Cached
#pragma region

namespace NCsScriptLibraryBehaviorTreeTypes
{
	namespace NCached
	{
		namespace Str
		{
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_BehaviorTree_Types::UCsScriptLibrary_BehaviorTree_Types(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBehaviorTree* UCsScriptLibrary_BehaviorTree_Types::FCsBehaviorTree_Get(const FCsBehaviorTree& A)
{
	return A.Get();
}