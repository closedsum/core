// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_BehaviorTree.generated.h"

UCLASS()
class CSAI_API UCsScriptLibrary_BehaviorTree : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Log and Error via VLog
	* 
	* @param Context
	* @param Owner
	* @param Message
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree")
	static void VLog_Error(const FString& Context, UObject* Owner, const FString& Message);

	/**
	* Log and Verbose via VLog
	* 
	* @param Context
	* @param Owner
	* @param Message
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree")
	static void VLog_Verbose(const FString& Context, UObject* Owner, const FString& Message);
};