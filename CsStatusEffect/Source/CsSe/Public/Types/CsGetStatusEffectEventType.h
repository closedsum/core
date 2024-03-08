// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsTypes_StatusEffect.h"

/**
* Interface to describe which Status Effect Event implementation to use.
* This is used to provide an easier way to determine which implementation to use
* when broadcasting a Status Effect.
*  Status Effect Event is an object that implements the interface: ICsStatusEffect::NEvent::IEvent
*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
*/
class CSSE_API ICsGetStatusEffectEventType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetStatusEffectEventType(){}

	/**
	* Get the type of Status Effect Event implementation.
	*
	* return Type.
	*/
	virtual const FECsStatusEffectEvent& GetStatusEffectEventType() const = 0;
};