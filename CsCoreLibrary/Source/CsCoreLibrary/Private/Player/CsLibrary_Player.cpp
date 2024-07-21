// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Player/CsLibrary_Player.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
// Pawn
#include "GameFramework/Pawn.h"
// Game
#include "Engine/GameInstance.h"
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

	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define GameInstanceLibrary NCsGameInstance::FLibrary

	ULocalPlayer* FLibrary::GetFirstLocalChecked(const FString& Context, const UObject* WorldContext)
	{
		UGameInstance* GameInstance = GameInstanceLibrary::GetChecked(Context, WorldContext);
		ULocalPlayer* LocalPlayer   = GameInstance->GetFirstGamePlayer();

		checkf(LocalPlayer, TEXT("%s: Failed to get LocalPlayer from GameInstance: %s."), *Context, *(GameInstance->GetName()));

		return LocalPlayer;
	}

	ULocalPlayer* FLibrary::GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, LogLevel)
	{
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

		UGameInstance* GameInstance = GameInstanceLibrary::GetChecked(Context, WorldContext);
		ULocalPlayer* LocalPlayer   = GameInstance->GetLocalPlayerByIndex(Index);

		checkf(LocalPlayer, TEXT("%s: Failed to get LocalPlayer[%d] from GameInstance: %s."), *Context, Index, *(GameInstance->GetName()));

		return LocalPlayer;
	}

	ULocalPlayer* FLibrary::GetSafeLocal(const FString& Context, const UObject* WorldContext, const int32& Index, LogLevel)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_NULL(Index, 0)

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

	#undef LogLevel
	#undef GameInstanceLibrary

	namespace NLocal
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NLocal::FLibrary, GetSafeControllerId);
				}
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

		const ULocalPlayer* FLibrary::GetChecked(const FString& Context, const APawn* Pawn)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			const APlayerController* PC	    = PlayerControllerLibrary::GetChecked(Context, Pawn);
			const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();

			CS_IS_PENDING_KILL_CHECKED(LocalPlayer)
			return LocalPlayer;
		}

		int32 FLibrary::GetSafeControllerId(const FString& Context, const APawn* Pawn, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_VALUE(Pawn, INDEX_NONE)

			if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
			{
				if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC->Player))
				{
					return LocalPlayer->GetControllerId();
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No LocalPlayer for PlayerController: %s."), *Context, *CsObjectLibrary::PrintNameAndClass(Pawn)));
					return INDEX_NONE;
				}
			}
			else
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s->Controller: %s with Class: %s"), *Context, *(Pawn->GetName()), *CsObjectLibrary::PrintNameAndClass(Pawn->GetController())));
				return INDEX_NONE;
			}
		}

		#undef LogLevel

		namespace NFirst
		{
			#define GameInstanceLibrary NCsGameInstance::FLibrary

			const ULocalPlayer* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
			{
				UGameInstance* GameInstance		= GameInstanceLibrary::GetChecked(Context, WorldContext);
				const ULocalPlayer* LocalPlayer = GameInstance->GetFirstGamePlayer();

				CS_IS_PENDING_KILL_CHECKED(LocalPlayer)
				return LocalPlayer;
			}

			#undef GameInstanceLibrary
		}
	}

	namespace NController
	{
		namespace NLocal
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::NLocal::FLibrary, GetSafe);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::NLocal::FLibrary, GetAll);
					}
				}
			}

			#define USING_NS_CACHED using namespace NCsPlayer::NController::NLocal::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsPlayer::NController::NLocal::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName
			#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
			#define WorldLibrary NCsWorld::FLibrary

			APlayerController* FLibrary::Get(const FString& Context, UWorld* World, const int32& ControllerId)
			{
				CS_IS_PTR_NULL_CHECKED(World)

				checkf(ControllerId > INDEX_NONE, TEXT("%s: ControllerId: %d is NOT Valid. ControllerId must be >= 0."), *Context, ControllerId);

				if (ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId))
					return Player->PlayerController;
				return nullptr;
			}

			APlayerController* FLibrary::GetChecked(const FString& Context, UWorld* World, const int32& ControllerId)
			{
				CS_IS_PTR_NULL_CHECKED(World)

				checkf(ControllerId > INDEX_NONE, TEXT("%s: ControllerId: %d is NOT Valid. ControllerId must be >= 0."), *Context, ControllerId);

				ULocalPlayer* Player = GEngine->GetLocalPlayerFromControllerId(World, ControllerId);

				checkf(Player, TEXT("%s: Failed to get Local Player with ControllerId: %d."), *Context, ControllerId);

				APlayerController* PC = Player->PlayerController;

				checkf(PC, TEXT("%s: Failed to get PlayerController from Local Player: %s with ControllerId: %d."), *Context, *(Player->GetName()), ControllerId);
				return PC;
			}

			APlayerController* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
			{
				return GetChecked(Context, WorldLibrary::GetChecked(Context, WorldContext), ControllerId);
			}

			APlayerController* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
			{
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

			APlayerController* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, LogLevel)
			{
				OutSuccess = false;

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

				OutSuccess = true;
				return PC;
			}
		
			APlayerController* FLibrary::GetSafe(const UObject* WorldContext, const int32& ControllerId)
			{
				SET_CONTEXT(GetSafe);

				return GetSafe(Context, WorldContext, ControllerId, nullptr);
			}

			const APlayerController* FLibrary::GetChecked(const FString& Context, const APawn* Pawn)
			{
				CS_IS_PENDING_KILL_CHECKED(Pawn)

				const AController* Controller = Pawn->GetController();

				CS_IS_PENDING_KILL_CHECKED(Controller)
				return CS_CONST_CAST_CHECKED(Controller, AController, APlayerController);
			}

			void FLibrary::GetAll(UWorld* World, TArray<APlayerController*>& OutControllers)
			{
				SET_CONTEXT(GetAll);

				if (!World)
					return;
				GetAllChecked(Context, World, OutControllers);
			}

			void FLibrary::GetAll(const UObject* WorldContext, TArray<APlayerController*>& OutControllers)
			{
				if (!WorldContext)
					return;
				GetAll(WorldContext->GetWorld(), OutControllers);
			}

			void FLibrary::GetAllChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers)
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

			bool FLibrary::GetSafeAll(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers, LogLevel)
			{
				CS_IS_PTR_NULL(World)

				for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					APlayerController* PC = Iterator->Get();

					if (PC && PC->GetLocalPlayer())
					{
						OutControllers.Add(PC);
					}
				}
				return true;
			}

			void FLibrary::GetAllChecked(const FString& Context, const UObject* WorldContext, TArray<APlayerController*>& OutControllers)
			{
				GetAllChecked(Context, WorldLibrary::GetChecked(Context, WorldContext), OutControllers);
			}

			bool FLibrary::GetSafeAll(const FString& Context, const UObject* WorldContext, TArray<APlayerController*>& OutControllers, LogLevel)
			{
				if (UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log))
				{
					return GetSafeAll(Context, World, OutControllers, Log);
				}
				return false;
			}


			#undef USING_NS_CACHED
			#undef SET_CONTEXT
			#undef LogLevel
			#undef WorldLibrary

			namespace NFirst
			{
				namespace NLibrary
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::NLocal::NFirst::FLibrary, Get);
							CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::NLocal::NFirst::FLibrary, GetChecked);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::NLocal::NFirst::FLibrary, GetSafe);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::NLocal::NFirst::FLibrary, SafeIsPossessedBy);
						}
					}
				}

				#define USING_NS_CACHED using namespace NCsPlayer::NController::NLocal::NFirst::NLibrary::NCached;
				#define SET_CONTEXT(__FunctionName) using namespace NCsPlayer::NController::NLocal::NFirst::NLibrary::NCached; \
					const FString& Context = Str::__FunctionName
				#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
				#define WorldLibrary NCsWorld::FLibrary

				APlayerController* FLibrary::Get(const FString& Context, UWorld* World)
				{
					CS_IS_PTR_NULL_CHECKED(World)

					return GEngine->GetFirstLocalPlayerController(World);
				}

				APlayerController* FLibrary::Get(UWorld* World)
				{
					SET_CONTEXT(Get);

					return Get(Context, World);
				}

				APlayerController* FLibrary::GetChecked(const FString& Context, UWorld* World)
				{
					CS_IS_PTR_NULL_CHECKED(World)

					APlayerController* PC = GEngine->GetFirstLocalPlayerController(World);

					CS_IS_PTR_NULL_CHECKED(PC)
					return PC;
				}

				APlayerController* FLibrary::GetSafe(const FString& Context, UWorld* World, LogLevel)
				{
					CS_IS_PTR_NULL_RET_NULL(World)

					return GEngine->GetFirstLocalPlayerController(World);
				}

				APlayerController* FLibrary::GetSafe(UWorld* World)
				{
					SET_CONTEXT(GetSafe);

					return GetSafe(Context, World, nullptr);
				}

				APlayerController* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
				{
					return GetChecked(Context, WorldLibrary::GetChecked(Context, WorldContext));
				}

				APlayerController* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, LogLevel) 
				{
					return GetSafe(Context, WorldLibrary::GetSafe(Context, WorldContext), Log);
				}

				APlayerController* FLibrary::GetSafe(const UObject* WorldContext)
				{
					SET_CONTEXT(GetSafe);

					return GetSafe(Context, WorldContext, nullptr);
				}

				void FLibrary::PossessChecked(const FString& Context, APawn* Pawn)
				{
					GetChecked(Context, Pawn)->Possess(Pawn);
				}

				bool FLibrary::SafePossess(const FString& Context, APawn* Pawn, LogLevel)
				{
					if (APlayerController* PC = GetSafe(Context, Pawn, Log))
					{
						PC->Possess(Pawn);
						return true;
					}
					return false;
				}

				bool FLibrary::SafeIsPossessedBy(const FString& Context, const APawn* Pawn, LogLevel)
				{
					if (APlayerController* PC = GetSafe(Context, Pawn, Log))
					{
						return PC->GetPawn() == Pawn;
					}
					return false;
				}

				bool FLibrary::SafeIsPossessedBy(const APawn* Pawn)
				{
					SET_CONTEXT(SafeIsPossessedBy);

					return SafeIsPossessedBy(Context, Pawn, nullptr);
				}

				void FLibrary::EnableAutoManageViewTarget(const FString& Context, const UObject* WorldContext)
				{
					GetChecked(Context, WorldContext)->bAutoManageActiveCameraTarget = true;
				}

				void FLibrary::DisableAutoManageViewTarget(const FString& Context, const UObject* WorldContext)
				{
					GetChecked(Context, WorldContext)->bAutoManageActiveCameraTarget = false;
				}

				#undef USING_NS_CACHED
				#undef SET_CONTEXT
				#undef LogLevel
				#undef WorldLibrary
			}
		}

		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetSafeLocal);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NController::FLibrary, GetSafeId);
				}
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
		#define WorldLibrary NCsWorld::FLibrary

		APlayerController* FLibrary::GetOrFirstLocalChecked(const FString& Context, APawn* Pawn)
		{
			CS_IS_PTR_NULL_CHECKED(Pawn)

			if (APlayerController* PC = Cast<APlayerController>(Pawn->Controller))
				return PC;
			return NCsPlayer::NController::NLocal::NFirst::FLibrary::GetChecked(Context, Pawn);
		}

		APlayerController* FLibrary::GetChecked(const FString& Context, const UObject* PlayerContext)
		{
			const APawn* Pawn	    = CS_CONST_CAST_CHECKED(PlayerContext, UObject, APawn);
			AController* Controller = Pawn->GetController();
			APlayerController* PC   = CS_CAST_CHECKED(Controller, AController, APlayerController);

			return PC;
		}

		APlayerController* FLibrary::GetSafe(const FString& Context, const APawn* Pawn, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_NULL(Pawn)

			AController* Controller = Pawn->GetController();

			return CS_CAST(Controller, AController, APlayerController);
		}

		int32 FLibrary::GetSafeId(const FString& Context, const UObject* PlayerContext, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_VALUE(PlayerContext, INDEX_NONE)

			if (const APawn* Pawn = Cast<APawn>(PlayerContext))
			{
				if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
				{
					if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC->Player))
					{
						return LocalPlayer->GetControllerId();
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No LocalPlayer for PlayerController: %s."), *Context, *CsObjectLibrary::PrintNameAndClass(PlayerContext)));
						return INDEX_NONE;
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s->Controller: %s with Class: %s"), *Context, *(PlayerContext->GetName()), *CsObjectLibrary::PrintNameAndClass(Pawn->GetController())));
					return INDEX_NONE;
				}
			}
			if (const APlayerController* PC = Cast<APlayerController>(PlayerContext))
			{
				if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC->Player))
				{
					return LocalPlayer->GetControllerId();
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No LocalPlayer for PlayerController: %s."), *Context, *CsObjectLibrary::PrintNameAndClass(PlayerContext)));
					return INDEX_NONE;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerContext: %s with Class: %s is NOT of type APawn or APlayerController."), *Context, *CsObjectLibrary::PrintNameAndClass(PlayerContext)));
			return INDEX_NONE;
		}

		int32 FLibrary::GetSafeId(const UObject* PlayerContext)
		{
			using namespace NCsPlayer::NController::NLibrary::NCached;

			const FString& Context = Str::GetSafeId;

			return GetSafeId(Context, PlayerContext, nullptr);
		}

		APlayerCameraManager* FLibrary::GetCameraManagerChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			APlayerController* PC = NCsPlayer::NController::NLocal::FLibrary::GetChecked(Context, WorldContext, ControllerId);

			checkf(PC->PlayerCameraManager, TEXT("%s: Player Controller: %s has NO Player Camera Manager."), *Context, *(PC->GetName()));
			return PC->PlayerCameraManager;
		}

		#undef LogLevel
		#undef WorldLibrary
	}

	namespace NState
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NState::FLibrary, GetFirstLocalChecked);
			}
		}

		#define PCFirstLocalLibrary NCsPlayer::NController::NLocal::NFirst::FLibrary

		APlayerState* FLibrary::GetFirstLocal(UWorld* World)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::Get(World))
				return PC->PlayerState;
			return nullptr;
		}

		APlayerState* FLibrary::GetFirstLocalChecked(const FString& Context, UWorld* World)
		{
			APlayerController* PC = PCFirstLocalLibrary::GetChecked(Context, World);
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

		#undef PCFirstLocalLibrary
	}
	
	namespace NPawn
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::P::FLibrary, GetFirstLocalChecked);
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
		#define PlayerControllerLibrary NCsPlayer::NController::FLibrary
		#define PCFirstLocalLibrary NCsPlayer::NController::NLocal::NFirst::FLibrary

		APawn* FLibrary::GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::GetSafe(Context, WorldContext, Log))
			{
				APawn* Pawn = PC->GetPawn();

				if (!IsValid(Pawn))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Pawn associated with First Local Player Controller: %s."), *Context, *(PC->GetName())))
					return nullptr;
				}
				return Pawn;
			}
			return nullptr;
		}

		APawn* FLibrary::GetFirstLocal(UWorld* World)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::Get(World))
				return PC->GetPawn();
			return nullptr;
		}

		APawn* FLibrary::GetFirstLocalChecked(const FString& Context, UWorld* World)
		{
			APlayerController* PC = PCFirstLocalLibrary::GetChecked(Context, World);
			APawn* P			  = PC->GetPawn();

			checkf(P, TEXT("%s: Failed to get Pawn from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));
			return P;
		}

		bool FLibrary::IsSafeFirstLocal(const FString& Context, const UObject* WorldContext, const APawn* Pawn, LogLevel)
		{
			CS_IS_PENDING_KILL(Pawn)

			return Pawn == GetSafeFirstLocal(Context, WorldContext, Log);
		}

		bool FLibrary::IsFirstLocal(UWorld* World, const APawn* Pawn)
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

		bool FLibrary::SafeUnPossess(const FString& Context, APawn* Pawn, LogLevel)
		{
			if (APlayerController* PC = PlayerControllerLibrary::GetSafe(Context, Pawn, Log))
			{
				PC->UnPossess();
				return true;
			}
			return false;
		}

		#undef LogLevel
		#undef PlayerControllerLibrary
		#undef PCFirstLocalLibrary
	}

	namespace NInput
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
		#define PCLocalLibrary NCsPlayer::NController::NLocal::FLibrary
		#define PCFirstLocalLibrary NCsPlayer::NController::NLocal::NFirst::FLibrary

		UPlayerInput* FLibrary::GetFirstLocal(UWorld* World)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::Get(World))
				return PC->PlayerInput;
			return nullptr;
		}

		UPlayerInput* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			APlayerController* PC	  = PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);
			UPlayerInput* PlayerInput = PC->PlayerInput;

			CS_IS_PTR_NULL_CHECKED(PlayerInput)

			return PlayerInput;
		}

		UPlayerInput* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
		{
			if (APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log))
			{
				UPlayerInput* PlayerInput = PC->PlayerInput;

				CS_IS_PTR_NULL_RET_NULL(PlayerInput)

				return PlayerInput;
			}
			return nullptr;
		}

		bool FLibrary::CanGetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
		{
			if (APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log))
			{
				UPlayerInput* PlayerInput = PC->PlayerInput;

				CS_IS_PTR_NULL(PlayerInput)

				return true;
			}
			return false;
		}

		#undef LogLevel
		#undef PCLocalLibrary
		#undef PCFirstLocalLibrary
	}
	
	namespace NHud
	{
		AHUD* FLibrary::GetFirstLocal(UWorld* World)
		{
			typedef NCsPlayer::NController::NLocal::NFirst::FLibrary PCFirstLocalLibrary;

			if (APlayerController* PC = PCFirstLocalLibrary::Get(World))
				return PC->MyHUD;
			return nullptr;
		}
	}
}