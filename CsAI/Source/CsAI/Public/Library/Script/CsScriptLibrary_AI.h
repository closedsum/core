// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_AI.generated.h"

class UAISystem;

UCLASS()
class CSAI_API UCsScriptLibrary_AI : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* GetDefault<UAISystem>
	*
	* return GetDefault<UAISystem>.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library")
	static const UAISystem* GetAISystem();
};