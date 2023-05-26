// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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