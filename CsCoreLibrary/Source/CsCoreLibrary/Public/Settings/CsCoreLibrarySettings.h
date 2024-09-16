// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Container
#include "Containers/CsSettings_Container.h"

#include "CsCoreLibrarySettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsCore Library Settings"))
class CSCORELIBRARY_API UCsCoreLibrarySettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Container
#pragma region

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Container Container;

#pragma endregion Container
};