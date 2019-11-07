// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"

// TimeGroup
#pragma region

namespace NCsTimeGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsTimeGroup, GameInstance, "Game Instance");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsTimeGroup, GameState, "Game State");
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsTimeGroup, Menu);
}

#pragma endregion TimeGroup

const FCsDeltaTime FCsDeltaTime::Zero;