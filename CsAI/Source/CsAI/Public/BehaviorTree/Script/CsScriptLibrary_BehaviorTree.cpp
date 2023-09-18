// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/Script/CsScriptLibrary_BehaviorTree.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "VisualLogger/VisualLogger.h"
// Behavior Tree
#include "BehaviorTree/BTNode.h"

// Cached
#pragma region

namespace NCsScriptLibraryBehaviorTree
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, VLog_Error);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, VLog_Verbose);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_BehaviorTree::UCsScriptLibrary_BehaviorTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_BehaviorTree::VLog_Error(const FString& Context, UObject* Owner, const FString& Message)
{
	using namespace NCsScriptLibraryBehaviorTree::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::VLog_Error : Context;

	if (!Owner)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Owner is NULL."), *Ctxt);
		return;
	}
	UE_VLOG(Owner, LogBehaviorTree, Error, TEXT("%s"), *Message);
}

void UCsScriptLibrary_BehaviorTree::VLog_Verbose(const FString& Context, UObject* Owner, const FString& Message)
{
	using namespace NCsScriptLibraryBehaviorTree::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::VLog_Verbose : Context;

	if (!Owner)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Owner is NULL."), *Ctxt);
		return;
	}
	UE_VLOG(Owner, LogBehaviorTree, Verbose, TEXT("%s"), *Message);
}