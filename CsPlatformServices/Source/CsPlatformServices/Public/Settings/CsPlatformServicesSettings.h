// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Managers/Save/CsSettings_Manager_Save.h"
#include "Managers/PlayerProfile/CsSettings_Manager_PlayerProfile.h"
#include "Managers/Achievement/CsSettings_Manager_Achievement.h"

#include "CsPlatformServicesSettings.generated.h"

class UDataTable;

UCLASS(config = Game, defaultconfig)
class CSPLATFORMSERVICES_API UCsPlatformServicesSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Save Manager_Save;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_PlayerProfile Manager_PlayerProfile;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Achievement Manager_Achievement;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSoftObjectPtr<UDataTable> Achievements;
};