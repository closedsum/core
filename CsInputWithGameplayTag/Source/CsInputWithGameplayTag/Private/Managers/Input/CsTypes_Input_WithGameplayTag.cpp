// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input_WithGameplayTag.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Input_WithGameplayTag)

// InputActionEvent
#pragma region

namespace NCsInputActionEvent
{
	namespace Ref
	{
		typedef EMCsInputActionEvent EnumMapType;

		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(FirstPressed);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(Pressed);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(FirstReleased);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(Released);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(FirstMoved);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(Moved);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(FirstStationary);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP(Stationary);
		CSINPUTWITHGAMEPLAYTAG_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputActionEvent_MAX, "MAX");
	}

	namespace Mask
	{
		CSINPUTWITHGAMEPLAYTAG_API const uint32 Boolean = (1 << static_cast<uint32>(ECsInputActionEvent::FirstPressed)) | (1 << static_cast<uint32>(ECsInputActionEvent::Pressed)) | (1 << static_cast<uint32>(ECsInputActionEvent::FirstReleased)) | (1 << static_cast<uint32>(ECsInputActionEvent::Released));
		CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstPressedOrPressed = (1 << static_cast<uint32>(ECsInputActionEvent::FirstPressed)) | (1 << static_cast<uint32>(ECsInputActionEvent::Pressed));
		CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstReleasedOrReleased = (1 << static_cast<uint32>(ECsInputActionEvent::FirstReleased)) | (1 << static_cast<uint32>(ECsInputActionEvent::Released));
		CSINPUTWITHGAMEPLAYTAG_API const uint32 NonBoolean = (1 << static_cast<uint32>(ECsInputActionEvent::FirstMoved)) | (1 << static_cast<uint32>(ECsInputActionEvent::Moved)) | (1 << static_cast<uint32>(ECsInputActionEvent::FirstStationary)) | (1 << static_cast<uint32>(ECsInputActionEvent::Stationary));
		CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstMovedOrMoved = (1 << static_cast<uint32>(ECsInputActionEvent::FirstMoved)) | (1 << static_cast<uint32>(ECsInputActionEvent::Moved));
		CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstStationaryOrStationary = (1 << static_cast<uint32>(ECsInputActionEvent::FirstStationary)) | (1 << static_cast<uint32>(ECsInputActionEvent::Stationary));		
	}
}

#pragma endregion InputActionEvent
