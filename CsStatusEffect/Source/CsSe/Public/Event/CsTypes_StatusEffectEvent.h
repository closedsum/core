// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"
#include "Types/CsTypes_Macro.h"
#pragma once

// FCsStatusEffectTriggerFrequencyInfo
#pragma region

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

struct CSSE_API FCsStatusEffectTriggerFrequencyInfo
{
public:

#define DataType NCsStatusEffect::NData::IData

	DataType* Data;

	float TotalTime;

	FCsDeltaTime ElapsedTotalTime;

	bool bDelayComplete;

	FCsDeltaTime ElapsedDelayTime;

	FCsDeltaTime ElapsedIntervalTime;

	int32 Count;

	FCsStatusEffectTriggerFrequencyInfo()
	{
	}

	void SetData(DataType* InData);

	bool CanApply() const;

	void Increment();

	bool IsComplete() const;

	void Update(const FCsDeltaTime& DeltaTime);

	void Reset();

#undef DataType
};

#pragma endregion FCsStatusEffectTriggerFrequencyInfo