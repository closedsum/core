// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Params/Point/CsTypes_SpawnerParams_Point.h"

// SpawnerPointSelection
#pragma region

namespace NCsSpawnerPointSelection
{
	namespace Ref
	{
		typedef EMCsSpawnerPointSelection EnumMapType;

		CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Index);
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(LastToFirst, "Last to First");
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Random);
		CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointSelection_MAX, "MAX");
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

				CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Index);
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(LastToFirst, "Last to First");
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP(Random);
				CSSPAWNER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ESelection_MAX, "MAX");
			}
		}
	}
}

#pragma endregion SpawnerPointSelection