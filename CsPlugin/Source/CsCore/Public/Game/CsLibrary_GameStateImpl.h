// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class AGameStateBase;
class UObject;

namespace NCsGameState
{
	namespace NImpl
	{
		class CSCORE_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &FCsLog::Warning

		public:

			static FString PrintGameStateAndClass(AGameStateBase* GameState);

		// ICsGameState_Startup
		#pragma region
		public:

			/**
			* Get whether the GameState has finished its Startup. This usually occurs after GameState has broadcasted StartPlay.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get whether the GameState has finished its Startup. This usually occurs after GameState has broadcasted StartPlay.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static bool SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeIsStartupComplete(Context, WorldContext, Log);
				return OutSuccess;
			}

		#pragma endregion ICsGameState_Startup

		// ICsGameState_Transition
		#pragma region
		public:
		
			/**
			* Get whether the GameState has finished "Transitioning Out", which usually occurs when switching between levels.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool HasFinishedTransitionOutChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Begin the process of the GameState "Transitioning Out" (i.e. a Pre-Shutdown). THis is usually called before
			*  switching to another level.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void TransitionOutChecked(const FString& Context, const UObject* WorldContext);

		#pragma endregion ICsGameState_Transition

		// ICsGameState_ExitGame
		#pragma region
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

		#pragma endregion ICsGameState_ExitGame

		#undef LogLevel
		};
	}
}

using CsGameStateImplLibrary = NCsGameState::NImpl::FLibrary;