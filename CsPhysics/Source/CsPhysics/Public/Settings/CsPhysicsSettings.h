// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Trace
#include "Managers/Trace/CsSettings_Manager_Trace.h"

#include "CsPhysicsSettings.generated.h"


UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Static Mesh Settings"))
class CSPHYSICS_API UCsPhysicsSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Trace", meta = (DisplayName = "Manager Trace"))
	FCsSettings_Manager_Trace Manager_Trace;
};