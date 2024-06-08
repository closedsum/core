// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsTypes_Input.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Input)

// InputDevice
#pragma region

namespace NCsInputDevice
{
	namespace Ref
	{
		typedef EMCsInputDevice EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(MouseAndKeyboard, "Mouse and Keyboard");
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Gamepad);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(MotionController, "Motion Controller");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputDevice_MAX, "MAX");
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

		CSINPUT_API CS_ADD_TO_ENUM_FLAG_MAP(Mouse);
		CSINPUT_API CS_ADD_TO_ENUM_FLAG_MAP(Keyboard);
		CSINPUT_API CS_ADD_TO_ENUM_FLAG_MAP(Gamepad);
		CSINPUT_API CS_ADD_TO_ENUM_FLAG_MAP(Touch);
		CSINPUT_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(MotionController, "Motion Controller");
	}

	CSINPUT_API const int32 None = 0;
	CSINPUT_API const int32 All = 31; // 1 + 2 + 4 + 8 + 16
}

#pragma endregion InputMode

// InputType
#pragma region

namespace NCsInputType
{
	namespace Ref
	{
		typedef EMCsInputType EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP(Action);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Axis);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Trigger);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Location);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Rotation);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputType_MAX, "MAX");
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

		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstPressed, "First Pressed");
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Pressed);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstReleased, "First Released");
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Released);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstMoved, "First Moved");
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Moved);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstStationary, "First Stationary");
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Stationary);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputEvent_MAX, "MAX");
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

		CSINPUT_API CS_ADD_TO_ENUM_MAP(Void);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Float);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Vector);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Rotator);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputValue_MAX, "MAX");
	}
}

#pragma endregion InputValue

// ControllerHand
#pragma region

namespace NCsControllerHand
{
	namespace Ref
	{
		CSINPUT_API const Type Left = EMCsControllerHand::Get().Add(Type::Left, TEXT("Left"));
		CSINPUT_API const Type Right = EMCsControllerHand::Get().Add(Type::Right, TEXT("Right"));
		CSINPUT_API const Type ECsControllerHand_MAX = EMCsControllerHand::Get().Add(Type::ECsControllerHand_MAX, TEXT("ECsControllerHand_MAX"), TEXT("MAX"));
	}

	CSINPUT_API const uint8 MAX = (uint8)Type::ECsControllerHand_MAX;
}

#pragma endregion ControllerHand