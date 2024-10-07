// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Game/Shutdown/CsGameInstance_Shutdown_Delegates.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class UObject;
class UGameInstance;
class ICsGameInstance_Shutdown_Event;

namespace NCsGameInstance
{
	namespace NShutdown
	{
		namespace NLibrary
		{
			using OnPreShutdownEventType = NCsGameInstance::FOnPreShutdown;
			using OnQueueExitGameEventType = NCsGameInstance::FOnQueueExitGame;

			class CSSEAMLESSTRANSITION_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

			public:

			// Interface
			#pragma region
			public:

				// Event
			#pragma region
			public:

				/**
				* Get the interface of type: ICsGameInstance_Shutdown_Event from GameInstance from ContextObject.
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						of
				*						A reference to the GameInstance.
				* return				ICsGameInstance_Shutdown_Event
				*/
				static ICsGameInstance_Shutdown_Event* GetEventInterfaceChecked(const FString& Context, const UObject* ContextObject);

			#pragma endregion Event

			#pragma endregion Interface

			// Events
			#pragma region
			public:

				static OnPreShutdownEventType& GetOnPreShutdown_EventChecked(const FString& Context, const UObject* ContextObject);
				static OnQueueExitGameEventType& GetOnQueueExitGame_EventChecked(const FString& Context, const UObject* ContextObject);

			#pragma endregion Events

			#undef LogLevel
			};
		}
	}
}

using CsGameInstanceShutdownLibrary = NCsGameInstance::NShutdown::NLibrary::FLibrary;