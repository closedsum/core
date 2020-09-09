// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsLibrary_SpawnerParams.h"

float FCsLibrary_SpawnerParams::CalculateTotalTime(const ICsSpawnerParams* Params)
{
	checkf(Params, TEXT("FCsLibrary_SpawnerParams::CalculateTotalTime: Params is NULL."));

	const FCsSpawnerFrequencyParams& FrequencyParams = Params->GetFrequencyParams();
	const FCsSpawnerCountParams& CountParams		 = Params->GetCountParams();

	float TotalTime = 0.0f;

	// Once
	if (FrequencyParams.Type == ECsSpawnerFrequency::Once)
	{
		TotalTime += FrequencyParams.Delay;
		TotalTime += CountParams.CountPerSpawn * CountParams.TimeBetweenCountPerSpawn;
	}
	// Count
	else
	if (FrequencyParams.Type == ECsSpawnerFrequency::Count)
	{
		TotalTime += FrequencyParams.Delay;

		// If there "time" from spawning objects, add that to the end instead
		// the last interval time.
		if (CountParams.CountPerSpawn > 1 &&
			CountParams.TimeBetweenCountPerSpawn > 0.0f)
		{
			TotalTime += FMath::Max(0, FrequencyParams.Count - 1) * FrequencyParams.Interval;
			TotalTime += CountParams.CountPerSpawn * CountParams.TimeBetweenCountPerSpawn;
		}
		else
		{
			TotalTime += FrequencyParams.Count * FrequencyParams.Interval;
		}
	}
	// TimeCount
	else
	if (FrequencyParams.Type == ECsSpawnerFrequency::TimeCount)
	{
		TotalTime += FrequencyParams.Delay;

		// If there "time" from spawning objects, add that to the end instead
		// the last interval time.
		if (CountParams.CountPerSpawn > 1 &&
			CountParams.TimeBetweenCountPerSpawn > 0.0f)
		{
			TotalTime += FMath::Max(0, FrequencyParams.Count - 1) * FrequencyParams.Interval;
			TotalTime += CountParams.CountPerSpawn * CountParams.TimeBetweenCountPerSpawn;
		}
		else
		{
			TotalTime += FrequencyParams.Time;
		}
	}
	// TimeInterval
	else
	if (FrequencyParams.Type == ECsSpawnerFrequency::TimeInterval)
	{
		TotalTime += FrequencyParams.Delay;

		// If there "time" from spawning objects, add that to the end instead
		// the last interval time.
		if (CountParams.CountPerSpawn > 1 &&
			CountParams.TimeBetweenCountPerSpawn > 0.0f)
		{
			TotalTime += FMath::Max(0, FrequencyParams.Count - 1) * FrequencyParams.Interval;
			TotalTime += CountParams.CountPerSpawn * CountParams.TimeBetweenCountPerSpawn;
		}
		else
		{
			TotalTime += FrequencyParams.Count * FrequencyParams.Interval;
		}
	}
	// Infinite
	if (FrequencyParams.Type == ECsSpawnerFrequency::Infinite)
	{
		TotalTime = 0.0f;
	}

	return TotalTime;
}