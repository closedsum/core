// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"
#pragma once

// FCsStatusEffectTriggerFrequencyInfo
#pragma region

class ICsData_StatusEffect;

struct CSSE_API FCsStatusEffectTriggerFrequencyInfo
{
public:

	ICsData_StatusEffect* Data;

	float TotalTime;

	FCsDeltaTime ElapsedTotalTime;

	bool bDelayComplete;

	FCsDeltaTime ElapsedDelayTime;

	FCsDeltaTime ElapsedIntervalTime;

	int32 Count;

	FCsStatusEffectTriggerFrequencyInfo()
	{
	}

	void SetData(ICsData_StatusEffect* InData);

	bool CanApply() const;

	void Increment();

	bool IsComplete() const;

	void Update(const FCsDeltaTime& DeltaTime);

	void Reset();
};

#pragma endregion FCsStatusEffectTriggerFrequencyInfo