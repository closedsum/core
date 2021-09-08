// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
#include "CsJsSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Javascript Settings"))
class CSJS_API UCsJsSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FString GameInstanceEntryPointFileName;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FString GameStateEntryPointFileName;
};