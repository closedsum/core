// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Player.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Player
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
// Pawn
#include "GameFramework/Pawn.h"
// Game
#include "Engine/GameInstance.h"
// Engine
#include "Engine/Engine.h"

namespace NCsPlayer
{
	ULocalPlayer* FLibrary::GetFirstLocalChecked(const FString& Context, UObject* WorldContext)
	{
		CS_IS_PTR_NULL_CHECKED(WorldContext)

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		UGameInstance* GameInstance = World->GetGameInstance();

		checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

		ULocalPlayer* LocalPlayer = GameInstance->GetFirstGamePlayer();

		checkf(LocalPlayer, TEXT("%s: Failed to get LocalPlayer from GameInstance: %s."), *Context, *(GameInstance->GetName()));

		return LocalPlayer;
	}

	namespace NController
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetFirstLocalChecked);

				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetAllLocal);
			}
		}

		APlayerController* FLibrary::GetFirstLocal(UWorld* World)
		{
			return GEngine->GetFirstLocalPlayerController(World);
		}

		APlayerController* FLibrary::GetFirstLocalChecked(const FString& Context, UObject* WorldContext)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			return GetFirstLocalChecked(Context, World);
		}

		APlayerController* FLibrary::GetLocal(const FString& Context, UWorld* World, const int32& ControllerId)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			checkf(ControllerId > INDEX_NONE, TEXT("%s: ControllerId: %d is NOT Valid. ControllerId must be >= 0."), *Context, ControllerId);

			if (ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId))
				return Player->PlayerController;
			return nullptr;
		}

		APlayerController* FLibrary::GetLocalChecked(const FString& Context, UWorld* World, const int32& ControllerId)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			checkf(ControllerId > INDEX_NONE, TEXT("%s: ControllerId: %d is NOT Valid. ControllerId must be >= 0."), *Context, ControllerId);

			ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId);

			checkf(Player, TEXT("%s: Failed to get Local Player with ControllerId: %d."), *Context, ControllerId);

			APlayerController* PC = Player->PlayerController;

			checkf(PC, TEXT("%s: Failed to get PlayerController from Local Player: %s with ControllerId: %d."), *Context, *(Player->GetName()), ControllerId);

			return PC;
		}

		APlayerController* FLibrary::GetLocalChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			return GetLocalChecked(Context, World, ControllerId);
		}

		APlayerController* FLibrary::GetOrFirstLocalChecked(const FString& Context, APawn* Pawn)
		{
			CS_IS_PTR_NULL_CHECKED(Pawn)

			if (APlayerController* PC = Cast<APlayerController>(Pawn->Controller))
				return PC;
			return GetFirstLocalChecked(Context, Pawn);
		}

		void FLibrary::GetAllLocal(UWorld* World, TArray<APlayerController*>& OutControllers)
		{
			using namespace NCsPlayer::NController::NCached;

			const FString& Context = Str::GetAllLocal;

			if (!World)
				return;

			GetAllLocalChecked(Context, World, OutControllers);
		}

		void FLibrary::GetAllLocal(UObject* WorldContext, TArray<APlayerController*>& OutControllers)
		{
			if (!WorldContext)
				return;

			GetAllLocal(WorldContext->GetWorld(), OutControllers);
		}

		void FLibrary::GetAllLocalChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				APlayerController* PC = Iterator->Get();

				if (PC && PC->GetLocalPlayer())
				{
					OutControllers.Add(PC);
				}
			}
		}

		void FLibrary::GetAllLocalChecked(const FString& Context, UObject* WorldContext, TArray<APlayerController*>& OutControllers)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			GetAllLocalChecked(Context, WorldContext->GetWorld(), OutControllers);
		}
	}

	namespace NState
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NState::FLibrary, GetFirstLocalChecked);
			}
		}

		APlayerState* FLibrary::GetFirstLocal(UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(World))
				return PC->PlayerState;
			return nullptr;
		}

		APlayerState* FLibrary::GetFirstLocalChecked(const FString& Context, UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, World);
			APlayerState* PS	  = PC->PlayerState;

			checkf(PS, TEXT("%s: Failed to get PlayerState from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			return PS;
		}

		bool FLibrary::IsFirstLocal(UWorld* World, APlayerState* PlayerState)
		{
			if (!PlayerState)
				return false;
			return PlayerState == GetFirstLocal(World);
		}
	}
	
	namespace NPawn
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::P::FLibrary, GetFirstLocalChecked);
			}
		}

		APawn* FLibrary::GetFirstLocal(UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(World))
				return PC->GetPawn();
			return nullptr;
		}

		APawn* FLibrary::GetFirstLocalChecked(const FString& Context, UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, World);
			APawn* P			  = PC->GetPawn();

			checkf(P, TEXT("%s: Failed to get Pawn from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			return P;
		}

		bool FLibrary::IsFirstLocal(UWorld* World, APawn* Pawn)
		{
			if (!Pawn)
				return false;
			return Pawn == GetFirstLocal(World);
		}

		bool FLibrary::IsHuman(APawn* Pawn)
		{
			if (!Pawn)
				return false;
			if (APlayerController* PC = Pawn->GetController<APlayerController>())
				return true;
			return false;
		}
	}

	namespace NInput
	{
		UPlayerInput* FLibrary::GetFirstLocal(UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(World))
				return PC->PlayerInput;
			return nullptr;
		}
	}
	
	namespace NHud
	{
		AHUD* FLibrary::GetFirstLocal(UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(World))
				return PC->MyHUD;
			return nullptr;
		}
	}
}