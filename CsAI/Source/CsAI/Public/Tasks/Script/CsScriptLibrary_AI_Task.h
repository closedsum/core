// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_AI.h"
// Gameplay
#include "GameplayTask.h"

#include "CsScriptLibrary_AI_Task.generated.h"


USTRUCT(BlueprintType)
struct CSAI_API FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bValid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bSuccess;

	/** NOTE: EGameplayTaskState doesn't seem to be set correctly in Script. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	EGameplayTaskState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	uint8 StateAsByte;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bWasMoveSuccessful;

	FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result() :
		bValid(false),
		bSuccess(false),
		State(EGameplayTaskState::Uninitialized),
		StateAsByte(0),
		bWasMoveSuccessful(false)
	{
	}
};


class UBehaviorTreeComponent;
class UAITask;
class UAITask_MoveTo;

UCLASS()
class CSAI_API UCsScriptLibrary_AI_Task : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Task->GetAIController()
	*
	* @param Context	The calling context
	* @param Task
	* return			AI Controller.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Task|Library", meta = (AutoCreateRefTerm="Context"))
	static AAIController* GetAIController(const FString& Context, const UAITask* Task);

	/**
	* Task->ReadyForActivation()
	*
	* @param Context	The calling context
	* @param Task
	* return			Result
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Blackboard|Library", meta = (AutoCreateRefTerm="Context"))
	static FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result MoveTo_ReadyForActivation(const FString& Context, UAITask_MoveTo* Task);

	/**
	* Task->SetUp()
	*
	* @param Context	The calling context
	* @param Task
	* @param Controller
	* @param MoveRequest
	* return			Whether Task->SetUp() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Task|Library", meta = (AutoCreateRefTerm="Context,MoveRequest"))
	static bool MoveTo_SetUp(const FString& Context, UAITask_MoveTo* Task, AAIController* Controller, const FCsAIMoveRequest& MoveRequest);

	/**
	* Task->ConditionalPerformMove()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->ConditionalPerformMove() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Task|Library", meta = (AutoCreateRefTerm="Context"))
	static bool MoveTo_ConditionalPerformMove(const FString& Context, UAITask_MoveTo* Task);

	/**
	* Task->WasMoveSuccessful()
	*
	* @param Context	The calling context
	* @param Task
	* return			Task->WasMoveSuccessful().
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Task|Library", meta = (AutoCreateRefTerm="Context"))
	static bool MoveTo_WasMoveSuccessful(const FString& Context, UAITask_MoveTo* Task);
};