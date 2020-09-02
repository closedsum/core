// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Range/CsDamageRange.h"
#pragma once

struct FCsInterfaceMap;

/**
* Basic implementation of the interface: ICsDmaageRange
*/
struct CSCORE_API FCsDamageRangeEmu : public ICsDamageRange
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	float* MinRange;

	float* MaxRange;

public:

	FCsDamageRangeEmu();
	~FCsDamageRangeEmu();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageRange
#pragma region
public:

	FORCEINLINE const float& GetMinRange() const
	{
		return *MinRange;
	}

	FORCEINLINE const float& GetMaxRange() const
	{
		return *MaxRange;
	}

#pragma endregion ICsDamageRange

public:

	void SetMinRange(float* Value)
	{
		MinRange = Value;
	}

	void SetMaxValue(float* Value)
	{
		MaxRange = Value;
	}
};