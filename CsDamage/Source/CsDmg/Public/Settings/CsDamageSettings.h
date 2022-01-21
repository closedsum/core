// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/DeveloperSettings.h"
// Damage
#include "Managers/Damage/CsSettings_Manager_Damage.h"

#include "CsDamageSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Damage Settings"))
class CSDMG_API UCsDamageSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (DisplayName = "Manager Damage"))
	FCsSettings_Manager_Damage Manager_Damage;
};