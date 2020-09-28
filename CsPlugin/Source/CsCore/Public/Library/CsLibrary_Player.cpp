// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Player.h"
#include "CsCore.h"

// Player
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
// Pawn
#include "GameFramework/Pawn.h"

#include "Engine/Engine.h"

namespace NCsLibraryPlayerCached
{
	namespace Str
	{
		CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPlayerControllerChecked);
		CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPlayerStateChecked);
		CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPawnChecked);
	}
}

// PlayerController
#pragma region

APlayerController* FCsLibrary_Player::GetFirstLocalPlayerController(UWorld* World)
{
	return GEngine->GetFirstLocalPlayerController(World);
}

#pragma endregion PlayerController

// PlayerState
#pragma region

APlayerState* FCsLibrary_Player::GetFirstLocalPlayerState(UWorld* World)
{
	if (APlayerController* PC = GetFirstLocalPlayerController(World))
		return PC->PlayerState;
	return nullptr;
}

APlayerState* FCsLibrary_Player::GetFirstLocalPlayerStateChecked(const FString& Context, UWorld* World)
{
	APlayerController* PC = GetFirstLocalPlayerControllerChecked(Context, World);
	APlayerState* PS	  = PC->PlayerState;

	checkf(PS, TEXT("%s: Failed to get PlayerState from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

	return PS;
}

bool FCsLibrary_Player::IsFirstLocalPlayerState(UWorld* World, APlayerState* PlayerState)
{
	if (!PlayerState)
		return false;
	return PlayerState == GetFirstLocalPlayerState(World);
}

#pragma endregion PlayerState

// Pawn
#pragma region

APawn* FCsLibrary_Player::GetFirstLocalPawn(UWorld* World)
{
	if (APlayerController* PC = GetFirstLocalPlayerController(World))
		return PC->GetPawn();
	return nullptr;
}

APawn* FCsLibrary_Player::GetFirstLocalPawnChecked(const FString& Context, UWorld* World)
{
	APlayerController* PC = GetFirstLocalPlayerControllerChecked(Context, World);
	APawn* P			  = PC->GetPawn();

	checkf(P, TEXT("%s: Failed to get Pawn from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

	return P;
}

bool FCsLibrary_Player::IsFirstLocalPawn(UWorld* World, APawn* Pawn)
{
	if (!Pawn)
		return false;
	return Pawn == GetFirstLocalPawn(World);
}

#pragma endregion Pawn

UPlayerInput* FCsLibrary_Player::GetFirstLocalPlayerInput(UWorld* World)
{
	if (APlayerController* PC = GetFirstLocalPlayerController(World))
		return PC->PlayerInput;
	return nullptr;
}

AHUD* FCsLibrary_Player::GetFirstLocalHUD(UWorld* World)
{
	if (APlayerController* PC = GetFirstLocalPlayerController(World))
		return PC->MyHUD;
	return nullptr;
}