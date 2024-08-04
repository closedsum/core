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
// World
#include "Engine/World.h"

namespace NCsGameInstance
{
	namespace NImpl
	{
		#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/

		FString FLibrary::PrintObjectAndClass(const UGameInstance* Object)
		{
			if (!Object)
				return FString::Printf(TEXT("INVALID"));
			return FString::Printf(TEXT("Object: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
		}

		FString FLibrary::PrintNameAndClass(const UGameInstance* Object)
		{
			if (!Object)
				return FString::Printf(TEXT("INVALID"));
			return FString::Printf(TEXT("%s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
		}

		// Get
		#pragma region

		UCsGameInstance* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetChecked<UCsGameInstance>(Context, ContextObject);
		}

		UCsGameInstance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			return CsGameInstanceLibrary::GetSafe<UCsGameInstance>(Context, ContextObject, Log);
		}

		#pragma endregion Get

		// Start
		#pragma region

		bool FLibrary::HasStartedFromEntryChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->HasStartedFromEntry();
		}

		bool FLibrary::SafeHasStartedFromEntry(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsGameInstance* GameInstance = GetSafe(Context, ContextObject, Log))
				return GameInstance->HasStartedFromEntry();
			return false;
		}

		#pragma endregion Start

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

		bool FLibrary::SafeIsMobilePreviewEditor(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsGameInstance* GameInstance = GetSafe(Context, ContextObject, Log))
			{
				return GameInstance->IsMobilePreviewEditor();
			}
			return false;
		}

		#pragma endregion Editor

		// Transition
		#pragma region
	
		bool FLibrary::HasFinishedTransitionChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->HasFinishedTransition();
		}

		#pragma endregion Transition

		// Events
		#pragma region

		#define OnQueueExitGameEventType NCsGameInstance::FOnQueueExitGame
		OnQueueExitGameEventType& FLibrary::GetOnQueueExitGame_EventChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetOnQueueExitGame_Event();
		}
		#undef OnQueueExitGameEventType

			// Transition
		#pragma region

		#define OnStartTransitionOutEventType NCsGameInstance::NTransition::FOut_OnStart
		#define OnFinishTransitionEventType NCsGameInstance::NTransition::FOnFinish

		OnStartTransitionOutEventType& FLibrary::GetTransitionOut_OnStart_EventChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetTransitionOut_OnStart_Event();
		}

		OnFinishTransitionEventType& FLibrary::GetTransition_OnFinish_EventChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetTransition_OnFinish_Event();
		}

		#undef OnStartTransitionOutEventType
		#undef OnFinishTransitionEventType

		#pragma endregion Transition

		#pragma endregion Events

		#undef LogLevel
	}
}