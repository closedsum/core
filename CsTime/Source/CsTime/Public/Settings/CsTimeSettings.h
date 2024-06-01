// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"

// Time
#include "Managers/Time/CsSettings_Manager_Time.h"

#include "CsTimeSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsTime Settings"))
class CSTIME_API UCsTimeSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (DisplayName = "Manager Time"))
	FCsSettings_Manager_Time Manager_Time;
};