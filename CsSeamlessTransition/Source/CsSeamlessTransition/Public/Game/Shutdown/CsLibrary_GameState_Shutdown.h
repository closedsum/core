// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class ICsGameState_Shutdown;

namespace NCsGameState
{
	namespace NShutdown
	{
		class CSSEAMLESSTRANSITION_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

		// Interface
		#pragma region
		public:

			/**
			* Get the interface of type: ICsGameState_Shutdown from GameState from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				ICsGameState_Shutdown
			*/
			static ICsGameState_Shutdown* GetInterfaceChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get interface of type: ICsGameState_Shutdown from GameState from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				ICsGameState_Shutdown
			*/
			static ICsGameState_Shutdown* GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static ICsGameState_Shutdown* GetSafeInterface(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				ICsGameState_Shutdown* Interface = GetSafeInterface(Context, WorldContext, Log);
				OutSuccess						 = Interface != nullptr;
				return Interface;
			}

		#pragma endregion Interface

		public:

			/**
			* Get whether the GameState has finished the process of "Exiting the Game". The occurs when there is a request
			*  to Exit the Game (i.e. Shutdown the running Game). This "works" in tandem with the GameInstance. The GameInstance
			*  captures the request from the User (or some other event) to Exit the Game and waits for the GameState to properly
			*  Shutdown / Exit Game.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool HasFinishedExitGameChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get whether the GameState has finished the process of "Exiting the Game". The occurs when there is a request
			*  to Exit the Game (i.e. Shutdown the running Game). This "works" in tandem with the GameInstance. The GameInstance
			*  captures the request from the User (or some other event) to Exit the Game and waits for the GameState to properly
			*  Shutdown / Exit Game.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static bool SafeHasFinishedExitGame(const FString& Context, const UObject* WorldContext, LogLevel);
			static bool SafeHasFinishedExitGame(const UObject* WorldContext);

		#undef LogLevel
		};
	}
}

using CsGameStateShudownLibrary = NCsGameState::NShutdown::FLibrary;