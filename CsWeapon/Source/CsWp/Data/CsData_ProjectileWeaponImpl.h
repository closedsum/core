// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_ProjectileWeapon.h"

struct FCsInterfaceMap;

struct CSWP_API FCsData_ProjectileWeaponImpl : public ICsData_ProjectileWeapon
{
private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_ProjectileWeaponImpl();
	~FCsData_ProjectileWeaponImpl();

	// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

	// ICsData_ProjectileWeapon
#pragma region
public:

#pragma endregion ICsData_ProjectileWeapon
};