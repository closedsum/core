// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class UObject;
class UGameInstance;
class ICsGameState_Transition;

namespace NCsGameState
{
	namespace NTransition
	{
		class CSSEAMLESSTRANSITION_API FLibrary final
		{
		private:
			
			CS_DECLARE_STATIC_LOG_LEVEL

		// Interface
		#pragma region
		public:

			/**
			* Get the interface of type: ICsGameState_Transition from GameState from ContextObject.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				ICsGameState_Transition
			*/
			static ICsGameState_Transition* GetInterfaceChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the interface of type: ICsGameState_Transition from GameState from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				ICsGameState_Transition
			*/
			static ICsGameState_Transition* GetSafeInterface(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static ICsGameState_Transition* GetSafeInterface(const FString& Context, const UObject* WorldContext, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				ICsGameState_Transition* Interface = GetSafeInterface(Context, WorldContext, Log);
				OutSuccess						   = Interface != nullptr;
				return Interface;
			}

		#pragma endregion Interface

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
			* Safely, get whether the GameState has finished "Transitioning Out", which usually occurs when switching between levels.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutSuccess		(out) Whether the load was executing successfully or not.
			* @param Log			(optional)
			* return
			*/
			static bool SafeHasFinishedTransitionOut(const FString& Context, const UObject* WorldContext, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static bool SafeHasFinishedTransitionOut(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				bool OutSuccess = false;
				return SafeHasFinishedTransitionOut(Context, WorldContext, OutSuccess, Log);
			}

			/**
			* Begin the process of the GameState "Transitioning Out" (i.e. a Pre-Shutdown). THis is usually called before
			*  switching to another level.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void TransitionOutChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely, Begin the process of the GameState "Transitioning Out" (i.e. a Pre-Shutdown). THis is usually called before
			*  switching to another level.
			*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static bool SafeTransitionOut(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static bool SafeTransitionOut(const FString& Context, const UObject* WorldContext, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				OutSuccess = SafeTransitionOut(Context, WorldContext, Log);
				return OutSuccess;
			}
		};
	}
}

using CsGameStateTransitionLibrary = NCsGameState::NTransition::FLibrary;