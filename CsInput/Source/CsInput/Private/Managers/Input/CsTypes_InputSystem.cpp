// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsTypes_InputSystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_InputSystem)

// InputSystem
#pragma region

namespace NCsInputSystem
{
	namespace Ref
	{
		typedef EMCsInputSystem EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP(Default);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Enhanced);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputSystem_MAX, "MAX");
	}
}

#pragma endregion InputSystem