// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Update.h"

// UpdateGroup
#pragma region

namespace NCsUpdateGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsUpdateGroup, EditorEngine, "Editor Engine");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsUpdateGroup, GameInstance, "Game Instance");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsUpdateGroup, GameState, "Game State");
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsUpdateGroup, Menu);
}

#pragma endregion UpdateGroup