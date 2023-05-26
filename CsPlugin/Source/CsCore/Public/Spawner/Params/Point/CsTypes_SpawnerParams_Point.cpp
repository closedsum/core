// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/Point/CsTypes_SpawnerParams_Point.h"

// SpawnerPointSelection
#pragma region

namespace NCsSpawnerPointSelection
{
	namespace Ref
	{
		typedef EMCsSpawnerPointSelection EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Index);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LastToFirst, "Last to First");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Random);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointSelection_MAX, "MAX");
	}
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NSelection
		{
			namespace Ref
			{
				typedef EMSelection EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(Index);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LastToFirst, "Last to First");
				CSCORE_API CS_ADD_TO_ENUM_MAP(Random);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ESelection_MAX, "MAX");
			}
		}
	}
}

#pragma endregion SpawnerPointSelection