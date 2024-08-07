// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "InputCoreTypes.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"
// Log
#include "Utility/CsInputLog.h"

class UObject;

namespace NCsGameEvent
{
	struct CSINPUT_API FLibrary final
	{
	public:

		/**
		* Safely check if the GameEvent is associated with the Key.
		* This looks at the PlayerInput.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param ControllerId
		* @param Event
		* @param Key
		* @param Log			(optional)
		* return				Whether the Action is associated with the Key or not.
		*/
		static bool SafeIsAssociatedWith(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsGameEvent& Event, const FKey& Key, void(*Log)(const FString&) = &NCsInput::FLog::Warning);
	};
}