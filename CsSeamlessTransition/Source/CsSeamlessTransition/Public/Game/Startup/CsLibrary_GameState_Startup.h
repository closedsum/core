// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class ICsGameState_Startup;

namespace NCsGameState
{
	namespace NStartup
	{
		class CSSEAMLESSTRANSITION_API FLibrary final
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

		// Interface
		#pragma region
		public:

			/**
			* Get the interface of type: ICsGameState_Startup from GameState from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				ICsGameState_Startup
			*/
			static ICsGameState_Startup* GetInterfaceChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get interface of type: ICsGameState_Startup from GameInstance from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				ICsGameState_Startup
			*/
			static ICsGameState_Startup* GetSafeInterface(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static ICsGameState_Startup* GetSafeInterface(const FString& Context, const UObject* WorldContext, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				ICsGameState_Startup* Interface = GetSafeInterface(Context, WorldContext, Log);
				OutSuccess						   = Interface != nullptr;
				return Interface;
			}

		#pragma endregion Interface

		public:

			static bool IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext);

			static bool SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static bool SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				OutSuccess = SafeIsStartupComplete(Context, WorldContext, Log);
				return OutSuccess;
			}
		};
	}
}

using CsGameStateStartupLibrary = NCsGameState::NStartup::FLibrary;