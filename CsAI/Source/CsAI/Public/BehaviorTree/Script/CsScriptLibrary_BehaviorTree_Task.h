// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "CsScriptLibrary_BehaviorTree_Task.generated.h"

class UBTNode;
class UBTTaskNode;
class UBehaviorTreeComponent;
class UAITask_MoveTo;
class UGameplayTask;

UCLASS()
class CSAI_API UCsScriptLibrary_BehaviorTree_Task : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree|Task", meta = (AutoCreateRefTerm="Context"))
	static UBehaviorTreeComponent* GetBTComponentForTask(const FString& Context, UBTNode* Task, UGameplayTask* GameplayTask);

	/**
	* NewBTAITask<UAITask_MoveTo>(OwnerComp)
	*
	* @param Context	The calling context
	* @param Task
	* @param OwnerComp
	* return			Whether NewBTAITask<UAITask_MoveTo>(OwnerComp) was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree|Task", meta = (AutoCreateRefTerm="Context"))
	static UAITask_MoveTo* New_MoveTo(const FString& Context, UBTNode* Task, UBehaviorTreeComponent* OwnerComp);

	/**
	* Task->FinishLatentTask()
	*
	* @param Context	The calling context
	* @param Task
	* @param OwnerComp
	* @param TaskResult
	* return			Whether Task->FinishLatentTask() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree|Task", meta = (AutoCreateRefTerm="Context,TaskResult"))
	static bool FinishLatentTask(const FString& Context, UBTTaskNode* Task, UBehaviorTreeComponent* OwnerComp, const TEnumAsByte<EBTNodeResult::Type>& TaskResult);
};