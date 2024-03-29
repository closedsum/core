// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Gesture/CsTypes_Gesture.h"

// GestureDevice
#pragma region

namespace NCsGestureDevice
{
	namespace Ref
	{
		CSCORE_API const Type Mouse = EMCsGestureDevice::Get().Add(Type::Mouse, TEXT("Mouse"));
		CSCORE_API const Type MotionController = EMCsGestureDevice::Get().Add(Type::MotionController, TEXT("Motion Controller"));
		CSCORE_API const Type ECsGestureDevice_MAX = EMCsGestureDevice::Get().Add(Type::ECsGestureDevice_MAX, TEXT("ECsGestureDevice_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsGestureDevice_MAX;
}

#pragma endregion GestureDevice