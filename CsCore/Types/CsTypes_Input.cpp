// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Input.h"

// InputDevice
CS_DEFINE_ENUM_MAP_BODY(EMCsInputDevice)

namespace NCsInputDevice
{
	namespace Ref
	{
		CSCORE_API const Type MouseAndKeyboard = EMCsInputDevice::Get().Add(Type::MouseAndKeyboard, TEXT("MouseAndKeyboard"), TEXT("Mouse and Keyboard"));
		CSCORE_API const Type Gamepad = EMCsInputDevice::Get().Add(Type::Gamepad, TEXT("Gamepad"), TEXT("Gamepad"));
		CSCORE_API const Type MotionController = EMCsInputDevice::Get().Add(Type::MotionController, TEXT("MotionController"), TEXT("Motion Controller"));
		CSCORE_API const Type ECsInputDevice_MAX = EMCsInputDevice::Get().Add(Type::ECsInputDevice_MAX, TEXT("ECsInputDevice_MAX"), TEXT("MAX"));
	}
}

// InputType
CS_DEFINE_ENUM_MAP_BODY(EMCsInputType)

namespace NCsInputType
{
	namespace Ref
	{
		CSCORE_API const Type Action = EMCsInputType::Get().Add(Type::Action, TEXT("Action"));
		CSCORE_API const Type Axis = EMCsInputType::Get().Add(Type::Axis, TEXT("Axis"));
		CSCORE_API const Type Trigger = EMCsInputType::Get().Add(Type::Trigger, TEXT("Trigger"));
		CSCORE_API const Type Location = EMCsInputType::Get().Add(Type::Location, TEXT("Location"));
		CSCORE_API const Type Rotation = EMCsInputType::Get().Add(Type::Rotation, TEXT("Rotation"));
		CSCORE_API const Type ECsInputType_MAX = EMCsInputType::Get().Add(Type::ECsInputType_MAX, TEXT("ECsInputType_MAX"), TEXT("MAX"));
	}
}

// InputEvent
CS_DEFINE_ENUM_MAP_BODY(EMCsInputEvent)

namespace NCsInputEvent
{
	namespace Ref
	{
		CSCORE_API const Type FirstPressed = EMCsInputEvent::Get().Add(Type::FirstPressed, TEXT("FirstPressed"), TEXT("First Pressed"));
		CSCORE_API const Type Pressed = EMCsInputEvent::Get().Add(Type::Pressed, TEXT("Pressed"), TEXT("Pressed"));
		CSCORE_API const Type FirstReleased = EMCsInputEvent::Get().Add(Type::FirstReleased, TEXT("FirstReleased"), TEXT("First Released"));
		CSCORE_API const Type Released = EMCsInputEvent::Get().Add(Type::Released, TEXT("Released"), TEXT("Released"));
		CSCORE_API const Type FirstMoved = EMCsInputEvent::Get().Add(Type::FirstMoved, TEXT("FirstMoved"), TEXT("First Moved"));
		CSCORE_API const Type Moved = EMCsInputEvent::Get().Add(Type::Moved, TEXT("Moved"), TEXT("Moved"));
		CSCORE_API const Type FirstStationary = EMCsInputEvent::Get().Add(Type::FirstStationary, TEXT("FirstStationary"), TEXT("First Stationary"));
		CSCORE_API const Type Stationary = EMCsInputEvent::Get().Add(Type::Stationary, TEXT("Stationary"), TEXT("Stationary"));
		CSCORE_API const Type ECsInputEvent_MAX = EMCsInputEvent::Get().Add(Type::ECsInputEvent_MAX, TEXT("ECsInputEvent_MAX"), TEXT("MAX"));
	}
}

// InputValue
CS_DEFINE_ENUM_MAP_BODY(EMCsInputValue)

namespace NCsInputValue
{
	namespace Ref
	{
		CSCORE_API const Type Void = EMCsInputValue::Get().Add(Type::Void, TEXT("Void"));
		CSCORE_API const Type Float = EMCsInputValue::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type Vector = EMCsInputValue::Get().Add(Type::Vector, TEXT("Vector"));
		CSCORE_API const Type Rotator = EMCsInputValue::Get().Add(Type::Rotator, TEXT("Rotator"));
		CSCORE_API const Type ECsInputValue_MAX = EMCsInputValue::Get().Add(Type::ECsInputValue_MAX, TEXT("ECsInputValue_MAX"), TEXT("MAX"));
	}
}

// InputActionMap
CS_DEFINE_ENUM_STRUCT_MASK_MAP_BODY(EMCsInputActionMap)

// InputAction
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsInputAction)

// GameEvent
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsGameEvent)