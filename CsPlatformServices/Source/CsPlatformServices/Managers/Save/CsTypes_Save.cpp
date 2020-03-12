// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Save/CsTypes_Save.h"

#pragma once

// SaveStorage
#pragma region

namespace NCsSaveStorage
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveStorage, Local);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveStorage, Cloud);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveStorage, ECsSaveStorage_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSaveStorage_MAX;
}

#pragma endregion SaveStorage

// Save
#pragma region

namespace NCsSave
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save1, "Save 1");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save2, "Save 2");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save3, "Save 3");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save4, "Save 4");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save5, "Save 5");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save6, "Save 6");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save7, "Save 7");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, Save8, "Save 8");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSave, ECsSave_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSave_MAX;
}

#pragma endregion Save

const FCsSaveFileInfo FCsSaveFileInfo::Invalid;

// SaveAction
#pragma region

namespace NCsSaveAction
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveAction, Enumerate);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveAction, Read);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, ReadAll, "Read All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveAction, Write);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, WriteAll, "Write All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveAction, Delete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, DeleteAll, "Delete All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveAction, ECsSaveAction_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSaveAction_MAX;
}

#pragma endregion SaveAction

// SaveActionState
#pragma region

namespace NCsSaveActionState
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveActionState, None);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveActionState, InProgress, "In Progress");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsSaveActionState, Complete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSaveActionState, ECsSaveActionState_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSaveActionState_MAX;
}

#pragma endregion SaveActionState