// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsLibrary_GameMode_SeamlessTransition.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Game/CsGameMode_SeamlessTransition.h"
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

		#define USING_NS_CACHED using namespace NCsGameMode::NSeamlessTransition::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameMode::NSeamlessTransition::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

		// Interface
		#pragma region

		ICsGameMode_SeamlessTransition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameModeBase* GameMode = CsWorldLibrary::GetChecked(Context, WorldContext)->GetAuthGameMode();

			return CS_INTERFACE_CAST_CHECKED(GameMode, AGameModeBase, ICsGameMode_SeamlessTransition);
		}

		ICsGameMode_SeamlessTransition* FLibrary::GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel)
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

		bool FLibrary::SafeQueueForSeamlessTravel(const FString& Context, const UObject* WorldContext, AActor* Actor, LogLevel)
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

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}