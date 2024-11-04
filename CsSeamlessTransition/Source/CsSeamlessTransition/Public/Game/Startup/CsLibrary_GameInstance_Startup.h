// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class ICsGameInstance_Startup;

namespace NCsGameInstance
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
			* Get the interface of type: ICsGameInstance_Startup from GameInstance from ContextObject.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* return				ICsGameInstance_Startup
			*/
			static ICsGameInstance_Startup* GetInterfaceChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get interface of type: ICsGameInstance_Startup from GameInstance from WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
			*						of
			*						A reference to the GameInstance.
			* @param Log
			* return				ICsGameInstance_Startup
			*/
			static ICsGameInstance_Startup* GetSafeInterface(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			FORCEINLINE static ICsGameInstance_Startup* GetSafeInterface(const FString& Context, const UObject* ContextObject, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				ICsGameInstance_Startup* Interface = GetSafeInterface(Context, ContextObject, Log);
				OutSuccess						   = Interface != nullptr;
				return Interface;
			}

		#pragma endregion Interface

		public:

			static bool HasStartedFromEntryChecked(const FString& Context, const UObject* ContextObject);

			static bool SafeHasStartedFromEntry(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		};
	}
}

using CsGameInstanceStartupLibrary = NCsGameInstance::NStartup::FLibrary;