// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Shutdown/CsLibrary_GameInstance_Shutdown.h"

// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Shutdown/Event/CsGameInstance_Shutdown_Event.h"


namespace NCsGameInstance
{
	namespace NShutdown
	{
		namespace NLibrary
		{
			#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

			// Interface
			#pragma region

				// Event
			#pragma region

			ICsGameInstance_Shutdown_Event* FLibrary::GetEventInterfaceChecked(const FString& Context, const UObject* ContextObject)
			{
				UObject* GameInstance = CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
			
				return CS_INTERFACE_CAST_CHECKED(GameInstance, UObject, ICsGameInstance_Shutdown_Event);
			}

			#pragma endregion Event

			#pragma endregion Interface

			// Events
			#pragma region

			OnPreShutdownEventType& FLibrary::GetOnPreShutdown_EventChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetEventInterfaceChecked(Context, ContextObject)->GetOnPreShutdown_Event();
			}

			OnQueueExitGameEventType& FLibrary::GetOnQueueExitGame_EventChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetEventInterfaceChecked(Context, ContextObject)->GetOnQueueExitGame_Event();
			}

			#pragma endregion Events

			#undef LogLevel
		}
	}
}