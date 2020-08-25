// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
#pragma once

class UObject;
struct FCsResource_DamageValue;
struct ICsDamageValue;

/**
* Container for an allocated object which implements the interface
* ICsDamageValue. This container is used to some what cleanly free
* the object after use.
*/
struct CSCORE_API FCsAllocated_DamageValue
{
public:

	UObject* Root;

	FCsResource_DamageValue* Container;

	ICsDamageValue* Value;

	FECsDamageValue Type;

	FCsAllocated_DamageValue() :
		Root(nullptr),
		Container(nullptr),
		Value(nullptr),
		Type()
	{
	}

	FORCEINLINE const ICsDamageValue* GetValue() const
	{
		return Value;
	}

	void CopyFrom(UObject* InRoot, const ICsDamageValue* From);

	void CopyFrom(const FCsAllocated_DamageValue* From);

	/**
	* Clear / null out all members and deallocate the Container.
	*/
	void Reset();
};