// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"

#include "CsGetSettingsManagerProjectile.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsGetSettingsManagerProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsGetSettingsManagerProjectile
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const FCsSettings_Manager_Projectile& GetSettingsManagerProjectile() const = 0;
};