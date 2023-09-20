// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/CsLibrary_BehaviorTree.h"
#include "CsAI.h"

// Library
	// Common
#include "Object/CsLibrary_Object.h"
// BehaviorTree
#include "BehaviorTree/BehaviorTree.h"

namespace NCsBehaviorTree
{
	// Load
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	UBehaviorTree* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UBehaviorTree>(Context, Path, Log);
	}

	UBehaviorTree* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
	{
		return ObjectLibrary::SafeLoad<UBehaviorTree>(Context, Path, Log);
	}

	#undef ObjectLibrary

	#pragma endregion Load
}