// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Startup/CsLibrary_GameInstance_Startup.h"

// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Startup/CsGameInstance_Startup.h"

namespace NCsGameInstance
{
	namespace NStartup
	{
		using LogClassType = NCsSeamlessTransition::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		// Interface
		#pragma region

		ICsGameInstance_Startup* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* GameInstance = CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
			
			return CS_INTERFACE_CAST_CHECKED(GameInstance, UObject, ICsGameInstance_Startup);
		}

		ICsGameInstance_Startup* FLibrary::GetSafeInterface(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UObject* GameInstance = CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log))
				return CS_INTERFACE_CAST(GameInstance, UObject, ICsGameInstance_Startup);
			return nullptr;
		}

		#pragma endregion Interface

		bool FLibrary::HasStartedFromEntryChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->HasStartedFromEntry();
		}

		bool FLibrary::SafeHasStartedFromEntry(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (ICsGameInstance_Startup* Interface = GetSafeInterface(Context, ContextObject, Log))
				return Interface->HasStartedFromEntry();
			return false;
		}
	}
}