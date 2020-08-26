// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsTypes_StatusEffectEvent.h"

#include "Data/CsData_StatusEffect.h"

// FCsStatusEffectTriggerFrequencyInfo
#pragma region

void FCsStatusEffectTriggerFrequencyInfo::SetData(ICsData_StatusEffect* InData)
{
	Data = InData;

	const FCsStatusEffectTriggerFrequencyParams& Params = Data->GetTriggerFrequencyParams();
	const ECsStatusEffectTriggerFrequency& Type		    = Params.Type;

	bDelayComplete = Params.Delay > 0.0f;

	// Once
	if (Type == ECsStatusEffectTriggerFrequency::Once)
	{
		TotalTime = Params.Delay;
	}
	// Count
	else
	if (Type == ECsStatusEffectTriggerFrequency::Count)
	{
		TotalTime += Params.Delay;
		TotalTime += Params.Delay * Params.Interval;
	}
	// Time
	else
	if (Type == ECsStatusEffectTriggerFrequency::Time)
	{
	}
}

bool FCsStatusEffectTriggerFrequencyInfo::CanApply() const
{
	const FCsStatusEffectTriggerFrequencyParams& Params = Data->GetTriggerFrequencyParams();
	const ECsStatusEffectTriggerFrequency& Type			= Params.Type;

	// Once
	if (Type == ECsStatusEffectTriggerFrequency::Once)
	{
		// Check Delay
		if (!bDelayComplete)
			return ElapsedDelayTime.Time >= Params.Delay;
		return ElapsedTotalTime.Time >= TotalTime;
	}
	// Count
	else
	if (Type == ECsStatusEffectTriggerFrequency::Count)
	{
		// Check Delay
		if (!bDelayComplete)
			return ElapsedDelayTime.Time >= Params.Delay;
		// Check Interval
		if (Params.Interval > 0.0f)
			return ElapsedIntervalTime.Time > Params.Interval;
		return true;
	}
	// Time
	else
	if (Type == ECsStatusEffectTriggerFrequency::Time)
	{
		// Check Delay
		if (!bDelayComplete)
			return ElapsedDelayTime.Time >= Params.Delay;
		return ElapsedIntervalTime.Time > Params.Interval;
	}
	// Infinite
	else
	if (Type == ECsStatusEffectTriggerFrequency::Infinite)
	{
		// Check Delay
		if (!bDelayComplete)
			return ElapsedDelayTime.Time >= Params.Delay;
		return ElapsedIntervalTime.Time > Params.Interval;
	}
	return false;
}

void FCsStatusEffectTriggerFrequencyInfo::Increment()
{
	bDelayComplete = true;
	ElapsedIntervalTime.Reset();
	++Count;
}

bool FCsStatusEffectTriggerFrequencyInfo::IsComplete() const
{
	const FCsStatusEffectTriggerFrequencyParams& Params = Data->GetTriggerFrequencyParams();
	const ECsStatusEffectTriggerFrequency& Type			= Params.Type;

	// Once
	if (Type == ECsStatusEffectTriggerFrequency::Once)
	{
		return ElapsedTotalTime.Time > TotalTime;
	}
	// Count
	else
	if (Type == ECsStatusEffectTriggerFrequency::Count)
	{
		return Count >= Params.Count;
	}
	// Time
	else
	if (Type == ECsStatusEffectTriggerFrequency::Time)
	{
		return ElapsedTotalTime.Time > TotalTime;
	}
	return false;
}

void FCsStatusEffectTriggerFrequencyInfo::Update(const FCsDeltaTime& DeltaTime)
{
	ElapsedTotalTime += DeltaTime;
	ElapsedDelayTime += DeltaTime;
	ElapsedIntervalTime += DeltaTime;
}

void FCsStatusEffectTriggerFrequencyInfo::Reset()
{
	Data = nullptr;
	TotalTime = 0.0f;
	ElapsedTotalTime.Reset();
	ElapsedDelayTime.Reset();
	ElapsedIntervalTime.Reset();
	Count = 0;
}

#pragma endregion FCsStatusEffectTriggerFrequencyInfo