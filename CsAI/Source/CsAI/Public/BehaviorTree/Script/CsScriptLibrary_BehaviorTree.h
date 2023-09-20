// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_BehaviorTree.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class CSAI_API UCsScriptLibrary_BehaviorTree : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Load
#pragma region
public:

	/**
	* Load a Behavior Tree at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the Behavior Tree to load.
	* return			Behavior Tree
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBehaviorTree* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a Behavior Tree at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the Behavior Tree to load.
	* return			Behavior Tree
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBehaviorTree* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Log
#pragma region
public:

	/**
	* Log via VLog
	* 
	* @param Context
	* @param Owner
	* @param Message
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Behavior Tree")
	static void VLog(const FString& Context, UObject* Owner, const FString& Message);

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

#pragma endregion Log
};