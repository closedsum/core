// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_Weapon.h"

struct FCsInterfaceMap;

struct CSWP_API FCsData_WeaponEmuSlice : public ICsData_Weapon
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_WeaponEmuSlice();
	~FCsData_WeaponEmuSlice();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

public:

	FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map)
	{
		InterfaceMap = Map;
	}

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap
};