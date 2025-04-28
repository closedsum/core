// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Components/ActorComponent.h"
// Interface
#include "Component/CsWeapon_Component.h"
#include "Fire/TimeBetweenShots/CsWeapon_Fire_TimeBetweenShots.h"
#include "Fire/TimeBetweenShots/CsWeapon_Fire_TimeBetweenShots_Event.h"
// Types
#include "CsMacro_Cached.h"

#include "CsWeapon_Fire_TimeBetweenShotsImpl.generated.h"

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsWeapon_Fire_TimeBetweenShotsImpl)

class ICsWeapon;
struct FCsRoutine;

/**
* Component Class that handles the Time Between "Shots" of a Fire Action of a Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*/
UCLASS(BlueprintType)
class CSWP_API UCsWeapon_Fire_TimeBetweenShotsImpl : public UActorComponent,
													 public ICsWeapon_Component,
													 public ICsWeapon_Fire_TimeBetweenShots,
													 public ICsWeapon_Fire_TimeBetweenShots_Event
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsWeapon_Fire_TimeBetweenShotsImpl);

	using OnElapsedTimeEventType = NCsWeapon::NFire::NTimeBetweenShots::FOnElapsedTime;
	using OnElapsedTimeAsPercentEventType = NCsWeapon::NFire::NTimeBetweenShots::FOnElapsedTimeAsPercent;
	using OnCompleteEventType = NCsWeapon::NFire::NTimeBetweenShots::FOnComplete;

// ICsWeapon_Component
#pragma region
public:

	FORCEINLINE void SetWeapon(ICsWeapon* InWeapon) { Weapon = InWeapon; }
	FORCEINLINE ICsWeapon* GetWeapon() const		{ return Weapon; }

#pragma endregion ICsWeapon_Component

// Weapon_Component
#pragma region
private:

	ICsWeapon* Weapon;

#pragma endregion Weapon_Component

// ICsWeapon_Fire_TimeBetweenShots
#pragma region
public:

	FORCEINLINE const float& GetValue() const		{ return Value; }
	FORCEINLINE void SetBase(const float& InBase)	{ Base = InBase; }
	FORCEINLINE const float& GetBase() const		{ return Base; }
	FORCEINLINE void ResetValueToBase()				{ Value = Base; }

	void Evaluate();

	FORCEINLINE void Clear()
	{
		OnElapsedTime_Event.Clear();
		OnElapsedTimeAsPercent_Event.Clear();
		OnComplete_Event.Clear();
	}

#pragma endregion ICsWeapon_Fire_TimeBetweenShots

// Weapon_Fire_TimeBetweenShots
#pragma region
private:

	/** This is the value BEFORE any modifications. */
	float Base;

	/** This is the value AFTER any modifications. */
	float Value;

	char Evaluate_Internal(FCsRoutine* R);

#pragma endregion Weapon_Fire_TimeBetweenShots

// ICsWeapon_Fire_TimeBetweenShots_Event
#pragma region
public:

	FORCEINLINE OnElapsedTimeEventType& GetOnElapsedTime_Event()					{ return OnElapsedTime_Event; }
	FORCEINLINE OnElapsedTimeAsPercentEventType& GetOnElapsedTimeAsPercent_Event()	{ return OnElapsedTimeAsPercent_Event; }
	FORCEINLINE OnCompleteEventType& GetOnComplete_Event()							{ return OnComplete_Event; }

#pragma endregion ICsWeapon_Fire_TimeBetweenShots_Event

// Weapon_Fire_TimeBetweenShots_Event
#pragma region
private:

	OnElapsedTimeEventType OnElapsedTime_Event;
	OnElapsedTimeAsPercentEventType OnElapsedTimeAsPercent_Event;
	OnCompleteEventType OnComplete_Event;

#pragma endregion Weapon_Fire_TimeBetweenShots_Event
};