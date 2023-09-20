// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_StartPlay.generated.h"

class UObject;

UCLASS()
class CSCORE_API UCsScriptLibrary_StartPlay : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Call HasStartedPlay for Object.
	*  Object MUST implement the interface: ICsStartPlay.
	* 
	* @param Context	The calling context.
	* @param Object
	* return			The result of HasStartedPlay.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Start Play", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool HasStartedPlay(const FString& Context, const UObject* Object);
};