// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Point/CsTypes_SpawnerPoint.h"
#include "CsSpawner.h"

// SpawnerPointCount
#pragma region

namespace NCsSpawnerPointCount
{
	namespace Ref
	{
		typedef EMCsSpawnerPointCount EnumMapType;

		CSSPAWNER_API CS_ADD_TO_ENUM_MAP(None);
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalCount, "Total Count");
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(CountPerSpawn, "Count per Spawn");
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointCount_MAX, "MAX");
	}

	CSSPAWNER_API const uint8 MAX = (uint8)Type::ECsSpawnerPointCount_MAX;
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

				CSSPAWNER_API CS_ADD_TO_ENUM_MAP(None);
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalCount, "Total Count");
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(CountPerSpawn, "Count per Spawn");
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECount_MAX, "MAX");
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

		CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Random);
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(RandomShuffle, "Random Shuffle");
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Custom);
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointOrder_MAX, "MAX");
	}

	CSSPAWNER_API const uint8 MAX = (uint8)Type::ECsSpawnerPointOrder_MAX;
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

				CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Random);
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(RandomShuffle, "Random Shuffle");
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Custom);
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(EOrder_MAX, "MAX");
			}

			CSSPAWNER_API const uint8 MAX = (uint8)EOrder::EOrder_MAX;
		}
	}
}

#pragma endregion SpawnerPointOrder