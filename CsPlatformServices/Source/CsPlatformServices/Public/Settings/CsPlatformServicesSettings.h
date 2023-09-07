// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/DeveloperSettings.h"
#include "CsPlatformServicesSettings.generated.h"

class UDataTable;

UCLASS(config = Game, defaultconfig)
class CSPLATFORMSERVICES_API UCsPlatformServicesSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSoftObjectPtr<UDataTable> Achievements;
};