// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Spawner/Params/Point/CsTypes_SpawnerParams_Point.h"
#include "Spawner/Params/Point/Generation/CsTypes_SpawnerParams_PointGeneration.h"

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NPoint
		{
			namespace NGeneration
			{
				struct CSCORE_API IGeneration : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IGeneration(){}
	
				#define ConditionType NCsSpawner::NPoint::NGeneration::ECondition
				#define CountType NCsSpawner::NPoint::NGeneration::ECount
				#define SelectionType NCsSpawner::NPoint::ESelection

					virtual const ConditionType& GetGenerationConditionType() const = 0;

					virtual const CountType& GetGenerationCountType() const = 0;

					virtual const int32& GetGenerationCount() const = 0;

					virtual const SelectionType& GetPointSelectionType() const = 0;

				#undef ConditionType
				#undef CountType
				#undef SelectionType
				};
			}
		}
	}
}