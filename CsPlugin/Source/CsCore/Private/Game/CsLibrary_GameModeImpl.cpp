// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameModeImpl.h"

// Library
#include "Game/CsLibrary_GameMode.h"
#include "Library/CsLibrary_Valid.h"
// World
#include "GameFramework/GameModeBase.h"

namespace NCsGameMode
{
	namespace NImpl
	{
		FString FLibrary::PrintGameModeAndClass(AGameModeBase* GameMode)
		{
			return FString::Printf(TEXT("GameMode: %s with Class: %s"), *(GameMode->GetName()), *(GameMode->GetClass()->GetName()));
		}

		// ICsGameMode_Event
		#pragma region

		#define OnPostSeamlessTravelCompleteEventType NCsGameMode::NSeamlessTravel::NPost::FOnComplete

		OnPostSeamlessTravelCompleteEventType& FLibrary::GetPostSeamlessTravel_OnComplete_EventChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameModeBase* GameMode		 = CsGameModeLibrary::GetChecked(Context, WorldContext);
			ICsGameMode_Event* Interface = CS_INTERFACE_CAST_CHECKED(GameMode, AGameModeBase, ICsGameMode_Event);

			return Interface->GetPostSeamlessTravel_OnComplete_Event();
		}

		#undef OnPostSeamlessTravelCompleteEventType

		#pragma endregion ICsGameMode_Event
	}
}