// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Managers/Runnable/CsSettings_Manager_Runnable.h"

#include "CsThreadSettings.generated.h"


UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Thread Settings"))
class CSTHREAD_API UCsThreadSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Runnable
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Runnable", meta = (DisplayName = "Manager Runnable"))
	FCsSettings_Manager_Runnable Manager_Runnable;

#pragma endregion Runnable
};