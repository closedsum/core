// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"

// Coroutine
#include "Coroutine/CsSettings_CoroutineScheduler.h"

#include "CsCoroutineSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsCoroutine Settings"))
class CSCOROUTINE_API UCsCoroutineSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_CoroutineScheduler CoroutineScheduler;
};