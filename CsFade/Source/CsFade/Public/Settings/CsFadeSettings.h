// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Managers/Fade/CsSettings_Manager_Fade.h"

#include "CsFadeSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Fade Settings"))
class CSFADE_API UCsFadeSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Fade
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Fade Manager_Fade;

#pragma endregion Fade
};