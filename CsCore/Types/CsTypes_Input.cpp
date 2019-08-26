// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Input.h"

// InputDevice
#pragma region

namespace NCsInputDevice
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, MouseAndKeyboard, "Mouse and Keyboard");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputDevice, Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, MotionController, "Motion Controller");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, ECsInputDevice_MAX, "MAX");
	}
}

#pragma endregion InputDevice

// InputType
#pragma region

namespace NCsInputType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Action);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Axis);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Trigger);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Location);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputType, ECsInputType_MAX, "MAX");
	}
}

#pragma endregion InputType

// InputEvent
#pragma region

namespace NCsInputEvent
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstPressed, "First Pressed");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Pressed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstReleased, "First Released");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Released);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstMoved, "First Moved");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Moved);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstStationary, "First Stationary");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Stationary);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, ECsInputEvent_MAX, "MAX");
	}
}

#pragma endregion InputEvent

// InputValue
#pragma region

namespace NCsInputValue
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Void);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Rotator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValue, ECsInputValue_MAX, "MAX");
	}
}

#pragma endregion InputValue