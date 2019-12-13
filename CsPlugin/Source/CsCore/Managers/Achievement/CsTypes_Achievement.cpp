// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/CsTypes_Achievement.h"

#pragma once

// AchievementState
#pragma region

namespace NCsAchievementState
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementState, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementState, InProgress);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementState, Completed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementState, ECsAchievementState_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAchievementState_MAX;
}

#pragma endregion AchievementState

// AchievementProgress
#pragma region

namespace NCsAchievementProgress
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Normalized);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Standard);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Binary);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Count);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Bitfield);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementProgress, ECsAchievementProgress_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAchievementProgress_MAX;
}

#pragma endregion AchievementProgress

// AchievementAction
#pragma region

namespace NCsAchievementAction
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, QueryIds, "Query Ids");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, QueryDescriptions, "Query Descriptions");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, UpdateDescriptions, "Update Descriptions");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementAction, Write);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementAction, Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, CompleteAll, "Complete All");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementAction, Reset);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, ResetAll, "Reset All");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, ECsAchievementAction_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAchievementAction_MAX;
}

#pragma endregion AchievementAction

// AchievementActionState
#pragma region

namespace NCsAchievementActionState
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementActionState, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementActionState, InProgress, "In Progress");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsAchievementActionState, Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementActionState, ECsAchievementActionState_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAchievementActionState_MAX;
}

#pragma endregion AchievementActionState