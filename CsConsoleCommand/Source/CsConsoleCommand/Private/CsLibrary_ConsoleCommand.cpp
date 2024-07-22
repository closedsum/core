// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_ConsoleCommand.h"
#include "CsConsoleCommand.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Player/CsLibrary_Player.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsConsoleCommand
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsConsoleCommand::FLibrary, Exec);
			}
		}

		#define USING_NS_CACHED using namespace NCsConsoleCommand::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsConsoleCommand::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define WorldLibrary NCsWorld::FLibrary
		#define GameInstanceLibrary NCsGameInstance::FLibrary

		bool FLibrary::Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Out /*= *GLog*/)
		{
			SET_CONTEXT(Exec);

			CS_IS_PENDING_KILL_CHECKED(World)

			if (APlayerController* PC = CsPCFirstLocalLibrary::Get(World))
			{
				FString Output = PC->ConsoleCommand(Cmd);
				return !Output.IsEmpty();
			}
			else
			{
				return GameInstanceLibrary::GetChecked(Context, World)->Exec(World, Cmd, Out);
			}
		}

		bool FLibrary::Exec(UObject* WorldContext, const FString& Cmd)
		{
			SET_CONTEXT(Exec);

			return Exec(WorldLibrary::GetChecked(Context, WorldContext), *Cmd);
		}

		bool FLibrary::ConsumeNextCharAndCheckNotEmpty(const FString& Context, FString& Str, const FString& Definition)
		{
			// Remove next char (usually a blank space ' ')
			Str.RemoveAt(0);

			if (Str.IsEmpty())
			{
				UE_LOG(LogCsConsoleCommand, Warning, TEXT("%s: Command:"), *Context);
				UE_LOG(LogCsConsoleCommand, Warning, TEXT("%s:"), *Definition);
				return false;
			}
			return true;
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef WorldLibrary
		#undef GameInstanceLibrary
	}
}