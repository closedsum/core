// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_InputSystem.generated.h"

// InputSystem
#pragma region

/**
* Describes tne Input System to use (i.e. Enhanced Input, ... etc)
*/
UENUM(BlueprintType)
enum class ECsInputSystem : uint8
{
	Default				UMETA(DisplayName = "Default"),
	Enhanced			UMETA(DisplayName = "Enhanced"),
	ECsInputSystem_MAX	UMETA(Hidden),
};

struct CSINPUT_API EMCsInputSystem : public TCsEnumMap<ECsInputSystem>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputSystem, ECsInputSystem)
};

namespace NCsInputSystem
{
	typedef ECsInputSystem Type;

	namespace Ref
	{
		extern CSINPUT_API const Type Default;
		extern CSINPUT_API const Type Enhanced;
		extern CSINPUT_API const Type ECsInputSystem_MAX;
	}
}

#pragma endregion InputSystem