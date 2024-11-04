// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameInstanceImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/CsGameInstance.h"

namespace NCsGameInstance
{
	namespace NImpl
	{
		using LogClassType = FCsLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		// Get
		#pragma region

		UCsGameInstance* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetChecked<UCsGameInstance>(Context, ContextObject);
		}

		UCsGameInstance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			return CsGameInstanceLibrary::GetSafe<UCsGameInstance>(Context, ContextObject, Log);
		}

		#pragma endregion Get

		// Editor
		#pragma region
	
		bool FLibrary::IsPIEChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->IsPIE();
		}

		bool FLibrary::IsMobilePIEChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->IsMobilePIE();
		}

		bool FLibrary::IsStandaloneFromEditorChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->IsStandaloneFromEditor();
		}
	
		bool FLibrary::IsStandaloneMobileFromEditorChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->IsStandaloneMobileFromEditor();
		}

		bool FLibrary::IsMobilePreviewEditorChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->IsMobilePreviewEditor();
		}

		bool FLibrary::SafeIsMobilePreviewEditor(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsGameInstance* GameInstance = GetSafe(Context, ContextObject, Log))
			{
				return GameInstance->IsMobilePreviewEditor();
			}
			return false;
		}

		#pragma endregion Editor
	}
}