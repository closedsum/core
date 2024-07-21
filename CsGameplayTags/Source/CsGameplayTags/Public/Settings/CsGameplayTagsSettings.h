// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Coordinator
#include "Coordinators/GameplayTag/CsSettings_Coordinator_GameplayTag.h"

#include "CsGameplayTagsSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsGameplayTags Settings"))
class CSGAMEPLAYTAGS_API UCsGameplayTagsSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Coordinator_GameplayTag
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Coordinator_GameplayTag Coordinator_GameplayTag;

#pragma endregion Coordinator_GameplayTag
};