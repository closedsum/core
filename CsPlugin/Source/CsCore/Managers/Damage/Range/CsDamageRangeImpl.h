// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Range/CsDamageRange.h"
// Container
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Basic implementation of the interface: ICsDamageRange
*/
struct CSCORE_API FCsDamageRangeImpl : public ICsDamageRange
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	float MinRange;

	float MaxRange;

public:

	FCsDamageRangeImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageRange
#pragma region
public:

	FORCEINLINE const float& GetMinRange() const
	{
		return MinRange;
	}

	FORCEINLINE const float& GetMaxRange() const
	{
		return MaxRange;
	}

#pragma endregion ICsDamageRange

public:

	void Reset();
};