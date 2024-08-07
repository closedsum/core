// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/ConsoleCommand/CsLibrary_Coordinator_ConsoleCommand.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsConsoleCommand
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsConsoleCommand::NCoordinator::FLibrary, GetSafeContextRoot);
				}
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsConsoleCommand::FLog::Warning*/

	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			UWorld* World				= CsWorldLibrary::GetChecked(Context, WorldContext);
			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));
			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext, LogLevel)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			UGameInstance* GameInstance = World->GetGameInstance();

			if (!GameInstance)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName())));
			}
			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			using namespace NCsConsoleCommand::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#undef LogLevel
	}
}