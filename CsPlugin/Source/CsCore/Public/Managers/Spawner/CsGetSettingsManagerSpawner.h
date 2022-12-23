// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Spawner/CsSettings_Manager_Spawner.h"

#include "CsGetSettingsManagerSpawner.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetSettingsManagerSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetSettingsManagerSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const FCsSettings_Manager_Spawner& GetSettingsManagerSpawner() const = 0;
};