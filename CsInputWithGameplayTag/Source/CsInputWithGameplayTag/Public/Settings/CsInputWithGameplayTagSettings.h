// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Input
#include "Managers/Input/CsSettings_Manager_Input_WithGameplayTag.h"

#include "CsInputWithGameplayTagSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsInput With GameplayTag Settings"))
class CSINPUTWITHGAMEPLAYTAG_API UCsInputWithGameplayTagSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Input
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "Manager Input"))
	FCsSettings_Manager_Input_WithGameplayTag Manager_Input;

#pragma endregion Input
};