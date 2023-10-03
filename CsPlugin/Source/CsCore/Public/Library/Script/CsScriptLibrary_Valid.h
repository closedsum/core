// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Valid.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Valid : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* checkf()
	*  Equivalent to the c++ version of checkf().
	* 
	* @param Expression		Value to Assert as True.
	* @param Message
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Valid", meta = (DisplayName = "checkf", AutoCreateRefTerm = "Expression,Context"))
	static bool Script_checkf(const bool& Expression, const FString& Message);

	/**
	* check()
	*  Equivalent to the c++ version of check().
	* 
	* @param Expression		Value to Assert as True.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Valid", meta = (DisplayName = "check", AutoCreateRefTerm = "Expression"))
	static bool Script_check(const bool& Expression);
};