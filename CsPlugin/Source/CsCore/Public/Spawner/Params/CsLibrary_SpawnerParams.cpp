// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsLibrary_SpawnerParams.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Spawner
#include "Spawner/Params/Shape/CsSpawnerParams_Shape.h"
#include "Spawner/Params/Shape/CsSpawnerParams_ShapeCircle.h"

namespace NCsSpawner
{
	namespace NParams
	{
		#define ParamsType NCsSpawner::NParams::IParams

		bool FLibrary::IsValidChecked(const FString& Context, const ParamsType* Params)
		{
			CS_IS_PTR_NULL_CHECKED(Params)

			typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;
			typedef NCsSpawner::NParams::FCount CountParamsType;

			const FrequencyParamsType& FrequencyParams = Params->GetFrequencyParams();
			const CountParamsType& CountParams		   = Params->GetCountParams();

			check(FrequencyParams.IsValidChecked(Context));

			check(CountParams.IsValidChecked(Context));

			// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)
			typedef NCsSpawner::NParams::NShape::IShape ShapeParamsType;

			if (const ShapeParamsType* ShapeParams = GetSafeInterfaceChecked<ShapeParamsType>(Context, Params))
			{
				typedef NCsSpawner::EMShape ShapeMapType;
				typedef NCsSpawner::EShape ShapeType;

				check(ShapeMapType::Get().IsValidEnumChecked(Context, ShapeParams->GetShapeType()));

				typedef NCsSpawner::NShape::EMCenter CenterMapType;
				typedef NCsSpawner::NShape::ECenter CenterType;

				check(CenterMapType::Get().IsValidEnumChecked(Context, ShapeParams->GetCenterType()));

				typedef NCsSpawner::EMDistribution DistributionMapType;
				typedef NCsSpawner::EDistribution DistributionType;

				check(DistributionMapType::Get().IsValidEnumChecked(Context, ShapeParams->GetDistributionType()));
			}
			// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
			typedef NCsSpawner::NParams::NShape::ICircle CircleParamsType;

			if (const CircleParamsType* CircleParams = GetSafeInterfaceChecked<CircleParamsType>(Context, Params))
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(CircleParams->GetMinRadius(), 0.0f)

				CS_IS_FLOAT_GREATER_THAN_CHECKED(CircleParams->GetMaxRadius(), 0.0f)
			}
			return true;
		}
		
		bool FLibrary::IsValid(const FString& Context, const ParamsType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL(Params)

			typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;
			typedef NCsSpawner::NParams::FCount CountParamsType;

			const FrequencyParamsType& FrequencyParams = Params->GetFrequencyParams();
			const CountParamsType& CountParams		   = Params->GetCountParams();

			if (FrequencyParams.IsValid(Context, Log))
				return false;

			if (CountParams.IsValid(Context, Log))
				return false;

			// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)
			typedef NCsSpawner::NParams::NShape::IShape ShapeParamsType;

			if (const ShapeParamsType* ShapeParams = GetSafeInterfaceChecked<ShapeParamsType>(Context, Params))
			{
				typedef NCsSpawner::EMShape ShapeMapType;
				typedef NCsSpawner::EShape ShapeType;

				CS_IS_ENUM_VALID(ShapeMapType, ShapeType, ShapeParams->GetShapeType())

				typedef NCsSpawner::NShape::EMCenter CenterMapType;
				typedef NCsSpawner::NShape::ECenter CenterType;

				CS_IS_ENUM_VALID(CenterMapType, CenterType, ShapeParams->GetCenterType())

				typedef NCsSpawner::EMDistribution DistributionMapType;
				typedef NCsSpawner::EDistribution DistributionType;

				CS_IS_ENUM_VALID(DistributionMapType, DistributionType, ShapeParams->GetDistributionType())
			}
			// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
			typedef NCsSpawner::NParams::NShape::ICircle CircleParamsType;

			if (const CircleParamsType* CircleParams = GetSafeInterfaceChecked<CircleParamsType>(Context, Params))
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(CircleParams->GetMinRadius(), 0.0f)

				CS_IS_FLOAT_GREATER_THAN(CircleParams->GetMaxRadius(), 0.0f)
			}
			return false;
		}

		float FLibrary::CalculateTotalTime(const FString& Context, const ParamsType* Params)
		{
			CS_IS_PTR_NULL_CHECKED(Params)

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

		#undef ParamsType
	}
}