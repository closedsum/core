// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/Script/CsScriptLibrary_BehaviorTree.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "BehaviorTree/CsLibrary_BehaviorTree.h"
#include "Library/CsLibrary_Valid.h"
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
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, LoadByStringPath);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, GetByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, GetSoftObjectAsStringByPath);
			// Log
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree, VLog);
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

#define USING_NS_CACHED using namespace NCsScriptLibraryBehaviorTree::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryBehaviorTree::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define SET_LOG_WARNING void(*Log)(const FString&) = &NCsAI::FLog::Warning;
#define BehaviorTreeLibrary NCsBehaviorTree::FLibrary

// Load
#pragma region

UBehaviorTree* UCsScriptLibrary_BehaviorTree::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return BehaviorTreeLibrary::SafeLoad(Ctxt, Path);
}

UBehaviorTree* UCsScriptLibrary_BehaviorTree::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return BehaviorTreeLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UBehaviorTree* UCsScriptLibrary_BehaviorTree::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return BehaviorTreeLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

bool UCsScriptLibrary_BehaviorTree::GetSoftObjectAsStringByPath(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetSoftObjectAsStringByPath);

	return BehaviorTreeLibrary::GetSafe(Context, Object, Path, OutPathAsString, OutSuccess);
}

#pragma endregion Get

// Log
#pragma region

void UCsScriptLibrary_BehaviorTree::VLog(const FString& Context, UObject* Owner, const FString& Message)
{
	CONDITIONAL_SET_CTXT(VLog);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Owner)
	UE_VLOG(Owner, LogBehaviorTree, Log, TEXT("%s"), *Message);
}

void UCsScriptLibrary_BehaviorTree::VLog_Error(const FString& Context, UObject* Owner, const FString& Message)
{
	CONDITIONAL_SET_CTXT(VLog_Error);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Owner)
	UE_VLOG(Owner, LogBehaviorTree, Error, TEXT("%s"), *Message);
}

void UCsScriptLibrary_BehaviorTree::VLog_Verbose(const FString& Context, UObject* Owner, const FString& Message)
{
	CONDITIONAL_SET_CTXT(VLog_Verbose);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Owner)
	UE_VLOG(Owner, LogBehaviorTree, Verbose, TEXT("%s"), *Message);
}

#pragma endregion Log

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SET_LOG_WARNING
#undef BehaviorTreeLibrary