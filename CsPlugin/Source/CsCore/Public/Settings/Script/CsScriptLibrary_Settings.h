// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Settings.generated.h"

class UCsDeveloperSettings;

UCLASS()
class CSCORE_API UCsScriptLibrary_Settings : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* *
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Settings")
	static UCsDeveloperSettings* Get();
};