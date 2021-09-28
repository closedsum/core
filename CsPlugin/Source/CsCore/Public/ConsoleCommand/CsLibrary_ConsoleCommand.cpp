// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
#include "ConsoleCommand/CsLibrary_ConsoleCommand.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Player.h"
// Player
#include "GameFramework/PlayerController.h"
// Engine
#include "Engine/Engine.h"

namespace NCsConsoleCommand
{
	namespace NLibrary
	{
		bool FLibrary::Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Out /*= *GLog*/)
		{
			checkf(World, TEXT("NCsConsoleCommand::FLibrary::Exec: World is NULL"));

			typedef NCsPlayer::NController::FLibrary PlayerLibrary;

			if (APlayerController* PC = PlayerLibrary::GetFirstLocal(World))
			{
				FString Output = PC->ConsoleCommand(Cmd);
				return !Output.IsEmpty();
			}
			else
			{
				return GEngine->Exec(World, Cmd, Out);
			}
			return false;
		}

		bool FLibrary::Exec(UObject* WorldContext, const FString& Cmd)
		{
			checkf(WorldContext, TEXT("NCsConsoleCommand::FLibrary::Exec: WorldContext is NULL."));

			UWorld* World = WorldContext->GetWorld();

			return Exec(World, *Cmd);
		}

		bool FLibrary::ConsumeNextCharAndCheckNotEmpty(const FString& Context, FString& Str, const FString& Definition)
		{
			// Remove next char (usually a blank space ' ')
			Str.RemoveAt(0);

			if (Str.IsEmpty())
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Command:"), *Context);
				UE_LOG(LogCs, Warning, TEXT("%s:"), *Definition);
				return false;
			}
			return true;
		}
	}
}