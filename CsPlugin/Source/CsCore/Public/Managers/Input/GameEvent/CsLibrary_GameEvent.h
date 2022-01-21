// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"
// Log
#include "Utility/CsLog.h"

class UObject;

namespace NCsGameEvent
{
	struct CSCORE_API FLibrary final
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
		static bool SafeIsAssociatedWith(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsGameEvent& Event, const FKey& Key, void(*Log)(const FString&) = &FCsLog::Warning);
	};
}