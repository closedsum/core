// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/Point/Generation/CsTypes_SpawnerParams_PointGeneration.h"

// SpawnerPointGenerationCondition
#pragma region

namespace NCsSpawnerPointGenerationCondition
{
	namespace Ref
	{
		typedef EMCsSpawnerPointGenerationCondition EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Once);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(CycleComplete, "Cycle Complete");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointGenerationCondition_MAX, "MAX");
	}
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NGeneration
		{
			namespace NCondition
			{
				namespace Ref
				{
					typedef EMCondition EnumMapType;

					CSCORE_API CS_ADD_TO_ENUM_MAP(Once);
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(CycleComplete, "Cycle Complete");
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECondition_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion SpawnerPointGenerationCondition

// SpawnerPointGenerationCount
#pragma region

namespace NCsSpawnerPointGenerationCount
{
	namespace Ref
	{
		typedef EMCsSpawnerPointGenerationCount EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(SpawnCount, "Spawn Count");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(UserDefined, "User Defined");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointGenerationCount_MAX, "MAX");
	}
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NGeneration
		{
			namespace NCount
			{
				namespace Ref
				{
					typedef EMCount EnumMapType;

					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(SpawnCount, "Spawn Count");
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(UserDefined, "User Defined");
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECount_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion SpawnerPointGenerationCount