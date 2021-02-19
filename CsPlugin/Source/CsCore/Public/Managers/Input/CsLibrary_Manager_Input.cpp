// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsLibrary_Manager_Input.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Player.h"
// Managers
#include "Managers/Input/CsManager_Input.h"
// Player
#include "GameFramework/PlayerController.h"
// Pawn
#include "GameFramework/Pawn.h"
// Input
#include "Managers/Input/CsGetManagerInput.h"

namespace NCsInput
{
	namespace NManager
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, GetFirstChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, SetFirstInputActionMapChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, ClearFirstInputActionMapChecked);
			}
		}

		UCsManager_Input* FLibrary::GetFirst(UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(World))
			{
				if (ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC))
				{
					return GetManagerInput->GetManager_Input();
				}
			}
			return nullptr;
		}

		UCsManager_Input* FLibrary::GetFirstChecked(const FString& Context, UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, World);

			return GetChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			return GetChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstChecked(UWorld* World)
		{
			using namespace NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetFirstChecked(Context, World);
		}

		UCsManager_Input* FLibrary::GetChecked(const FString& Context, APlayerController* PC)
		{
			checkf(PC, TEXT("%s: PC is NULL"), *Context);

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			checkf(GetManagerInput, TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

			checkf(Manager_Input, TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			return Manager_Input;
		}

		UCsManager_Input* FLibrary::GetSafe(APawn* Pawn)
		{
			if (!Pawn)
				return nullptr;

			if (APlayerController* PC = Cast<APlayerController>(Pawn->Controller))
			{
				if (ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC))
				{
					return GetManagerInput->GetManager_Input();
				}
			}
			return nullptr;
		}

		bool FLibrary::HaveAllBeenCreated(UObject* WorldContext, const int32& NumLocalPlayers)
		{
			checkf(NumLocalPlayers > 0, TEXT("FLibrary::HaveAllBeenCreated: NumLocalPlayer: %d is NOT > 0."), NumLocalPlayers);

			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			TArray<APlayerController*> PlayerControllers;

			PlayerControllerLibrary::GetAllLocal(WorldContext, PlayerControllers);

			int32 Count = 0;

			for (APlayerController* PC : PlayerControllers)
			{
				ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

				if (!GetManagerInput)
					return false;

				UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

				if (!Manager_Input)
					return false;
				++Count;
			}
			return Count == NumLocalPlayers;
		}

		// InputActionMap
		#pragma region

			// Set
		#pragma region

		void FLibrary::SetFirstInputActionMap(UWorld* World, const FECsInputActionMap& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirst(World))
			{
				Manager_Input->SetCurrentInputActionMap(Map);
			}
		}

		void FLibrary::SetFirstInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, World);

			Manager_Input->SetCurrentInputActionMap(Context, Map);
		}

		void FLibrary::SetFirstInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			SetFirstInputActionMapChecked(Context, WorldContext->GetWorld(), Map);
		}

		void FLibrary::SetFirstInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map)
		{
			using namespace NCached;

			const FString& Context = Str::SetFirstInputActionMapChecked;

			SetFirstInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::SetFirstInputActionMap(UWorld* World, const int32& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirst(World))
			{
				Manager_Input->SetCurrentInputActionMap(Map);
			}
		}

		void FLibrary::SetFirstInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, World);

			Manager_Input->SetCurrentInputActionMap(Context, Map);
		}

		void FLibrary::SetFirstInputActionMapChecked(UWorld* World, const int32& Map)
		{
			using namespace NCached;

			const FString& Context = Str::SetFirstInputActionMapChecked;

			SetFirstInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::SetInputActionMapChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetChecked(Context, PC);

			Manager_Input->SetCurrentInputActionMap(Context, Map);
		}

		void FLibrary::SetInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			TArray<APlayerController*> PlayerControllers;

			PlayerControllerLibrary::GetAllLocalChecked(Context, World, PlayerControllers);

			for (APlayerController* PC : PlayerControllers)
			{
				SetInputActionMapChecked(Context, PC, Map);
			}
		}

		void FLibrary::SetInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			SetInputActionMapChecked(Context, WorldContext->GetWorld(), Map);
		}

		void FLibrary::SetInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

			SetInputActionMapChecked(Context, PC, Map);
		}

		#pragma endregion Set

			// Clear
		#pragma region

		void FLibrary::ClearFirstInputActionMap(UWorld* World, const FECsInputActionMap& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirst(World))
			{
				Manager_Input->ClearCurrentInputActionMap(Map);
			}
		}

		void FLibrary::ClearFirstInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, World);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, WorldContext);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map)
		{
			using namespace NCached;

			const FString& Context = Str::ClearFirstInputActionMapChecked;

			ClearFirstInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::ClearFirstInputActionMap(UWorld* World, const int32& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirst(World))
			{
				Manager_Input->ClearCurrentInputActionMap(Map);
			}
		}

		void FLibrary::ClearFirstInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, World);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, WorldContext);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstInputActionMapChecked(UWorld* World, const int32& Map)
		{
			using namespace NCached;

			const FString& Context = Str::ClearFirstInputActionMapChecked;

			ClearFirstInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::ClearInputActionMapChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetChecked(Context, PC);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			TArray<APlayerController*> PlayerControllers;

			PlayerControllerLibrary::GetAllLocalChecked(Context, World, PlayerControllers);

			for (APlayerController* PC : PlayerControllers)
			{
				UCsManager_Input* Manager_Input = GetChecked(Context, PC);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}
		}

		void FLibrary::ClearInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			ClearInputActionMapChecked(Context, WorldContext->GetWorld(), Map);
		}

		void FLibrary::ClearInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, const int32& Map)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

			ClearInputActionMapChecked(Context, PC, Map);
		}

		#pragma endregion Clear

			// Reset
		#pragma region

		void FLibrary::ResetFirstInputActionMapChecked(const FString& Context, UWorld* World)
		{
			UCsManager_Input* Manager_Input = GetFirstChecked(Context, World);

			Manager_Input->ResetCurrentInputActionMap();
		}

		void FLibrary::ResetFirstInputActionMapChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			ResetFirstInputActionMapChecked(Context, WorldContext->GetWorld());
		}

		void FLibrary::ResetInputActionMapChecked(const FString& Context, APlayerController* PC)
		{
			UCsManager_Input* Manager_Input = GetChecked(Context, PC);

			Manager_Input->ResetCurrentInputActionMap();
		}

		void FLibrary::ResetInputActionMapChecked(const FString& Context, UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			TArray<APlayerController*> PlayerControllers;

			PlayerControllerLibrary::GetAllLocalChecked(Context, World, PlayerControllers);

			for (APlayerController* PC : PlayerControllers)
			{
				UCsManager_Input* Manager_Input = GetChecked(Context, PC);

				Manager_Input->ResetCurrentInputActionMap();
			}
		}

		void FLibrary::ResetInputActionMapChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			ResetInputActionMapChecked(Context, WorldContext->GetWorld());
		}

		void FLibrary::ResetInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

			ResetInputActionMapChecked(Context, PC);
		}

		#pragma endregion Reset

		#pragma endregion InputActionMap
	}
}