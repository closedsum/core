// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/SeamlessTransition/CsLibrary_GameMode_SeamlessTransition.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameMode.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Game/SeamlessTransition/CsGameMode_SeamlessTransition.h"
#include "Game/SeamlessTransition/Event/CsGameMode_SeamlessTransition_Event.h"
// Game
#include "GameFramework/GameModeBase.h"
// World
#include "Engine/World.h"

namespace NCsGameMode
{
	namespace NSeamlessTransition
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameMode::NSeamlessTransition::FLibrary, GetSafeInterface);
				}
			}
		}

		using LogClassType = NCsSeamlessTransition::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsGameMode::NSeamlessTransition::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameMode::NSeamlessTransition::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		using OnPostSeamlessTravelCompleteEventType = NCsGameMode::NSeamlessTravel::NPost::FOnComplete;

		// Interface
		#pragma region

		ICsGameMode_SeamlessTransition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameModeBase* GameMode = CsWorldLibrary::GetChecked(Context, WorldContext)->GetAuthGameMode();

			return CS_INTERFACE_CAST_CHECKED(GameMode, AGameModeBase, ICsGameMode_SeamlessTransition);
		}

		ICsGameMode_SeamlessTransition* FLibrary::GetSafeInterface(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext, Log))
			{
				AGameModeBase* GameMode = World->GetAuthGameMode();

				return CS_INTERFACE_CAST(GameMode, AGameModeBase, ICsGameMode_SeamlessTransition);
			}
			return nullptr;
		}

		ICsGameMode_SeamlessTransition* FLibrary::GetSafeInterface(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafeInterface);

			return GetSafeInterface(Context, WorldContext, nullptr);
		}

		#pragma endregion Interface

		// Seamless  Travel
		#pragma region
	
		void FLibrary::QueueForSeamlessTravelChecked(const FString& Context, const UObject* WorldContext, AActor* Actor)
		{
			CS_IS_PENDING_KILL_CHECKED(Actor)

			GetInterfaceChecked(Context, WorldContext)->QueueForSeamlessTravel(Actor);
		}

		bool FLibrary::SafeQueueForSeamlessTravel(const FString& Context, const UObject* WorldContext, AActor* Actor, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL(Actor)

			if (ICsGameMode_SeamlessTransition* Interface = GetSafeInterface(Context, WorldContext, Log))
			{
				Interface->QueueForSeamlessTravel(Actor);
				return true;
			}
			return false;
		}

		void FLibrary::ClearQueueForSeamlessTravelChecked(const FString& Context, const UObject* WorldContext)
		{
			GetInterfaceChecked(Context, WorldContext)->ClearQueueForSeamlessTravel();
		}

		#pragma endregion Seamless Travel
	
		// Event
		#pragma region

		OnPostSeamlessTravelCompleteEventType& FLibrary::GetPostSeamlessTravel_OnComplete_EventChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameModeBase* GameMode						    = CsGameModeLibrary::GetChecked(Context, WorldContext);
			ICsGameMode_SeamlessTransition_Event* Interface = CS_INTERFACE_CAST_CHECKED(GameMode, AGameModeBase, ICsGameMode_SeamlessTransition_Event);

			return Interface->GetPostSeamlessTravel_OnComplete_Event();
		}

		#pragma endregion Event

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}