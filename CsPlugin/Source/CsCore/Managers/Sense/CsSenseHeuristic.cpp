// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sense/CsSenseHeuristic.h"
#include "CsCore.h"

// SenseHeuristicScoreSortOrder
#pragma region

namespace NCsSenseHeuristicScoreSortOrder
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSenseHeuristicScoreSortOrder, Descending);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSenseHeuristicScoreSortOrder, Ascending);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSenseHeuristicScoreSortOrder, Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSenseHeuristicScoreSortOrder, ECsSenseHeuristicScoreSortOrder_MAX, "MAX");
	}
}

#pragma endregion SenseHeuristicScoreSortOrder