// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
struct FCsResource_DamageRange;
struct ICsDamageRange;

/**
* Container for an allocated object which implements the interface
* ICsDamageRange. This container is used to some what cleanly free
* the object after use.
*/
struct CSCORE_API FCsAllocated_DamageRange
{
public:

	UObject* Root;

	FCsResource_DamageRange* Container;

	ICsDamageRange* Range;

	FCsAllocated_DamageRange() :
		Root(nullptr),
		Container(nullptr),
		Range(nullptr)
	{
	}

	FORCEINLINE const ICsDamageRange* GetRange() const
	{
		return Range;
	}

	void CopyFrom(UObject* InRoot, const ICsDamageRange* From);

	void CopyFrom(const FCsAllocated_DamageRange* From);

	/**
	* Clear / null out all members and deallocate the Container.
	*/
	void Reset();
};