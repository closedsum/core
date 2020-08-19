// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"
#pragma once

struct FCsInterfaceMap;

/**
* Basic implementation of the interface: ICsDamageValue
*/
struct CSCORE_API FCsDamageValuePointEmu : public ICsDamageValue,
										   public ICsDamageValuePoint
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsDamageValuePoint

	float* Value;

public:

	FCsDamageValuePointEmu();
	~FCsDamageValuePointEmu();

	FCsDamageValuePointEmu(const FCsDamageValuePointEmu&) = delete;
	FCsDamageValuePointEmu& operator = (const FCsDamageValuePointEmu&) = delete;

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageValue
#pragma region
public:

#pragma endregion ICsDamageValue

// ICsDamageValuePoint
#pragma region
public:

	FORCEINLINE const float& GetValue() const
	{
		return *Value;
	}

#pragma endregion ICsDamageValuePoint

public:

	void SetValue(float* InValue)
	{
		Value = InValue;
	}
};