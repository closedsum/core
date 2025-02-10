// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Fire/TimeBetweenShots/CsWeapon_Fire_TimeBetweenShotsImpl.h"

// Coroutine
#include "Coroutine/CsRoutine.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsWeapon_Fire_TimeBetweenShotsImpl)

// UCsWeapon_Fire_TimeBetweenShotsImpl
//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsWeapon_Fire_TimeBetweenShotsImpl)
	// ICsWeapon_Fire_TimeBetweenShots
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsWeapon_Fire_TimeBetweenShotsImpl, Evaluate)
	// Weapon_Fire_TimeBetweenShots
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsWeapon_Fire_TimeBetweenShotsImpl, Evaluate_Internal)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsWeapon_Fire_TimeBetweenShotsImpl::UCsWeapon_Fire_TimeBetweenShotsImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// ICsWeapon_Fire_TimeBetweenShots
#pragma region

void UCsWeapon_Fire_TimeBetweenShotsImpl::Evaluate()
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(Evaluate);

	CS_COROUTINE_SETUP_UOBJECT(UCsWeapon_Fire_TimeBetweenShotsImpl, Evaluate_Internal, NCsUpdateGroup::GameState, this, this);

	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START

	// "Captured" value of Time Between Shots
	//   Use the current value at the time Evaluate gets called.
	//   This represents the Total time Evaluate should "run" / be "ticked".
	//   NOTE: Value can change during the process of Evaluate being "ticked".
	//		   That is why a "captured" value is used instead.
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Value);

	CS_COROUTINE_START(this);
}

#pragma endregion ICsWeapon_Fire_TimeBetweenShots

// Weapon_Fire_TimeBetweenShots
#pragma region

char UCsWeapon_Fire_TimeBetweenShotsImpl::Evaluate_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_DELTA_TIME_START
	CS_COROUTINE_READ_FLOAT_START

	// ElapsedTime
	CS_COROUTINE_READ_DELTA_TIME_REF(R, ElapsedTime);

	const FCsDeltaTime PreviousElapsedTime = ElapsedTime;
	ElapsedTime							   += R->GetDeltaTime();

	// "Captured" value of Time Between Shots
	//   Use the current value at the time Evaluate gets called.
	//   NOTE: Value can change during the process of Evaluate being "ticked".
	//		   That is why a "captured" value is used instead.
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, Captured_TimeBetweenShots);

	// Broadcast ElapsedTime events

		// Time
	const float& PreviousTime = PreviousElapsedTime.Time;
	const float NewTime		   = FMath::Max(ElapsedTime.Time, Captured_TimeBetweenShots);

	OnElapsedTime_Event.Broadcast(Weapon, PreviousTime, NewTime);
	// Percent
	const float PreviousPercent = PreviousElapsedTime.Time / Captured_TimeBetweenShots;
	const float NewPercent		= FMath::Min(ElapsedTime.Time / Captured_TimeBetweenShots, 1.0f);

	OnElapsedTimeAsPercent_Event.Broadcast(Weapon, PreviousPercent, NewPercent);

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= Captured_TimeBetweenShots);

	OnComplete_Event.Broadcast(Weapon);

	CS_COROUTINE_END(R);
}

#pragma endregion Weapon_Fire_TimeBetweenShots
