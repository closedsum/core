// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Game/Transition/CsGameInstance_Transition_Delegates.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class UObject;
class UGameInstance;
class ICsGameInstance_Transition;
class ICsGameInstance_Transition_Event;

namespace NCsGameInstance
{
	namespace NTransition
	{
		namespace NLibrary
		{
			using OnStartTransitionOutEventType = NCsGameInstance::NTransition::FOut_OnStart;
			using OnFinishTransitionEventType = NCsGameInstance::NTransition::FOnFinish;

			class CSSEAMLESSTRANSITION_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

			public:

				static FString PrintObjectAndClass(const UGameInstance* Object);

				static FString PrintNameAndClass(const UGameInstance* Object);

			// Interface
			#pragma region
			public:

				/**
				* Get the interface of type: ICsGameInstance_Transition from GameInstance from ContextObject.
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						of
				*						A reference to the GameInstance.
				* return				ICsGameInstance_Transition
				*/
				static ICsGameInstance_Transition* GetInterfaceChecked(const FString& Context, const UObject* ContextObject);

				/**
				* Safely get the interface of type: ICsGameInstance_Transition from GameInstance from WorldContext.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
				*						of
				*						A reference to the GameInstance.
				* @param Log
				* return				ICsGameInstance_Transition
				*/
				static ICsGameInstance_Transition* GetSafeInterface(const FString& Context, const UObject* ContextObject, LogLevel);
				FORCEINLINE static ICsGameInstance_Transition* GetSafeInterface(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel)
				{
					ICsGameInstance_Transition* Interface = GetSafeInterface(Context, ContextObject, Log);
					OutSuccess							  = Interface != nullptr;
					return Interface;
				}

				// Event
			#pragma region
			public:

				/**
				* Get the interface of type: ICsGameInstance_Transition_Event from GameInstance from ContextObject.
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						of
				*						A reference to the GameInstance.
				* return				ICsGameInstance_Transition_Event
				*/
				static ICsGameInstance_Transition_Event* GetEventInterfaceChecked(const FString& Context, const UObject* ContextObject);

			#pragma endregion Event

			#pragma endregion Interface

			public:

				static bool HasFinishedTransitionChecked(const FString& Context, const UObject* ContextObject);

			// Events
			#pragma region
			public:

				static OnStartTransitionOutEventType& GetTransitionOut_OnStart_EventChecked(const FString& Context, const UObject* ContextObject);
				static OnFinishTransitionEventType& GetTransition_OnFinish_EventChecked(const FString& Context, const UObject* ContextObject);

			#pragma endregion Events

			#undef LogLevel
			};
		}
	}
}

using CsGameInstanceTransitionLibrary = NCsGameInstance::NTransition::NLibrary::FLibrary;