// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/Script/CsScriptLibrary_BehaviorTree_Task.h"
#include "CsAI.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Behavior Tree
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BTTaskNode.h"
// AI
#include "Tasks/AITask_MoveTo.h"
// Log
#include "Utility/CsAILog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_BehaviorTree_Task)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_BehaviorTree_Task)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree_Task, New_MoveTo)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree_Task, GetBTComponentForTask)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_BehaviorTree_Task, FinishLatentTask)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_BehaviorTree_Task::UCsScriptLibrary_BehaviorTree_Task(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define SET_LOG_WARNING void(*Log)(const FString&) = &NCsAI::FLog::Warning;

UAITask_MoveTo* UCsScriptLibrary_BehaviorTree_Task::New_MoveTo(const FString& Context, UBTNode* Task, UBehaviorTreeComponent* OwnerComp)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(New_MoveTo);
	SET_LOG_WARNING

	CS_IS_PTR_NULL_RET_NULL2(Task)
	CS_IS_PTR_NULL_RET_NULL2(OwnerComp)

	UAITask_MoveTo* NewTask = Task->NewBTAITask<UAITask_MoveTo>(*OwnerComp);

	if (!NewTask)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Failed to create new Task of type: UAITask_MoveTo."), *Ctxt);
	}
	return NewTask;
}

UBehaviorTreeComponent* UCsScriptLibrary_BehaviorTree_Task::GetBTComponentForTask(const FString& Context, UBTNode* Task, UGameplayTask* GameplayTask)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(GetBTComponentForTask);
	SET_LOG_WARNING

	CS_IS_PTR_NULL_RET_NULL2(Task)
	CS_IS_PTR_NULL_RET_NULL2(GameplayTask)
	return Task->GetBTComponentForTask(*GameplayTask);
}

bool UCsScriptLibrary_BehaviorTree_Task::FinishLatentTask(const FString& Context, UBTTaskNode* Task, UBehaviorTreeComponent* OwnerComp, const TEnumAsByte<EBTNodeResult::Type>& TaskResult)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(FinishLatentTask);
	SET_LOG_WARNING

	CS_IS_PTR_NULL(Task)
	CS_IS_PTR_NULL(OwnerComp)

	Task->FinishLatentTask(*OwnerComp, TaskResult);
	return true;
}

#undef SET_LOG_WARNING