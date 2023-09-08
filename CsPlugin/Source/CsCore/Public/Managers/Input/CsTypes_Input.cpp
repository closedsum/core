// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsTypes_Input.h"
#include "CsCore.h"

// InputDevice
#pragma region

namespace NCsInputDevice
{
	namespace Ref
	{
		typedef EMCsInputDevice EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MouseAndKeyboard, "Mouse and Keyboard");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MotionController, "Motion Controller");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputDevice_MAX, "MAX");
	}
}

#pragma endregion InputDevice

// InputMode
#pragma region

namespace NCsInputMode
{
	namespace Ref
	{
		typedef EMCsInputMode EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Mouse);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Keyboard);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Touch);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(MotionController, "Motion Controller");
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 31; // 1 + 2 + 4 + 8 + 16
}

#pragma endregion InputMode

// InputType
#pragma region

namespace NCsInputType
{
	namespace Ref
	{
		typedef EMCsInputType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Action);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Axis);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Trigger);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Location);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputType_MAX, "MAX");
	}
}

#pragma endregion InputType

// InputEvent
#pragma region

namespace NCsInputEvent
{
	namespace Ref
	{
		typedef EMCsInputEvent EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstPressed, "First Pressed");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Pressed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstReleased, "First Released");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Released);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstMoved, "First Moved");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Moved);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstStationary, "First Stationary");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Stationary);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputEvent_MAX, "MAX");
	}
}

#pragma endregion InputEvent

// InputValue
#pragma region

namespace NCsInputValue
{
	namespace Ref
	{
		typedef EMCsInputValue EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Void);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rotator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputValue_MAX, "MAX");
	}
}

#pragma endregion InputValue

// ControllerHand
#pragma region

namespace NCsControllerHand
{
	namespace Ref
	{
		CSCORE_API const Type Left = EMCsControllerHand::Get().Add(Type::Left, TEXT("Left"));
		CSCORE_API const Type Right = EMCsControllerHand::Get().Add(Type::Right, TEXT("Right"));
		CSCORE_API const Type ECsControllerHand_MAX = EMCsControllerHand::Get().Add(Type::ECsControllerHand_MAX, TEXT("ECsControllerHand_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsControllerHand_MAX;
}

#pragma endregion ControllerHand