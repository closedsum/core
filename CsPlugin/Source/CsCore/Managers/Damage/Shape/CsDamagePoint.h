// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Shape/CsDamageShape.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
*
*/
struct CSCORE_API FCsDamagePoint : public ICsDamageShape
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	float Damage;

public:

	FCsDamagePoint();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageShape
#pragma region
public:

	FORCEINLINE const float& GetMinDamage() const
	{
		return Damage;
	}

	FORCEINLINE const float& GetMaxDamage() const 
	{
		return Damage;
	}

	FORCEINLINE float CalculateDamage(const FVector& Origin, const FVector& Point) const
	{
		return Damage;
	}

#pragma endregion ICsDamageShape
};