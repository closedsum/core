// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Load
#include "Managers/Load/CsSettings_Manager_Load.h"

#include "CsLoadSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsLoad Settings"))
class CSLOAD_API UCsLoadSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Load
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Load", meta = (DisplayName = "Manager Load"))
	FCsSettings_Manager_Load Manager_Load;

#pragma endregion Load
};