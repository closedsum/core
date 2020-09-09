// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsTypes_SpawnerParams.h"

// SpawnerFrequency
#pragma region

namespace NCsSpawnerFrequency
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Once);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Count);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, TimeCount);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, TimeInterval);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Infinite);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSpawnerFrequency, ECsSpawnerFrequency_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerFrequency_MAX;
}

#pragma endregion SpawnerFrequency

// FCsSpawnerCountParams
#pragma region

bool FCsSpawnerCountParams::IsValidChecked(const FString& Context) const
{
	checkf(CountPerSpawn >= 1, TEXT("%s: CountPerSpawn MUST be >= 1."), *Context);
	return true;
}

#pragma endregion FCsSpawnerCountParams

// FCsSpawnerFrequencyParams
#pragma region

bool FCsSpawnerFrequencyParams::IsValidChecked(const FString& Context) const
{
	// Once
	if (Type == ECsSpawnerFrequency::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == ECsSpawnerFrequency::Count)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::Count."), *Context);
	}
	// TimeCount
	else
	if (Type == ECsSpawnerFrequency::TimeCount)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::TimeCount."), *Context);
	}
	// TimeInterval
	else
	if (Type == ECsSpawnerFrequency::TimeInterval)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::TimeInterval."), *Context);
	}
	// Infinite
	else
	if (Type == ECsSpawnerFrequency::Infinite)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::Infinite."), *Context);
	}
	return true;
}

void FCsSpawnerFrequencyParams::OnPostEditChange()
{
	if (Time > 0.0f)
	{
		// TimeCount
		if (Type == ECsSpawnerFrequency::TimeCount)
		{
			if (Count >= 1)
			{
				Interval = Time / (float)Count;
			}
		}
		// TimeInterval
		else
		if (Type == ECsSpawnerFrequency::TimeInterval)
		{
			if (Interval > 0.0f)
			{
				Count = FMath::FloorToInt(Time / Interval);
			}
		}
	}
}

#pragma endregion FCsSpawnerFrequencyParams


// SpawnerPoint
#pragma region

namespace NCsSpawnerPoint
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerPoint, Self);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerPoint, Transform);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerPoint, Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerPoint, Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSpawnerPoint, ECsSpawnerPoint_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerPoint_MAX;
}

#pragma endregion SpawnerPoint
