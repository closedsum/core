// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Range/CsDamageRange.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Basic implementation of the interface: ICsDamageRange
*/
struct CSCORE_API FCsDamageRangeImpl : public ICsDamageRange,
									   public ICsReset
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

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

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

// ICsReset
#pragma region
public:

	void Reset();

#pragma endregion ICsReset
};