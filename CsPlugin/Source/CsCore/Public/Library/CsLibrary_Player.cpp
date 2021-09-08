// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Player.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameInstance.h"
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
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::FLibrary, GetSafeFirstLocal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::FLibrary, GetSafeLocal);
			}
		}
	}

	ULocalPlayer* FLibrary::GetFirstLocalChecked(const FString& Context, const UObject* WorldContext)
	{
		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		UGameInstance* GameInstance = GameInstanceLibrary::GetChecked(Context, WorldContext);
		ULocalPlayer* LocalPlayer   = GameInstance->GetFirstGamePlayer();

		checkf(LocalPlayer, TEXT("%s: Failed to get LocalPlayer from GameInstance: %s."), *Context, *(GameInstance->GetName()));

		return LocalPlayer;
	}

	ULocalPlayer* FLibrary::GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		UGameInstance* GameInstance = GameInstanceLibrary::GetSafe(Context, WorldContext, Log);

		if (!GameInstance)
			return nullptr;

		ULocalPlayer* LocalPlayer = GameInstance->GetFirstGamePlayer();

		if (!LocalPlayer)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get LocalPlayer from GameInstance: %s."), *Context, *(GameInstance->GetName())));
		}
		return LocalPlayer;
	}

	ULocalPlayer* FLibrary::GetSafeFirstLocal(const UObject* WorldContext)
	{
		using namespace NCsPlayer::NLibrary::NCached;

		const FString& Context = Str::GetSafeFirstLocal;

		return GetSafeFirstLocal(Context, WorldContext, nullptr);
	}

	ULocalPlayer* FLibrary::GetLocalChecked(const FString& Context, const UObject* WorldContext, const int32& Index)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		UGameInstance* GameInstance = GameInstanceLibrary::GetChecked(Context, WorldContext);
		ULocalPlayer* LocalPlayer   = GameInstance->GetLocalPlayerByIndex(Index);

		checkf(LocalPlayer, TEXT("%s: Failed to get LocalPlayer[%d] from GameInstance: %s."), *Context, Index, *(GameInstance->GetName()));

		return LocalPlayer;
	}

	ULocalPlayer* FLibrary::GetSafeLocal(const FString& Context, const UObject* WorldContext, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_NULL(Index, 0)

		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		UGameInstance* GameInstance = GameInstanceLibrary::GetSafe(Context, WorldContext, Log);

		if (!GameInstance)
			return nullptr;

		ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(Index);

		if (!LocalPlayer)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get LocalPlayer[%d] from GameInstance: %s."), *Context, Index, *(GameInstance->GetName())));
		}
		return LocalPlayer;
	}

	ULocalPlayer* FLibrary::GetSafeLocal(const UObject* WorldContext, const int32& Index)
	{
		using namespace NCsPlayer::NLibrary::NCached;

		const FString& Context = Str::GetSafeLocal;

		return GetSafeLocal(Context, WorldContext, Index, nullptr);
	}

	namespace NController
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetFirstLocal);
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetFirstLocalChecked);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetSafeFirstLocal);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetSafeLocal);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetAllLocal);
				}
			}
		}

		APlayerController* FLibrary::GetFirstLocal(const FString& Context, UWorld* World)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			return GEngine->GetFirstLocalPlayerController(World);
		}

		APlayerController* FLibrary::GetFirstLocal(UWorld* World)
		{
			using namespace NCsPlayer::NController::NLibrary::NCached;

			const FString& Context = Str::GetFirstLocal;

			return GetFirstLocal(Context, World);
		}

		APlayerController* FLibrary::GetFirstLocalChecked(const FString& Context, UWorld* World)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			APlayerController* PC = GEngine->GetFirstLocalPlayerController(World);

			CS_IS_PTR_NULL_CHECKED(PC)

			return PC;
		}

		APlayerController* FLibrary::GetSafeFirstLocal(const FString& Context, UWorld* World, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(World)

			return GEngine->GetFirstLocalPlayerController(World);
		}

		APlayerController* FLibrary::GetSafeFirstLocal(UWorld* World)
		{
			using namespace NCsPlayer::NController::NLibrary::NCached;

			const FString& Context = Str::GetSafeFirstLocal;

			return GetSafeFirstLocal(Context, World, nullptr);
		}

		APlayerController* FLibrary::GetFirstLocalChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			return GetFirstLocalChecked(Context, World);
		}

		APlayerController* FLibrary::GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/) 
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

			return GetSafeFirstLocal(Context, World, Log);
		}

		APlayerController* FLibrary::GetSafeFirstLocal(const UObject* WorldContext)
		{
			using namespace NCsPlayer::NController::NLibrary::NCached;

			const FString& Context = Str::GetSafeFirstLocal;

			return GetSafeFirstLocal(Context, WorldContext, nullptr);
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

		APlayerController* FLibrary::GetLocalChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			return GetLocalChecked(Context, World, ControllerId);
		}

		APlayerController* FLibrary::GetSafeLocal(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_NULL(ControllerId, 0)

			ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId);

			if (!Player)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Local Player with ControllerId: %d."), *Context, ControllerId));
				return nullptr;
			}

			APlayerController* PC = Player->PlayerController;

			if (!PC)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get PlayerController from Local Player: %s with ControllerId: %d."), *Context, *(Player->GetName()), ControllerId));
			}
			return PC;
		}

		APlayerController* FLibrary::GetSafeLocal(const UObject* WorldContext, const int32& ControllerId)
		{
			using namespace NCsPlayer::NController::NLibrary::NCached;

			const FString& Context = Str::GetSafeLocal;

			return GetSafeLocal(Context, WorldContext, ControllerId, nullptr);
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
			using namespace NCsPlayer::NController::NLibrary::NCached;

			const FString& Context = Str::GetAllLocal;

			if (!World)
				return;

			GetAllLocalChecked(Context, World, OutControllers);
		}

		void FLibrary::GetAllLocal(const UObject* WorldContext, TArray<APlayerController*>& OutControllers)
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

		void FLibrary::GetAllLocalChecked(const FString& Context, const UObject* WorldContext, TArray<APlayerController*>& OutControllers)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

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

		UPlayerInput* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC	  = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);
			UPlayerInput* PlayerInput = PC->PlayerInput;

			CS_IS_PTR_NULL_CHECKED(PlayerInput)

			return PlayerInput;
		}

		UPlayerInput* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log))
			{
				UPlayerInput* PlayerInput = PC->PlayerInput;

				CS_IS_PTR_NULL_RET_NULL(PlayerInput)

				return PlayerInput;
			}
			return nullptr;
		}

		bool FLibrary::CanGetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log))
			{
				UPlayerInput* PlayerInput = PC->PlayerInput;

				CS_IS_PTR_NULL(PlayerInput)

				return true;
			}
			return false;
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