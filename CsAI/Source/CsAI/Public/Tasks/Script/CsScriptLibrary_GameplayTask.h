// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_GameplayTask.generated.h"

class UGameplayTask;

UCLASS()
class CSAI_API UCsScriptLibrary_GameplayTask : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Task->ReadyForActivation()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->ReadyForActivation() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Gameplay Task", meta = (AutoCreateRefTerm="Context"))
	static bool ReadyForActivation(const FString& Context, UGameplayTask* Task);

	/**
	* Task->ExternalCancel()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->ExternalCancel() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Gameplay Task", meta = (AutoCreateRefTerm="Context"))
	static bool ExternalCancel(const FString& Context, UGameplayTask* Task);

	/**
	* Task->IsActive()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->IsActive() was called or not.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Gameplay Task", meta = (AutoCreateRefTerm="Context"))
	static bool IsActive(const FString& Context, UGameplayTask* Task);

	/**
	* Task->IsPaused()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->IsPaused() was called or not.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Gameplay Task", meta = (AutoCreateRefTerm="Context"))
	static bool IsPaused(const FString& Context, UGameplayTask* Task);

	/**
	* Task->IsFinished()
	*
	* @param Context	The calling context
	* @param Task
	* return			Whether Task->IsFinished() was called or not.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Gameplay Task", meta = (AutoCreateRefTerm="Context"))
	static bool IsFinished(const FString& Context, UGameplayTask* Task);
};