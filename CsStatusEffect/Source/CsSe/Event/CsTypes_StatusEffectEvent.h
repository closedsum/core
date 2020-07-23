// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"
#pragma once

// FCsStatusEffectTriggerFrequencyInfo
#pragma region

class ICsStatusEffect;

struct CSSE_API FCsStatusEffectTriggerFrequencyInfo
{
public:

	ICsStatusEffect* StatusEffect;

	float TotalTime;

	FCsDeltaTime ElapsedTotalTime;

	bool bDelayComplete;

	FCsDeltaTime ElapsedDelayTime;

	FCsDeltaTime ElapsedIntervalTime;

	int32 Count;

	FCsStatusEffectTriggerFrequencyInfo()
	{
	}

	void SetStatusEffect(ICsStatusEffect* Effect);

	bool CanApply() const;

	void Increment();

	bool IsComplete() const;

	void Update(const FCsDeltaTime& DeltaTime);

	void Reset();
};

#pragma endregion FCsStatusEffectTriggerFrequencyInfo