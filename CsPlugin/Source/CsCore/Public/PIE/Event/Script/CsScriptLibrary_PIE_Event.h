// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_PIE_Event.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_PIE_Event : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Get whether Object implements the interface: ICsPIE_Event.
	*
	* @param Context	The calling context.
	* @param Object		
	* return			Whether Object implements the interface: ICsPIE_Event or not.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|PIE|Event", meta = (AutoCreateRefTerm = "Context"))
	static bool Implements(const FString& Context, const UObject* Object);
};