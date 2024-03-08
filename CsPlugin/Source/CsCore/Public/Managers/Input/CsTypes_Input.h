// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumFlagMap.h"

#include "CsTypes_Input.generated.h"

// InputDevice
#pragma region

UENUM(BlueprintType)
enum class ECsInputDevice : uint8
{
	MouseAndKeyboard	UMETA(DisplayName = "Mouse And Keyboard"),
	Gamepad				UMETA(DisplayName = "Gamepad"),
	MotionController	UMETA(DisplayName = "MotionController"),
	ECsInputDevice_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputDevice : public TCsEnumMap<ECsInputDevice>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputDevice, ECsInputDevice)
};

namespace NCsInputDevice
{
	typedef ECsInputDevice Type;

	namespace Ref
	{
		extern CSCORE_API const Type MouseAndKeyboard;
		extern CSCORE_API const Type Gamepad;
		extern CSCORE_API const Type MotionController;
		extern CSCORE_API const Type ECsInputDevice_MAX;
	}
}

#define ECS_INPUT_DEVICE_MAX (uint8)ECsInputDevice::ECsInputDevice_MAX

#pragma endregion InputDevice

// InputMode
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsInputMode : uint8
{
	Mouse				UMETA(DisplayName = "Mouse"),				// 0
	Keyboard			UMETA(DisplayName = "Keyboard"),			// 1
	Gamepad				UMETA(DisplayName = "Gamepad"),				// 2
	Touch				UMETA(DisplayName = "Touch"),				// 3
	MotionController	UMETA(DisplayName = "Motion Controller"),	// 4
};

struct CSCORE_API EMCsInputMode : public TCsEnumFlagMap<ECsInputMode>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsInputMode, ECsInputMode)
};

namespace NCsInputMode
{
	typedef ECsInputMode Type;

	namespace Ref
	{
		extern CSCORE_API const Type Mouse;
		extern CSCORE_API const Type Keyboard;
		extern CSCORE_API const Type Gamepad;
		extern CSCORE_API const Type Touch;
		extern CSCORE_API const Type MotionController;
	}

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#define CS_INPUT_MODE_NONE 0

#pragma endregion InputMode

// InputType
#pragma region

UENUM(BlueprintType)
enum class ECsInputType : uint8
{
	Action				UMETA(DisplayName = "Action"),
	Axis				UMETA(DisplayName = "Axis"),
	Trigger				UMETA(DisplayName = "Trigger"),
	Location			UMETA(DisplayName = "Location"),
	Rotation			UMETA(DisplayName = "Rotation"),
	ECsInputType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputType : public TCsEnumMap<ECsInputType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputType, ECsInputType)
};

namespace NCsInputType
{
	typedef ECsInputType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Action;
		extern CSCORE_API const Type Axis;
		extern CSCORE_API const Type Trigger;
		extern CSCORE_API const Type Location;
		extern CSCORE_API const Type Rotation;
		extern CSCORE_API const Type ECsInputType_MAX;
	}
}

#pragma endregion InputType

// InputEvent
#pragma region

UENUM(BlueprintType)
enum class ECsInputEvent: uint8
{
	FirstPressed		UMETA(DisplayName = "First Pressed"),
	Pressed				UMETA(DisplayName = "Pressed"),
	FirstReleased		UMETA(DisplayName = "First Released"),
	Released			UMETA(DisplayName = "Released"),
	FirstMoved			UMETA(DisplayName = "First Moved"),
	Moved				UMETA(DisplayName = "Moved"),
	FirstStationary		UMETA(DisplayName = "First Stationary"),
	Stationary			UMETA(DisplayName = "Stationary"),
	ECsInputEvent_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputEvent : public TCsEnumMap<ECsInputEvent>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputEvent, ECsInputEvent)
};

namespace NCsInputEvent
{
	typedef ECsInputEvent Type;

	namespace Ref
	{
		extern CSCORE_API const Type FirstPressed;
		extern CSCORE_API const Type Pressed;
		extern CSCORE_API const Type FirstReleased;
		extern CSCORE_API const Type Released;
		extern CSCORE_API const Type FirstMoved;
		extern CSCORE_API const Type Moved;
		extern CSCORE_API const Type FirstStationary;
		extern CSCORE_API const Type Stationary;
		extern CSCORE_API const Type ECsInputEvent_MAX;
	}
}

#pragma endregion InputEvent

// InputValue
#pragma region

UENUM(BlueprintType)
enum class ECsInputValue : uint8
{
	Void				UMETA(DisplayName = "Void"),
	Float				UMETA(DisplayName = "Float"),
	Vector				UMETA(DisplayName = "Vector"),
	Rotator				UMETA(DisplayName = "Rotator"),
	ECsInputValue_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputValue : public TCsEnumMap<ECsInputValue>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputValue, ECsInputValue)
};

namespace NCsInputValue
{
	typedef ECsInputValue Type;

	namespace Ref
	{
		extern CSCORE_API const Type Void;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type Vector;
		extern CSCORE_API const Type Rotator;
		extern CSCORE_API const Type ECsInputValue_MAX;
	}
}

#pragma endregion InputValue

// ControllerHand
#pragma region

UENUM(BlueprintType)
enum class ECsControllerHand : uint8
{
	Left					UMETA(DisplayName = "Left"),
	Right					UMETA(DisplayName = "Right"),
	ECsControllerHand_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsControllerHand : public TCsEnumMap<ECsControllerHand>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsControllerHand, ECsControllerHand)
};

namespace NCsControllerHand
{
	typedef ECsControllerHand Type;

	namespace Ref
	{
		extern CSCORE_API const Type Left;
		extern CSCORE_API const Type Right;
		extern CSCORE_API const Type ECsControllerHand_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ControllerHand