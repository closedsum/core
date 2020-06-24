// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Containers/CsGetInterfaceMap.h"

#pragma once

class UObject;
struct ICsPooledObjectPayload;

/**
*/
struct CSCORE_API ICsPooledObjectCache : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsPooledObjectCache(){}

	/**
	*
	*
	* @param InIndex
	*/
	virtual void Init(const int32& InIndex) = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetIndex() const = 0;
	
	/*
	*
	*
	* @param Payload
	* @param InTime
	*/
	virtual void Allocate(ICsPooledObjectPayload* Payload) = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& IsAllocated() const = 0;

	/**
	*
	*/
	virtual void Deallocate() = 0;

	/**
	*
	*/
	virtual void QueueDeallocate() = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& ShouldDeallocate() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const ECsPooledObjectState& GetState() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const ECsPooledObjectUpdate& GetUpdateType() const = 0;

	/**
	*
	*
	* return
	*/
	virtual UObject* GetInstigator() const = 0;

	/**
	*
	*
	* return
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	*
	*
	* return
	*/
	virtual UObject* GetParent() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetWarmUpTime() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetLifeTime() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FCsTime& GetStartTime() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FCsDeltaTime& GetElapsedTime() const = 0;

	/**
	*
	*
	* return
	*/
	virtual bool HasLifeTimeExpired() = 0;

	/**
	*
	*/
	virtual void Reset() = 0;
};