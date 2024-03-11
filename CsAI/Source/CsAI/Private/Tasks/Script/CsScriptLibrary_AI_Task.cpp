// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Tasks/Script/CsScriptLibrary_AI_Task.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// AI
#include "AIController.h"
#include "Tasks/AITask_MoveTo.h"
// Log
#include "Utility/CsAILog.h"

// Cached
#pragma region

namespace NCsScriptLibraryAITask
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, GetAIController);
			// MoveTo
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AI_Task, New_MoveTo);
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

#define USING_NS_CACHED using namespace NCsScriptLibraryAITask::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryAITask::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define SET_LOG_WARNING void(*Log)(const FString&) = &NCsAI::FLog::Warning;

AAIController* UCsScriptLibrary_AI_Task::GetAIController(const FString& Context, const UAITask* Task)
{
	CONDITIONAL_SET_CTXT(GetAIController);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_RET_NULL2(Task)
	return Task->GetAIController();
}

UAITask_MoveTo* UCsScriptLibrary_AI_Task::New_MoveTo(const FString& Context, AAIController* OwnerController)
{
	CONDITIONAL_SET_CTXT(New_MoveTo);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL_RET_NULL2(OwnerController)

	UAITask_MoveTo* NewTask = UAITask::NewAITask<UAITask_MoveTo>(*OwnerController);

	if (!NewTask)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Failed to create new Task of type: UAITask_MoveTo."), *Ctxt);
	}
	return NewTask;
}

bool UCsScriptLibrary_AI_Task::MoveTo_ReadyForActivation(const FString& Context, UAITask_MoveTo* Task, FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result& OutResult)
{
	CONDITIONAL_SET_CTXT(MoveTo_ReadyForActivation);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Task)

	Task->ReadyForActivation();

	OutResult.bValid			 = IsValid(Task);
	OutResult.bSuccess			 = true;
	OutResult.State				 = (ECsGameplayTaskState)Task->GetState();
	OutResult.StateAsByte		 = (uint8)Task->GetState();
	OutResult.bWasMoveSuccessful = Task->WasMoveSuccessful();

	return true;
}

bool UCsScriptLibrary_AI_Task::MoveTo_SetUp(const FString& Context, UAITask_MoveTo* Task, AAIController* Controller, const FCsAIMoveRequest& MoveRequest)
{
	CONDITIONAL_SET_CTXT(MoveTo_SetUp);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Task)
	CS_IS_PENDING_KILL2(Controller)

	FAIMoveRequest Request;
	MoveRequest.CopyTo(Request);

	Task->SetUp(Controller, Request);
	return true;
}

bool UCsScriptLibrary_AI_Task::MoveTo_ConditionalPerformMove(const FString& Context, UAITask_MoveTo* Task)
{
	CONDITIONAL_SET_CTXT(MoveTo_ConditionalPerformMove);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Task)

	Task->ConditionalPerformMove();
	return true;
}

bool UCsScriptLibrary_AI_Task::MoveTo_WasMoveSuccessful(const FString& Context, UAITask_MoveTo* Task)
{
	CONDITIONAL_SET_CTXT(MoveTo_WasMoveSuccessful);
	SET_LOG_WARNING

	CS_IS_PENDING_KILL2(Task)

	Task->WasMoveSuccessful();
	return true;
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SET_LOG_WARNING