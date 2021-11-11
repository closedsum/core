// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Weapon.h"

#include "CsGetWeaponTypes.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsGetWeaponTypes : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsGetWeaponTypes
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const TSet<FECsWeapon>& GetWeaponTypes() const = 0;
};