// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsTypes_StatusEffectEvent.h"

#include "Data/CsData_StatusEffect.h"

// FCsStatusEffectTriggerFrequencyInfo
#pragma region

#define DataType NCsStatusEffect::NData::IData
void FCsStatusEffectTriggerFrequencyInfo::SetData(DataType* InData)
{
#undef DataType

	Data = InData;

	typedef NCsStatusEffect::NTrigger::FFrequencyParams TriggerFrequencyParamsType;

	const TriggerFrequencyParamsType& Params = Data->GetTriggerFrequencyParams();

	typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

	const FrequencyType& Type = Params.Type;

	bDelayComplete = Params.Delay > 0.0f;

	// Once
	if (Type == FrequencyType::Once)
	{
		TotalTime = Params.Delay;
	}
	// Count
	else
	if (Type == FrequencyType::Count)
	{
		TotalTime += Params.Delay;
		TotalTime += Params.Delay * Params.Interval;
	}
	// Time
	else
	if (Type == FrequencyType::Time)
	{
	}
}

bool FCsStatusEffectTriggerFrequencyInfo::CanApply() const
{
	typedef NCsStatusEffect::NTrigger::FFrequencyParams TriggerFrequencyParamsType;

	const TriggerFrequencyParamsType& Params = Data->GetTriggerFrequencyParams();

	typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

	const FrequencyType& Type = Params.Type;

	// Once
	if (Type == FrequencyType::Once)
	{
		// Check Delay
		if (!bDelayComplete)
			return ElapsedDelayTime.Time >= Params.Delay;
		return ElapsedTotalTime.Time >= TotalTime;
	}
	// Count
	else
	if (Type == FrequencyType::Count)
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
	if (Type == FrequencyType::Time)
	{
		// Check Delay
		if (!bDelayComplete)
			return ElapsedDelayTime.Time >= Params.Delay;
		return ElapsedIntervalTime.Time > Params.Interval;
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
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
	typedef NCsStatusEffect::NTrigger::FFrequencyParams TriggerFrequencyParamsType;

	const TriggerFrequencyParamsType& Params = Data->GetTriggerFrequencyParams();

	typedef NCsStatusEffect::NTrigger::EFrequency FrequencyType;

	const FrequencyType& Type = Params.Type;

	// Once
	if (Type == FrequencyType::Once)
	{
		return ElapsedTotalTime.Time > TotalTime;
	}
	// Count
	else
	if (Type == FrequencyType::Count)
	{
		return Count >= Params.Count;
	}
	// Time
	else
	if (Type == FrequencyType::Time)
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