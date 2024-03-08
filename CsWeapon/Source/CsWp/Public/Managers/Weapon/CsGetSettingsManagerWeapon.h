// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/Weapon/CsSettings_Manager_Weapon.h"

#include "CsGetSettingsManagerWeapon.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsGetSettingsManagerWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsGetSettingsManagerWeapon
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const FCsSettings_Manager_Weapon& GetSettingsManagerWeapon() const = 0;
};