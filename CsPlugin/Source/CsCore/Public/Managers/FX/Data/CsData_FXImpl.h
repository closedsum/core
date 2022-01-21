// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/FX/Data/CsData_FX.h"

struct FCsInterfaceMap;

struct CSCORE_API FCsData_FXImpl : public ICsData_FX
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