// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class UObject;
class ICsGameState_SeamlessTransition;

namespace NCsGameState
{
	namespace NSeamlessTransition
	{
		struct CSSEAMLESSTRANSITION_API FLibrary final
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

		// Get
		#pragma region
		public:

			/**
			* Get Interface of type: ICsGameState_SeamlessTransition from the GameState from WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static ICsGameState_SeamlessTransition* GetInterfaceChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get Interface of type: ICsGameState_SeamlessTransition the GameState from WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static ICsGameState_SeamlessTransition* GetSafeInterface(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Safely get Interface of type: ICsGameState_SeamlessTransition from the GameState from WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static ICsGameState_SeamlessTransition* GetSafeInterface(const UObject* WorldContext);

			/**
			* Whether it is possible to get Interface of type: ICsGameState_SeamlessTransition from the GameState from WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool CanGetInterfaceChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely check whether it is possible to get Interface of type: ICsGameState_SeamlessTransition from the GameState from WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static bool CanGetSafeInterface(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Get

		public:

			static void SeamlessTransition_TransitionOutChecked(const FString& Context, const UObject* WorldContext);

			static bool SeamlessTransition_Transition_IsTransitionOutCompleteChecked(const FString& Context, const UObject* WorldContext);

			static bool SeamlessTransition_Transition_IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext);
		};
	}
}

using CsGSSeamlessTransitionLibrary = NCsGameState::NSeamlessTransition::FLibrary;