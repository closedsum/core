// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Spawner/CsSettings_Manager_Spawner.h"

#include "CsGetSettingsManagerSpawner.generated.h"

UINTERFACE(Blueprintable)
class CSSPAWNER_API UCsGetSettingsManagerSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSPAWNER_API ICsGetSettingsManagerSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const FCsSettings_Manager_Spawner& GetSettingsManagerSpawner() const = 0;
};