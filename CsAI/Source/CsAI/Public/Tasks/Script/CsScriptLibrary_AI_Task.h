// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Cached.h"
#include "Types/CsTypes_AI.h"
#include "Tasks/Types/CsTypes_GameplayTask.h"

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
	ECsGameplayTaskState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	uint8 StateAsByte;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bWasMoveSuccessful;

	FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result() :
		bValid(false),
		bSuccess(false),
		State(ECsGameplayTaskState::Uninitialized),
		StateAsByte(0),
		bWasMoveSuccessful(false)
	{
	}
};


class UBehaviorTreeComponent;
class UAITask;
class UAITask_MoveTo;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsScriptLibrary_AI_Task)

UCLASS()
class CSAI_API UCsScriptLibrary_AI_Task : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsScriptLibrary_AI_Task);
	
public:

	/**
	* Task->GetAIController()
	*
	* @param Context	The calling context
	* @param Task
	* return			AI Controller.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Task", meta = (AutoCreateRefTerm="Context"))
	static AAIController* GetAIController(const FString& Context, const UAITask* Task);

// MoveTo
#pragma region
public:

	/**
	* NewBTAITask<UAITask_MoveTo>(OwnerController)
	*
	* @param Context			The calling context
	* @param OwnerController
	* return					Whether NewBTAITask<UAITask_MoveTo>(OwnerController) was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Task", meta = (AutoCreateRefTerm="Context"))
	static UAITask_MoveTo* New_MoveTo(const FString& Context, AAIController* OwnerController);

	/**
	* Task->ReadyForActivation()
	*
	* @param Context	The calling context
	* @param Task
	* return			Result
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Task", meta = (AutoCreateRefTerm="Context,OutResult"))
	static bool MoveTo_ReadyForActivation(const FString& Context, UAITask_MoveTo* Task, FCsScriptLibrary_AI_Task_MoveTo_ReadyForActivation_Result& OutResult);

	/**
	* Task->SetUp()
	*
	* @param Context	The calling context
	* @param Task
	* @param Controller
	* @param MoveRequest
	* return			Whether Task->SetUp() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Task", meta = (AutoCreateRefTerm="Context,MoveRequest"))
	static bool MoveTo_SetUp(const FString& Context, UAITask_MoveTo* Task, AAIController* Controller, const FCsAIMoveRequest& MoveRequest);

	/**
	* Task->ConditionalPerformMove()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->ConditionalPerformMove() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Task", meta = (AutoCreateRefTerm="Context"))
	static bool MoveTo_ConditionalPerformMove(const FString& Context, UAITask_MoveTo* Task);

	/**
	* Task->WasMoveSuccessful()
	*
	* @param Context	The calling context
	* @param Task
	* return			Task->WasMoveSuccessful().
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Task", meta = (AutoCreateRefTerm="Context"))
	static bool MoveTo_WasMoveSuccessful(const FString& Context, UAITask_MoveTo* Task);

#pragma endregion MoveTo
};