// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/FX/Data/CsData_FX.h"

struct FCsInterfaceMap;

struct CSFX_API FCsData_FXImpl : public ICsData_FX
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_FXImpl();
	~FCsData_FXImpl();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsData_FX

// ICsData_Projectile
#pragma region
public:

#pragma endregion ICsData_FX
};