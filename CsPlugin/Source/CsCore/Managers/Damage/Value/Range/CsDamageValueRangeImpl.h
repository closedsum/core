// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"
// Container
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Basic implementation of the interface: ICsDamageValue
*/
struct CSCORE_API FCsDamageValueRangeImpl : public ICsDamageValue,
											public ICsDamageValueRange
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	float MinValue;

	float MaxValue;

public:

	FCsDamageValueRangeImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
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
		return MinValue;
	}

	FORCEINLINE const float& GetMaxValue() const
	{
		return MaxValue;
	}

#pragma endregion ICsDamageValueRange

public:

	void Reset();
};