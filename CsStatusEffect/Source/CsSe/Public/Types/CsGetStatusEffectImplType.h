// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsTypes_StatusEffect.h"

/**
* Interface to describe which Status Effect implementation type.
* This is used to provide an easier way to access what the "type" is
* for a Status Effect implementation.
*/
class CSSE_API ICsGetStatusEffectImplType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetStatusEffectImplType(){}

	/**
	* Get the type of Status Effect implementation.
	*
	* return Type.
	*/
	virtual const FECsStatusEffectImpl& GetStatusEffectImplType() const = 0;
};