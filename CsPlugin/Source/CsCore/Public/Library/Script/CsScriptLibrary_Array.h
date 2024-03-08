// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Array.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Array : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:
	
	/**
	* Make an array of int32 from 0 to N inclusive and shuffled.
	* 
	* @param N
	* @param OutArray	(out)
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Array", meta = (AutoCreateRefTerm = "N"))
	static bool MakeShuffle_int32_0toN(const int32& N, TArray<int32>& OutArray);
};