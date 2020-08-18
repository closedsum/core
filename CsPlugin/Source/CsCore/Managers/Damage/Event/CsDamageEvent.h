// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "Managers/Damage/CsTypes_Damage.h"
#pragma once

class ICsDamageExpression;
struct ICsDamageValue;

/**
*
*/
struct CSCORE_API ICsDamageEvent : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsDamageEvent() {}

	/**
	*
	*
	* return
	*/
	virtual const float& GetDamage() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const ICsDamageValue* GetDamageValue() const = 0;

	/**
	*
	*
	* return 
	*/
	//virtual const ICsDamageRange* GetDamageRange() const = 0;

	/**
	*
	*
	* return
	*/ 
	virtual ICsDamageExpression* GetExpression() const = 0;

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
	virtual const FECsHitType& GetHitType() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FHitResult& GetOrigin() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FHitResult& GetHitResult() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const TArray<UObject*>& GetIgnoreObjects() const = 0;
};