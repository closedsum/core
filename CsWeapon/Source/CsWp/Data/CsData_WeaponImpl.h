// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_Weapon.h"

struct FCsInterfaceMap;

struct CSWP_API FCsData_WeaponImpl : public ICsData_Weapon
{
private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_WeaponImpl();
	~FCsData_WeaponImpl();

	// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap
};