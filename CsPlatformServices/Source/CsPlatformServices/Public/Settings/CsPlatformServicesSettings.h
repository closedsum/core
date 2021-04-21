// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
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