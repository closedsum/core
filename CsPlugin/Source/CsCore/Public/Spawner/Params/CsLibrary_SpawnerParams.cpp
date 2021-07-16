// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsLibrary_SpawnerParams.h"

namespace NCsSpawner
{
	namespace NParams
	{
		#define ParamsType NCsSpawner::NParams::IParams
		float FLibrary::CalculateTotalTime(const ParamsType* Params)
		{
		#undef ParamsType

			checkf(Params, TEXT("FCsLibrary_SpawnerParams::CalculateTotalTime: Params is NULL."));

			typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;
			typedef NCsSpawner::NParams::FCount CountParamsType;

			const FrequencyParamsType& FrequencyParams = Params->GetFrequencyParams();
			const CountParamsType& CountParams		   = Params->GetCountParams();

			float TotalTime = 0.0f;

			typedef NCsSpawner::EFrequency FrequencyType;

			// Once
			if (FrequencyParams.GetType() == FrequencyType::Once)
			{
				TotalTime += FrequencyParams.GetDelay();
				TotalTime += CountParams.GetCountPerSpawn() * CountParams.GetTimeBetweenCountPerSpawn();
			}
			// Count
			else
			if (FrequencyParams.GetType() == FrequencyType::Count)
			{
				TotalTime += FrequencyParams.GetDelay();

				// If there "time" from spawning objects, add that to the end instead
				// the last interval time.
				if (CountParams.GetCountPerSpawn() > 1 &&
					CountParams.GetTimeBetweenCountPerSpawn() > 0.0f)
				{
					TotalTime += FMath::Max(0, FrequencyParams.GetCount() - 1) * FrequencyParams.GetInterval();
					TotalTime += CountParams.GetCountPerSpawn() * CountParams.GetTimeBetweenCountPerSpawn();
				}
				else
				{
					TotalTime += FrequencyParams.GetCount() * FrequencyParams.GetInterval();
				}
			}
			// TimeCount
			else
			if (FrequencyParams.GetType() == FrequencyType::TimeCount)
			{
				TotalTime += FrequencyParams.GetDelay();

				// If there "time" from spawning objects, add that to the end instead
				// the last interval time.
				if (CountParams.GetCountPerSpawn() > 1 &&
					CountParams.GetTimeBetweenCountPerSpawn() > 0.0f)
				{
					TotalTime += FMath::Max(0, FrequencyParams.GetCount() - 1) * FrequencyParams.GetInterval();
					TotalTime += CountParams.GetCountPerSpawn() * CountParams.GetTimeBetweenCountPerSpawn();
				}
				else
				{
					TotalTime += FrequencyParams.GetTime();
				}
			}
			// TimeInterval
			else
			if (FrequencyParams.GetType() == FrequencyType::TimeInterval)
			{
				TotalTime += FrequencyParams.GetDelay();

				// If there "time" from spawning objects, add that to the end instead
				// the last interval time.
				if (CountParams.GetCountPerSpawn() > 1 &&
					CountParams.GetTimeBetweenCountPerSpawn() > 0.0f)
				{
					TotalTime += FMath::Max(0, FrequencyParams.GetCount() - 1) * FrequencyParams.GetInterval();
					TotalTime += CountParams.GetCountPerSpawn() * CountParams.GetTimeBetweenCountPerSpawn();
				}
				else
				{
					TotalTime += FrequencyParams.GetCount() * FrequencyParams.GetInterval();
				}
			}
			// Infinite
			if (FrequencyParams.GetType() == FrequencyType::Infinite)
			{
				TotalTime = 0.0f;
			}

			return TotalTime;
		}
	}
}