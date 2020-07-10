// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsData_ProjectileWeaponSound.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeaponSound : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_ProjectileWeaponSound : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsSound& GetFireSound() const = 0;
};