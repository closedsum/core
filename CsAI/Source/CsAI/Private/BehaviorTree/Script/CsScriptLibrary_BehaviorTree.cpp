// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/Script/CsScriptLibrary_BehaviorTree.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_BehaviorTree)

// Library
#include "BehaviorTree/CsLibrary_BehaviorTree.h"
#include "Library/CsLibrary_Valid.h"
// Log
#include "VisualLogger/VisualLogger.h"
// Behavior Tree
#include "BehaviorTree/BTNode.h"

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_BehaviorTree)
	// Load
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, LoadBySoftObjectPath)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, LoadByStringPath)
	// Get
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, GetByPath)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, GetSoftObjectAsStringByPath)
	// Log
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, VLog)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, VLog_Error)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree, VLog_Verbose)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_BehaviorTree::UCsScriptLibrary_BehaviorTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define SET_LOG_WARNING void(*Log)(const FString&) = &NCsAI::FLog::Warning;

// Load
#pragma region

UBehaviorTree* UCsScriptLibrary_BehaviorTree::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(LoadBySoftObjectPath);

	return CsBehaviorTreeLibrary::SafeLoad(Ctxt, Path);
}

UBehaviorTree* UCsScriptLibrary_BehaviorTree::LoadByStringPath(const FString& Context, const FString& Path)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(LoadByStringPath);

	return CsBehaviorTreeLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UBehaviorTree* UCsScriptLibrary_BehaviorTree::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetByPath);

	return CsBehaviorTreeLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

bool UCsScriptLibrary_BehaviorTree::GetSoftObjectAsStringByPath(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetSoftObjectAsStringByPath);

	return CsBehaviorTreeLibrary::GetSafe(Context, Object, Path, OutPathAsString, OutSuccess);
}

#pragma endregion Get

// Log
#pragma region

void UCsScriptLibrary_BehaviorTree::VLog(const FString& Context, UObject* Owner, const FString& Message)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(VLog);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Owner)
	UE_VLOG(Owner, LogBehaviorTree, Log, TEXT("%s"), *Message);
}

void UCsScriptLibrary_BehaviorTree::VLog_Error(const FString& Context, UObject* Owner, const FString& Message)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(VLog_Error);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Owner)
	UE_VLOG(Owner, LogBehaviorTree, Error, TEXT("%s"), *Message);
}

void UCsScriptLibrary_BehaviorTree::VLog_Verbose(const FString& Context, UObject* Owner, const FString& Message)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(VLog_Verbose);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_EXIT2(Owner)
	UE_VLOG(Owner, LogBehaviorTree, Verbose, TEXT("%s"), *Message);
}

#pragma endregion Log

#undef SET_LOG_WARNING