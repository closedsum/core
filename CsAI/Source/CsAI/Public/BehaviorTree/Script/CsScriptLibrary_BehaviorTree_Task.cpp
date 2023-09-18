// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "BehaviorTree/Script/CsScriptLibrary_BehaviorTree_Task.h"
#include "CsAI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Behavior Tree
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BTTaskNode.h"
// AI
#include "Tasks/AITask_MoveTo.h"

// Cached
#pragma region

namespace NCsScriptLibraryBehaviorTreeTask
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree_Task, New_MoveTo);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree_Task, GetBTComponentForTask);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_BehaviorTree_Task, FinishLatentTask);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_BehaviorTree_Task::UCsScriptLibrary_BehaviorTree_Task(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAITask_MoveTo* UCsScriptLibrary_BehaviorTree_Task::New_MoveTo(const FString& Context, UBTNode* Task, UBehaviorTreeComponent* OwnerComp)
{
	using namespace NCsScriptLibraryBehaviorTreeTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::New_MoveTo : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return nullptr;
	}

	if (!OwnerComp)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: OwnerComp is NULL."), *Ctxt);
		return nullptr;
	}
	return Task->NewBTAITask<UAITask_MoveTo>(*OwnerComp);
}

UBehaviorTreeComponent* UCsScriptLibrary_BehaviorTree_Task::GetBTComponentForTask(const FString& Context, UBTNode* Task, UGameplayTask* GameplayTask)
{
	using namespace NCsScriptLibraryBehaviorTreeTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetBTComponentForTask : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return nullptr;
	}

	if (!GameplayTask)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: GameplayTask is NULL."), *Ctxt);
		return nullptr;
	}

	return Task->GetBTComponentForTask(*GameplayTask);
}

bool UCsScriptLibrary_BehaviorTree_Task::FinishLatentTask(const FString& Context, UBTTaskNode* Task, UBehaviorTreeComponent* OwnerComp, const TEnumAsByte<EBTNodeResult::Type>& TaskResult)
{
	using namespace NCsScriptLibraryBehaviorTreeTask::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetBTComponentForTask : Context;

	if (!Task)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: Task is NULL."), *Ctxt);
		return false;
	}

	if (!OwnerComp)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s: OwnerComp is NULL."), *Ctxt);
		return false;
	}

	Task->FinishLatentTask(*OwnerComp, TaskResult);
	return true;
}