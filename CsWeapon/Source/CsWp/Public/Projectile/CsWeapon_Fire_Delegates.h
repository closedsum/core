// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

#include "CsWeapon_Fire_Delegates.generated.h"

USTRUCT()
struct CSWP_API FCsWeapon_Fire_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsWeapon_Fire_Delegates_STUB()
	{
	}
};

class ICsWeapon;
class UObject;
struct FCsRoutine;

namespace NCsWeapon
{
	namespace NFire
	{
		/** 
		* Delegate type for an Event that is broadcast BEFORE the Fire Action STARTS
		*  for a Weapon.
		*  Weapon is an object that implements the interface: ICsWeapon. 
		*  
		* @param Weapon		The Weapon current performing the Fire action.
		* @param ID			Represents a Unique ID associated with a Fire Action. 
		*/
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreStart, ICsWeapon* /*Weapon*/, const uint32& /*ID*/);

		/** 
		* Delegate type for an Event that is broadcast BEFORE the Fire Action Event: "Shot"
		*  for a Weapon.
		*  Weapon is an object that implements the interface: ICsWeapon. 
		*  "Shot" references to the moment a "object" (Projectile, Trace, Beam, ... etc) is "launched" from the Weapon.
		* 
		* @param Weapon						The Weapon current performing the Fire action.
		* @param ID							Represents a Unique ID associated with a Fire Action.
		* @param CurrentObectPerShotIndex
		*/
		DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPreShot, ICsWeapon* /*Weapon*/, const uint32& /*ID*/, const int32& /*CurrentObectPerShotIndex*/);

		/** 
		* Delegate type for an Event that is broadcast when the Fire Action Completes or Ends
		*  for a Weapon.
		*  Weapon is an object that implements the interface: ICsWeapon.
		*  This usually occurs AFTER the Weapon "launches" all "Shots".
		* 
		* @param Weapon		The Weapon current performing the Fire action.
		* @param Routine	Represents the Coroutine associated with the Fire action.
		*/
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnd, ICsWeapon* /*Weapon*/, FCsRoutine* /*R*/);
	}
}