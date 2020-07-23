// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Time/CsTypes_Time.h"
#pragma once

class ICsStatusEffect;

/**
*/
struct CSSE_API ICsStatusEffectEvent : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	/**
	*
	*
	* return
	*/
	virtual ICsStatusEffect* GetStatusEffect() const = 0;

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
	virtual UObject* GetCauser() const = 0;

	/**
	*
	*
	* return
	*/
	virtual UObject* GetReceiver() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const = 0;
};