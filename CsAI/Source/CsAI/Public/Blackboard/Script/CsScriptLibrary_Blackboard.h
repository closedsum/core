// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Blackboard.generated.h"

UCLASS()
class CSAI_API UCsScriptLibrary_Blackboard : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Safely check whether KeyType is of type Object.
	*
	* @param Context	The calling context
	* @param KeyType
	* return			Whether KeyType is of type Object or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Blackboard|Library", meta = (AutoCreateRefTerm="Context"))
	static bool IsKeyType_Object(const FString& Context, UClass* KeyType);

	/**
	* Safely check whether KeyType is of type Vector (Vector3d).
	*
	* @param Context	The calling context
	* @param KeyType
	* return			Whether KeyType is of type Vector (Vector3d) or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Blackboard|Library", meta = (AutoCreateRefTerm="Context"))
	static bool IsKeyType_Vector(const FString& Context, UClass* KeyType);
};