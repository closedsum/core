// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Managers/Creep/CsTdSettings_Manager_Creep.h"
#include "CsTdSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Tower Defense Settings"))
class CSTD_API UCsTdSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

// Enum
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	TArray<FCsSettings_Enum> ECsTdCreep;

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsTdSettings_Manager_Creep ManagerCreep;
};