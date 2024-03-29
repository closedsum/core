// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsTypes_InputSystem.h"
#include "CsCore.h"

// InputSystem
#pragma region

namespace NCsInputSystem
{
	namespace Ref
	{
		typedef EMCsInputSystem EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Default);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Enhanced);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputSystem_MAX, "MAX");
	}
}

#pragma endregion InputSystem