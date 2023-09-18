// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Tasks/Script/CsScriptLibrary_AI_Task.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// AI
#include "Tasks/AITask_MoveTo.h"

// Cached
#pragma region

namespace NCsScriptLibraryAITask
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, GetAIController);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, MoveTo_ReadyForActivation);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, MoveTo_SetUp);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, MoveTo_ConditionalPerformMove);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, MoveTo_WasMoveSuccessful);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AI_Task::UCsScriptLibrary_AI_Task(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

AAIController* UCsScriptLibrary_AI_Task::GetAIController(const FString& Context, const UAITask* Task)
{
	using namespace NCsScriptLibraryAITask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAIController : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	return Task->GetAIController();
}

FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result UCsScriptLibrary_AI_Task::MoveTo_ReadyForActivation(const FString& Context, UAITask_MoveTo* Task)
{
	using namespace NCsScriptLibraryAITask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveTo_ReadyForActivation : Context;

	FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result Result;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return Result;
	}
	Task->ReadyForActivation();

	Result.bValid			  = IsValid(Task);
	Result.bSuccess			  = true;
	Result.State			  = Task->GetState();
	Result.StateAsByte		  = (uint8)Task->GetState();
	Result.bWasMoveSuccessful = Task->WasMoveSuccessful();

	return Result;
}

bool UCsScriptLibrary_AI_Task::MoveTo_SetUp(const FString& Context, UAITask_MoveTo* Task, AAIController* Controller, const FCsAIMoveRequest& MoveRequest)
{
	using namespace NCsScriptLibraryAITask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveTo_SetUp : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}

	if (!Controller)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Controller is NULL."), *Ctxt);
		return false;
	}

	FAIMoveRequest Request;
	MoveRequest.CopyTo(Request);

	Task->SetUp(Controller, Request);
	return true;
}

bool UCsScriptLibrary_AI_Task::MoveTo_ConditionalPerformMove(const FString& Context, UAITask_MoveTo* Task)
{
	using namespace NCsScriptLibraryAITask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveTo_ConditionalPerformMove : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	Task->ConditionalPerformMove();
	return true;
}

bool UCsScriptLibrary_AI_Task::MoveTo_WasMoveSuccessful(const FString& Context, UAITask_MoveTo* Task)
{
	using namespace NCsScriptLibraryAITask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::MoveTo_WasMoveSuccessful : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}
	Task->WasMoveSuccessful();
	return true;
}