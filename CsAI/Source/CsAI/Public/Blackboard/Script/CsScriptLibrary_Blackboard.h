// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
//Types
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "CsScriptLibrary_Blackboard.generated.h"

UCLASS()
class CSAI_API UCsScriptLibrary_Blackboard : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Get whether KeyType is of type Object.
	*
	* @param Context	The calling context
	* @param KeyType
	* return			Whether KeyType is of type Object or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Blackboard|Library", meta = (AutoCreateRefTerm="Context"))
	static bool IsKeyType_Object(const FString& Context, UClass* KeyType);

	/**
	* Get whether KeyType is of type Vector (Vector3d).
	*
	* @param Context	The calling context
	* @param KeyType
	* return			Whether KeyType is of type Vector (Vector3d) or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Blackboard|Library", meta = (AutoCreateRefTerm="Context"))
	static bool IsKeyType_Vector(const FString& Context, UClass* KeyType);

// Selector
#pragma region
public:

	/**
	* Get whether Key Selector is Valid and of type Object.
	*
	* @param Context	The calling context
	* @param KeyType
	* return			Whether KeyType is of type Object or not.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Blackboard|Library", meta = (DisplayName = "Is Key Object (Checked)", AutoCreateRefTerm = "Context,Key"))
	static bool IsKeySelectorChecked_Object(const FString& Context, const FBlackboardKeySelector& Key);

#pragma endregion Selector
};