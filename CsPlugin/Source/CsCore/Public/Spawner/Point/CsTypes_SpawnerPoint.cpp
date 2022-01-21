// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Point/CsTypes_SpawnerPoint.h"
#include "CsCore.h"

// SpawnerPointCount
#pragma region

namespace NCsSpawnerPointCount
{
	namespace Ref
	{
		typedef EMCsSpawnerPointCount EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalCount, "Total Count");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(CountPerSpawn, "Count per Spawn");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointCount_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerPointCount_MAX;
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NCount
		{
			namespace Ref
			{
				typedef EMCount EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(None);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalCount, "Total Count");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(CountPerSpawn, "Count per Spawn");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECount_MAX, "MAX");
			}
		}
	}
}

#pragma endregion SpawnerPointCount

// SpawnerPointOrder
#pragma region

namespace NCsSpawnerPointOrder
{
	namespace Ref
	{
		typedef EMCsSpawnerPointOrder EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Random);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RandomShuffle, "Random Shuffle");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointOrder_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerPointOrder_MAX;
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NOrder
		{
			namespace Ref
			{
				typedef EMOrder EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(Random);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RandomShuffle, "Random Shuffle");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
				CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EOrder_MAX, "MAX");
			}

			CSCORE_API const uint8 MAX = (uint8)EOrder::EOrder_MAX;
		}
	}
}

#pragma endregion SpawnerPointOrder