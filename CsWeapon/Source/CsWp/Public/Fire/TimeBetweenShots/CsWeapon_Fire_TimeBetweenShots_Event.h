// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsWeapon_Fire_TimeBetweenShots_Event.generated.h"

class ICsWeapon;

namespace NCsWeapon
{
	namespace NFire
	{
		namespace NTimeBetweenShots
		{
			/**
			* Delegate type for an Event that broadcasts when the time ELAPSED between "shots" of a Fire Action
			*  for a Weapon.
			*  Weapon is an object that implements the interface: ICsWeapon.
			* 
			* @param Weapon			The Weapon performing the Fire action.
			* @param PreviousTime	The Time in seconds that has elapsed BEFORE to Evaluate() being "ticked".
			* @param NewTime		The Time in seconds that has elapsed DURING Evalate() being "ticked".
			*/
			DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnElapsedTime, ICsWeapon* /*Weapon*/, const float& /*PreviousTime*/, const float& /*NewTime*/);

			/**
			* Delegate type for an Event that broadcasts when the time ELAPSED between "shots" of a Fire Action
			*  for a Weapon.
			*  Weapon is an object that implements the interface: ICsWeapon.
			* 
			* @param Weapon			The Weapon performing the Fire action.
			* @param PreviousValue	The Time as a Percent that has elapsed BEFORE to Evaluate() being "ticked".
			* @param NewValue		The Time as a Percent that has elapsed DURING Evalate() being "ticked".
			*/
			DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnElapsedTimeAsPercent, ICsWeapon* /*Weapon*/, const float& /*PreviousValue*/, const float& /*NewValue*/);

			/**
			* Delegate type for an Event that broadcasts when a "Shot" for a Fire Action has "completed"
			*  for a Weapon.
			*  Weapon is an object that implements the interface: ICsWeapon.
			*  Specifically when the time between "Shots" amount of time has ELAPSED during a Fire Action,
			*  the "Shot" has "completed".
			* 
			* @param Weapon		The Weapon performing the Fire action.
			*/
			DECLARE_MULTICAST_DELEGATE_OneParam(FOnComplete, ICsWeapon* /*Weapon*/);
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsWeapon_Fire_TimeBetweenShots_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSWP_API ICsWeapon_Fire_TimeBetweenShots_Event
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using OnElapsedTimeEventType = NCsWeapon::NFire::NTimeBetweenShots::FOnElapsedTime;
		using OnElapsedTimeAsPercentEventType = NCsWeapon::NFire::NTimeBetweenShots::FOnElapsedTimeAsPercent;
		using OnCompleteEventType = NCsWeapon::NFire::NTimeBetweenShots::FOnComplete;
	};

public:

	/**
	* Get the Delegate type for an Event that broadcasts when the time ELAPSED between "shots" of a Fire Action
	*  for a Weapon.
	*  Weapon is an object that implements the interface: ICsWeapon.
	*/
	virtual _::OnElapsedTimeEventType& GetOnElapsedTime_Event() = 0;

	/**
	* Get the Delegate type for an Event that broadcasts when the time ELAPSED between "shots" of a Fire Action
	*  for a Weapon.
	*  Weapon is an object that implements the interface: ICsWeapon.
	*/
	virtual _::OnElapsedTimeAsPercentEventType& GetOnElapsedTimeAsPercent_Event() = 0;

	/**
	* Get the Delegate type for an Event that broadcasts when a "Shot" for a Fire Action has "completed"
	*  for a Weapon.
	*  Weapon is an object that implements the interface: ICsWeapon.
	*  Specifically when the time between "Shots" amount of time has ELAPSED during a Fire Action,
	*  the "Shot" has "completed".
	*/
	virtual _::OnCompleteEventType& GetOnComplete_Event() = 0;
};