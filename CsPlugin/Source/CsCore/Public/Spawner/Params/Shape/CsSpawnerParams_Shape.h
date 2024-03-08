// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Spawner/Params/CsTypes_SpawnerParams.h"

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NShape
		{
			struct CSCORE_API IShape : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IShape(){}
	
			#define ShapeType NCsSpawner::EShape
			#define CenterType NCsSpawner::NShape::ECenter
			#define DistributionType NCsSpawner::EDistribution

				virtual const ShapeType& GetShapeType() const = 0;

				virtual const CenterType& GetCenterType() const = 0;

				virtual const DistributionType& GetDistributionType() const = 0;

			#undef ShapeType
			#undef CenterType
			#undef DistributionType
			};
		}
	}
}