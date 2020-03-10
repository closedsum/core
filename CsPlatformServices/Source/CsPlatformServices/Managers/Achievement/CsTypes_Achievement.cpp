// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/CsTypes_Achievement.h"

#pragma once

// AchievementState
#pragma region

namespace NCsAchievementState
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementState, None);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementState, InProgress);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementState, Completed);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementState, ECsAchievementState_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementState_MAX;
}

#pragma endregion AchievementState

// AchievementProgress
#pragma region

namespace NCsAchievementProgress
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Normalized);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Standard);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Binary);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Count);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementProgress, Bitfield);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementProgress, ECsAchievementProgress_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementProgress_MAX;
}

#pragma endregion AchievementProgress

// AchievementAction
#pragma region

namespace NCsAchievementAction
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, QueryIds, "Query Ids");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, QueryDescriptions, "Query Descriptions");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, UpdateDescriptions, "Update Descriptions");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementAction, Write);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementAction, Complete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, CompleteAll, "Complete All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementAction, Reset);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, ResetAll, "Reset All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementAction, ECsAchievementAction_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementAction_MAX;
}

#pragma endregion AchievementAction

// AchievementActionState
#pragma region

namespace NCsAchievementActionState
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementActionState, None);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementActionState, InProgress, "In Progress");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsAchievementActionState, Complete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAchievementActionState, ECsAchievementActionState_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementActionState_MAX;
}

#pragma endregion AchievementActionState