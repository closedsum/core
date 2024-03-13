// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.\
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/Sound/Data/CsData_Sound.h"

struct FCsInterfaceMap;

struct CSSOUND_API FCsData_SoundImpl : public ICsData_Sound
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	FCsData_SoundImpl();
	~FCsData_SoundImpl();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsData_Sound
#pragma region
public:

#pragma endregion ICsData_Sound
};