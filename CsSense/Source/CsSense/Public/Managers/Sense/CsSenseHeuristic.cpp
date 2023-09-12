// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sense/CsSenseHeuristic.h"
#include "CsSense.h"

// SenseHeuristicScoreSortOrder
#pragma region

namespace NCsSenseHeuristicScoreSortOrder
{
	namespace Ref
	{
		typedef EMCsSenseHeuristicScoreSortOrder EnumMapType;

		CSSENSE_API CS_ADD_TO_ENUM_MAP(Descending);
		CSSENSE_API CS_ADD_TO_ENUM_MAP(Ascending);
		CSSENSE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSSENSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSenseHeuristicScoreSortOrder_MAX, "MAX");
	}
}

#pragma endregion SenseHeuristicScoreSortOrder