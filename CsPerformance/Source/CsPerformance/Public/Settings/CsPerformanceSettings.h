// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Managers/Performance/CsSettings_Manager_Performance.h"
#include "UI/CsSettings_Performance_UI.h"

#include "CsPerformanceSettings.generated.h"


UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Performance Settings"))
class CSPERFORMANCE_API UCsPerformanceSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Performance Manager_Performance;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Performance_UI UI;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bShowFPS;
};