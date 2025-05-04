// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Tasks/Script/CsScriptLibrary_GameplayTask.h"
#include "CsAI.h"

// Types
#include "CsMacro_Misc.h"
// AI
#include "GameplayTask.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GameplayTask)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_GameplayTask)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_GameplayTask, ReadyForActivation)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_GameplayTask, ExternalCancel)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_GameplayTask, IsActive)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_GameplayTask, IsPaused)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_GameplayTask, IsFinished)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_GameplayTask::UCsScriptLibrary_GameplayTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_GameplayTask::ReadyForActivation(const FString& Context, UGameplayTask* Task)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(ReadyForActivation);

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	Task->ReadyForActivation();
	return true;
}

bool UCsScriptLibrary_GameplayTask::ExternalCancel(const FString& Context, UGameplayTask* Task)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(ExternalCancel);

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	Task->ExternalCancel();
	return true;
}

bool UCsScriptLibrary_GameplayTask::IsActive(const FString& Context, UGameplayTask* Task)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(IsActive);

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->IsActive();
}

bool UCsScriptLibrary_GameplayTask::IsPaused(const FString& Context, UGameplayTask* Task)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(IsPaused);

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->IsPaused();
}

bool UCsScriptLibrary_GameplayTask::IsFinished(const FString& Context, UGameplayTask* Task)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(IsFinished);

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->IsFinished();
}