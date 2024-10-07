// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class ICsGameState_Startup;

namespace NCsGameState
{
	namespace NStartup
	{
		class CSSEAMLESSTRANSITION_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

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
			static ICsGameState_Startup* GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static ICsGameState_Startup* GetSafeInterface(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				ICsGameState_Startup* Interface = GetSafeInterface(Context, WorldContext, Log);
				OutSuccess						   = Interface != nullptr;
				return Interface;
			}

		#pragma endregion Interface

		public:

			static bool IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext);

			static bool SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static bool SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeIsStartupComplete(Context, WorldContext, Log);
				return OutSuccess;
			}

		#undef LogLevel
		};
	}
}

using CsGameStateStartupLibrary = NCsGameState::NStartup::FLibrary;