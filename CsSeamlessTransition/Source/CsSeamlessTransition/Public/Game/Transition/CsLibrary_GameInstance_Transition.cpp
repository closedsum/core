// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Transition/CsLibrary_GameInstance_Transition.h"

// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Transition/CsGameInstance_Transition.h"
#include "Game/Transition/Event/CsGameInstance_Transition_Event.h"

namespace NCsGameInstance
{
	namespace NTransition
	{
		namespace NLibrary
		{
			#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

			// Interface
			#pragma region

			ICsGameInstance_Transition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* ContextObject)
			{
				UObject* GameInstance = CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
			
				return CS_INTERFACE_CAST_CHECKED(GameInstance, UObject, ICsGameInstance_Transition);
			}

			ICsGameInstance_Transition* FLibrary::GetSafeInterface(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				if (UObject* GameInstance = CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log))
					return CS_INTERFACE_CAST(GameInstance, UObject, ICsGameInstance_Transition);
				return nullptr;
			}

				// Event
			#pragma region

			ICsGameInstance_Transition_Event* FLibrary::GetEventInterfaceChecked(const FString& Context, const UObject* ContextObject)
			{
				UObject* GameInstance = CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
			
				return CS_INTERFACE_CAST_CHECKED(GameInstance, UObject, ICsGameInstance_Transition_Event);
			}

			#pragma endregion Event

			#pragma endregion Interface

			bool FLibrary::HasFinishedTransitionChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetInterfaceChecked(Context, ContextObject)->HasFinishedTransition();
			}

			// Events
			#pragma region

			OnStartTransitionOutEventType& FLibrary::GetTransitionOut_OnStart_EventChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetEventInterfaceChecked(Context, ContextObject)->GetTransitionOut_OnStart_Event();
			}

			OnFinishTransitionEventType& FLibrary::GetTransition_OnFinish_EventChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetEventInterfaceChecked(Context, ContextObject)->GetTransition_OnFinish_Event();
			}

			#pragma endregion Events

			#undef LogLevel
		}
	}
}