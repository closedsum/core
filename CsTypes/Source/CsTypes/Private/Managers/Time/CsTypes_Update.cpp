// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsTypes_Update.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Update)

// UpdateGroup
#pragma region

namespace NCsUpdateGroup
{
	CSTYPES_API CS_CREATE_ENUM_STRUCT_CUSTOM(Custom, "Custom");
	CSTYPES_API CS_CREATE_ENUM_STRUCT_CUSTOM(EditorEngine, "Editor Engine");
	CSTYPES_API CS_CREATE_ENUM_STRUCT_CUSTOM(GameInstance, "Game Instance");
	CSTYPES_API CS_CREATE_ENUM_STRUCT_CUSTOM(GameState, "Game State");
	CSTYPES_API CS_CREATE_ENUM_STRUCT(Menu);
}

#pragma endregion UpdateGroup