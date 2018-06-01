// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Input.h"

EMCsInputDevice* EMCsInputDevice::Instance;

EMCsInputDevice& EMCsInputDevice::Get()
{
	if (!Instance)
		Instance = new EMCsInputDevice();
	return *Instance;
}

namespace ECsInputDevice
{
	namespace Str
	{
		CSCORE_API const TCsString MouseAndKeyboard = TCsString(TEXT("MouseAndKeyboard"), TEXT("mouseandkeyboard"));
		CSCORE_API const TCsString Gamepad = TCsString(TEXT("Gamepad"), TEXT("gamepad"));
		CSCORE_API const TCsString MotionController = TCsString(TEXT("MotionController"), TEXT("motioncontroller"));
	}

	namespace Ref
	{
		CSCORE_API const Type MouseAndKeyboard = EMCsInputDevice::Get().Add(Type::MouseAndKeyboard, TEXT("MouseAndKeyboard"), TEXT("Mouse and Keyboard"));
		CSCORE_API const Type Gamepad = EMCsInputDevice::Get().Add(Type::Gamepad, TEXT("Gamepad"), TEXT("Gamepad"));
		CSCORE_API const Type MotionController = EMCsInputDevice::Get().Add(Type::MotionController, TEXT("MotionController"), TEXT("Motion Controller"));
		CSCORE_API const Type ECsInputDevice_MAX = EMCsInputDevice::Get().Add(Type::ECsInputDevice_MAX, TEXT("ECsInputDevice_MAX"), TEXT("MAX"));
	}
}

EMCsInputType* EMCsInputType::Instance;

EMCsInputType& EMCsInputType::Get()
{
	if (!Instance)
		Instance = new EMCsInputType();
	return *Instance;
}

namespace ECsInputType
{
	namespace Str
	{
		CSCORE_API const TCsString Action = TCsString(TEXT("Action"), TEXT("action"));
		CSCORE_API const TCsString Axis = TCsString(TEXT("Axis"), TEXT("axis"));
		CSCORE_API const TCsString Trigger = TCsString(TEXT("Trigger"), TEXT("trigger"));
		CSCORE_API const TCsString Location = TCsString(TEXT("Location"), TEXT("location"));
		CSCORE_API const TCsString Rotation = TCsString(TEXT("Rotation"), TEXT("rotation"));
	}

	namespace Ref
	{
		CSCORE_API const Type Action = EMCsInputType::Get().Add(Type::Action, TEXT("Action"));
		CSCORE_API const Type Axis = EMCsInputType::Get().Add(Type::Axis, TEXT("Axis"));
		CSCORE_API const Type Trigger = EMCsInputType::Get().Add(Type::Trigger, TEXT("Trigger"));
		CSCORE_API const Type Location = EMCsInputType::Get().Add(Type::Location, TEXT("Location"));
		CSCORE_API const Type Rotation = EMCsInputType::Get().Add(Type::Rotation, TEXT("Rotation"));
		CSCORE_API const Type ECsInputType_MAX = EMCsInputType::Get().Add(Type::ECsInputType_MAX, TEXT("ECsInputType_MAX"));
	}
}

EMCsInputEvent* EMCsInputEvent::Instance;

EMCsInputEvent& EMCsInputEvent::Get()
{
	if (!Instance)
		Instance = new EMCsInputEvent();
	return *Instance;
}

namespace ECsInputEvent
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		CSCORE_API const TCsString FirstPressed = TCsString(TEXT("FirstPressed"), TEXT("firstpressed"), TEXT("first pressed"));
		CSCORE_API const TCsString Pressed = TCsString(TEXT("Pressed"), TEXT("pressed"), TEXT("pressed"));
		CSCORE_API const TCsString FirstReleased = TCsString(TEXT("FirstReleased"), TEXT("firstreleased"), TEXT("first released"));
		CSCORE_API const TCsString Released = TCsString(TEXT("Released"), TEXT("released"), TEXT("released"));
		CSCORE_API const TCsString FirstMoved = TCsString(TEXT("FirstMoved"), TEXT("firstmoved"), TEXT("first moved"));
		CSCORE_API const TCsString Moved = TCsString(TEXT("Moved"), TEXT("moved"), TEXT("moved"));
		CSCORE_API const TCsString FirstStationary = TCsString(TEXT("FirstStationary"), TEXT("firststationary"), TEXT("first stationary"));
		CSCORE_API const TCsString Stationary = TCsString(TEXT("Stationary"), TEXT("stationary"), TEXT("stationary"));
	}

	namespace Ref
	{
		CSCORE_API const Type FirstPressed = Type::FirstPressed;
		CSCORE_API const Type Pressed = Type::Pressed;
		CSCORE_API const Type FirstReleased = Type::FirstReleased;
		CSCORE_API const Type Released = Type::Released;
		CSCORE_API const Type FirstMoved = Type::FirstMoved;
		CSCORE_API const Type Moved = Type::Moved;
		CSCORE_API const Type FirstStationary = Type::FirstStationary;
		CSCORE_API const Type Stationary = Type::Stationary;
		CSCORE_API const Type ECsInputEvent_MAX = Type::ECsInputEvent_MAX;
	}
}

namespace ECsInputValue
{
	namespace Str
	{
		CSCORE_API const TCsString Void = TCsString(TEXT("Void"), TEXT("void"));
		CSCORE_API const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		CSCORE_API const TCsString Vector = TCsString(TEXT("Vector"), TEXT("vector"));
		CSCORE_API const TCsString Rotator = TCsString(TEXT("Rotator"), TEXT("rotator"));
	}

	namespace Ref
	{
		CSCORE_API const Type Void = Type::Void;
		CSCORE_API const Type Float = Type::Float;
		CSCORE_API const Type Vector = Type::Vector;
		CSCORE_API const Type Rotator = Type::Rotator;
		CSCORE_API const Type ECsInputValue_MAX = Type::ECsInputValue_MAX;
	}
}

EMCsInputActionMap* EMCsInputActionMap::Instance;

EMCsInputActionMap& EMCsInputActionMap::Get()
{
	if (!Instance)
		Instance = new EMCsInputActionMap();
	return *Instance;
}

EMCsInputAction* EMCsInputAction::Instance;

EMCsInputAction& EMCsInputAction::Get()
{
	if (!Instance)
		Instance = new EMCsInputAction();
	return *Instance;
}

EMCsGameEvent* EMCsGameEvent::Instance;

EMCsGameEvent& EMCsGameEvent::Get()
{
	if (!Instance)
		Instance = new EMCsGameEvent();
	return *Instance;
}