// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Tasks/Script/CsScriptLibrary_GameplayTask.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// AI
#include "GameplayTask.h"

// Cached
#pragma region

namespace NCsScriptLibraryGameplayTask
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTask, ReadyForActivation);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTask, ExternalCancel);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTask, IsActive);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTask, IsPaused);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameplayTask, IsFinished);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameplayTask::UCsScriptLibrary_GameplayTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_GameplayTask::ReadyForActivation(const FString& Context, UGameplayTask* Task)
{
	using namespace NCsScriptLibraryGameplayTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ReadyForActivation : Context;

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
	using namespace NCsScriptLibraryGameplayTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ExternalCancel : Context;

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
	using namespace NCsScriptLibraryGameplayTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsActive : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->IsActive();
}

bool UCsScriptLibrary_GameplayTask::IsPaused(const FString& Context, UGameplayTask* Task)
{
	using namespace NCsScriptLibraryGameplayTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsPaused : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->IsPaused();
}

bool UCsScriptLibrary_GameplayTask::IsFinished(const FString& Context, UGameplayTask* Task)
{
	using namespace NCsScriptLibraryGameplayTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsFinished : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->IsFinished();
}