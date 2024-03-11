// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Params/Point/CsTypes_SpawnerParams_Point.h"
#include "Params/Point/Generation/CsTypes_SpawnerParams_PointGeneration.h"

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NPoint
		{
			namespace NGeneration
			{
				struct CSSPAWNER_API IGeneration : public ICsGetInterfaceMap
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