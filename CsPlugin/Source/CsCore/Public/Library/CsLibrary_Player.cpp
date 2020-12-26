// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Player.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Player
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
// Pawn
#include "GameFramework/Pawn.h"

#include "Engine/Engine.h"

namespace NCsLibraryPlayer
{
	namespace NCached
	{
		namespace Str
		{
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPlayerControllerChecked);
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPlayerStateChecked);
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPawnChecked);
		}
	}
}

// PlayerController
#pragma region

APlayerController* FCsLibrary_Player::GetFirstLocalPlayerController(UWorld* World)
{
	return GEngine->GetFirstLocalPlayerController(World);
}

APlayerController* FCsLibrary_Player::GetFirstLocalPlayerControllerChecked(const FString& Context, UObject* WorldContext)
{
	checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

	UWorld* World = WorldContext->GetWorld();

	checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

	return GetFirstLocalPlayerControllerChecked(Context, World);
}

APlayerController* FCsLibrary_Player::GetLocalPlayerController(const FString& Context, UWorld* World, const int32& ControllerId)
{
	checkf(World, TEXT("%s: World is NULL."), *Context);

	checkf(ControllerId > INDEX_NONE, TEXT("%s: ControllerId: %d is NOT Valid. ControllerId must be >= 0."), *Context, ControllerId);

	if (ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId))
		return Player->PlayerController;
	return nullptr;
}

APlayerController* FCsLibrary_Player::GetLocalPlayerControllerChecked(const FString& Context, UWorld* World, const int32& ControllerId)
{
	checkf(World, TEXT("%s: World is NULL."), *Context);

	checkf(ControllerId > INDEX_NONE, TEXT("%s: ControllerId: %d is NOT Valid. ControllerId must be >= 0."), *Context, ControllerId);

	ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId);

	checkf(Player, TEXT("%s: Failed to get Local Player with ControllerId: %d."), *Context, ControllerId);

	APlayerController* PC = Player->PlayerController;

	checkf(PC, TEXT("%s: Failed to get PlayerController from Local Player: %s with ControllerId: %d."), *Context, *(Player->GetName()), ControllerId);

	return PC;
}

APlayerController* FCsLibrary_Player::GetPlayerControllerOrFirstLocalChecked(const FString& Context, APawn* Pawn)
{
	checkf(Pawn, TEXT("%s: Pawn is NULL."));

	if (APlayerController* PC = Cast<APlayerController>(Pawn->Controller))
		return PC;
	return GetFirstLocalPlayerControllerChecked(Context, Pawn);
}

void FCsLibrary_Player::GetAllLocalPlayerControllersChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers)
{
	checkf(World, TEXT("%s: World is NULL."), *Context);

	for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Iterator->Get();

		if (PC && PC->GetLocalPlayer())
		{
			OutControllers.Add(PC);
		}
	}
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

// Cursor
#pragma region


void FCsLibrary_Player::ShowMouseCursorChecked(const FString& Context, UObject* WorldContext)
{
	APlayerController* PC = GetFirstLocalPlayerControllerChecked(Context, WorldContext);

	PC->bShowMouseCursor = true;
}

void FCsLibrary_Player::HideMouseCursorChecked(const FString& Context, UObject* WorldContext)
{
	APlayerController* PC = GetFirstLocalPlayerControllerChecked(Context, WorldContext);

	PC->bShowMouseCursor = false;
}

#pragma endregion Cursor