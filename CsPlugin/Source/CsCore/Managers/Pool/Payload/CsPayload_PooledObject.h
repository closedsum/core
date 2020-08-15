// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Time/CsTypes_Time.h"

#pragma once

class UObject;

/**
* Interface for delivering a "payload" or blob of data when Allocating an
* object that implements the interface: ICsPooledObject. Usually this payload
* is passed through a Manager handling the pooled objects.
*/
struct CSCORE_API ICsPayload_PooledObject : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:
	
	virtual ~ICsPayload_PooledObject(){}

	/**
	* Whether the payload has been marked to be used (allocated).
	*
	* return Whether or not the payload has been marked to be used.
	*/
	virtual const bool& IsAllocated() const = 0;

	/**
	* The object "instigating" or starting the process.
	*
	* return Instigator.
	*/
	virtual UObject* GetInstigator() const = 0;

	/**
	* The owner of the object.
	*
	* return Owner.
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	* The parent of the object.
	*
	* return Parent.
	*/
	virtual UObject* GetParent() const = 0;

	/**
	* The current time.
	*
	* return time
	*/
	virtual const FCsTime& GetTime() const = 0;

	/**
	* Mark the payload as being used (allocated).
	*/
	virtual void Allocate() = 0;

	/**
	* Reset the contents of the payload to the default values.
	*/
	virtual void Reset() = 0;
};