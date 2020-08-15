// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"
#pragma once

struct FCsInterfaceMap;

/**
* Basic implementation of the interface: ICsDamageValue
*/
struct CSCORE_API FCsDamageValueRangeEmu : public ICsDamageValue,
										   public ICsDamageValueRange
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	float* MinValue;

	float* MaxValue;

public:

	FCsDamageValueRangeEmu();
	~FCsDamageValueRangeEmu();

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

// ICsDamageValueRange
#pragma region
public:

	FORCEINLINE const float& GetMinValue() const
	{
		return *MinValue;
	}

	FORCEINLINE const float& GetMaxValue() const
	{
		return *MaxValue;
	}

#pragma endregion ICsDamageValueRange

public:

	void SetMinValue(float* InValue)
	{
		MinValue = InValue;
	}

	void SetMaxValue(float* InValue)
	{
		MaxValue = InValue;
	}
};