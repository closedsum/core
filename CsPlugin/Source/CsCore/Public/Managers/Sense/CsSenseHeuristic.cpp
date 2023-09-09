// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sense/CsSenseHeuristic.h"
#include "CsCore.h"

// SenseHeuristicScoreSortOrder
#pragma region

namespace NCsSenseHeuristicScoreSortOrder
{
	namespace Ref
	{
		typedef EMCsSenseHeuristicScoreSortOrder EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Descending);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Ascending);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSenseHeuristicScoreSortOrder_MAX, "MAX");
	}
}

#pragma endregion SenseHeuristicScoreSortOrder