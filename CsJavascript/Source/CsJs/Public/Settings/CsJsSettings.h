// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Managers/CsSettings_Manager_Javascript.h"

#include "CsJsSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Javascript Settings"))
class CSJS_API UCsJsSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Javascript Manager_Javascript;
};