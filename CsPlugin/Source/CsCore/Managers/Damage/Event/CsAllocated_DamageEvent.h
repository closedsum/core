// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
struct FCsResource_DamageEvent;
struct ICsDamageEvent;

/**
* Container for an allocated object which implements the interface
* ICsDamageEvent. This container is used to some what cleanly free
* the object after use.
*/
struct CSCORE_API FCsAllocated_DamageEvent
{
public:

	UObject* Root;

	FCsResource_DamageEvent* Container;

	ICsDamageEvent* Event;

	FCsAllocated_DamageEvent() :
		Root(nullptr),
		Container(nullptr),
		Event(nullptr)
	{
	}

	FORCEINLINE const ICsDamageEvent* GetEvent() const
	{
		return Event;
	}

	void CopyFrom(UObject* InRoot, const ICsDamageEvent* From);

	void CopyFrom(const FCsAllocated_DamageEvent* Event);

	/**
	* Clear / null out all members and deallocate the Container.
	*/
	void Reset();
};