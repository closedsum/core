// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Save/CsTypes_Save.h"

#pragma once

// Save
#pragma region

namespace NCsSave
{
	namespace Ref
	{
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save1, "Save 1");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save2, "Save 2");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save3, "Save 3");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save4, "Save 4");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save5, "Save 5");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save6, "Save 6");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save7, "Save 7");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save8, "Save 8");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, ECsSave_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSave_MAX;
}

#pragma endregion Save

const FCsSaveFileInfo FCsSaveFileInfo::Invalid;

// SaveAction
#pragma region

namespace NCsSaveAction
{
	namespace Ref
	{
		CSCORE_API RS_ADD_TO_ENUM_MAP(EMCsSaveAction, Enumerate);
		CSCORE_API RS_ADD_TO_ENUM_MAP(EMCsSaveAction, Read);
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, ReadAll, "Read All");
		CSCORE_API RS_ADD_TO_ENUM_MAP(EMCsSaveAction, Write);
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, WriteAll, "Write All");
		CSCORE_API RS_ADD_TO_ENUM_MAP(EMCsSaveAction, Delete);
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, DeleteAll, "Delete All");
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, ECsSaveAction_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSaveAction_MAX;
}

#pragma endregion SaveAction

// SaveActionState
#pragma region

namespace NCsSaveActionState
{
	namespace Ref
	{
		CSCORE_API RS_ADD_TO_ENUM_MAP(EMCsSaveActionState, None);
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveActionState, InProgress, "In Progress");
		CSCORE_API RS_ADD_TO_ENUM_MAP(EMCsSaveActionState, Complete);
		CSCORE_API RS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveActionState, ECsSaveActionState_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSaveActionState_MAX;
}

#pragma endregion SaveActionState