// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsWeapon_Fire_TimeBetweenShots.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsWeapon_Fire_TimeBetweenShots : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface that describes the Time Between "Shots" of a Fire Action for a Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  This interface is typically implemented as a component of a Weapon.
*/
class CSWP_API ICsWeapon_Fire_TimeBetweenShots
{
	GENERATED_IINTERFACE_BODY()

public:

	/** 
	* Get the current value associated with Time Between Shots. 
	*/
	virtual const float& GetValue() const = 0;

	virtual void SetBase(const float& InBase) = 0;

	virtual const float& GetBase() const = 0;

	/**
	* Reset the current value associated with Time Between Shots to the "base" value.
	*  This is usually a value that the Time Between Shots STARTS at before ANY Modifiers
	*  are applied.
	*  Modifier is an object that implements the interface: CsModifierType (NCsModifier::IModifier).
	*/
	virtual void ResetValueToBase() = 0;

	/**
	* "Tick" / Process the Time Between Shots.
	*/
	virtual void Evaluate() = 0;

	/**
	* Clear all events bindings.
	*  TODO: FUTURE: MAYBE? Move to the Event Interface.
	*/
	virtual void Clear() = 0;
};