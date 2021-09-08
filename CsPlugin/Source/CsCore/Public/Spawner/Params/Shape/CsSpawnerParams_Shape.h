// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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