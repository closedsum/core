// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_JsLog.generated.h"

UCLASS()
class CSJS_API UCsScriptLibrary_JsLog : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Log Warning
	* 
	* @param Message
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Log")
	static void Log_Warning(const FString& Message);
};