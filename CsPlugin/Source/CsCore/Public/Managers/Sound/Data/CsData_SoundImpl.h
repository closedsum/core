// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Sound/Data/CsData_Sound.h"

struct FCsInterfaceMap;

struct CSCORE_API FCsData_SoundImpl : public ICsData_Sound
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