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
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, GetFirstLocalManagerInputChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, SetFirstLocalCurrentInputActionMapChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, ClearFirstLocalCurrentInputActionMapChecked);
			}
		}

		UCsManager_Input* FLibrary::GetFirstLocalManagerInput(UWorld* World)
		{
			if (APlayerController* PC = FCsLibrary_Player::GetFirstLocalPlayerController(World))
			{
				if (ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC))
				{
					return GetManagerInput->GetManager_Input();
				}
			}
			return nullptr;
		}

		UCsManager_Input* FLibrary::GetFirstLocalManagerInputChecked(const FString& Context, UWorld* World)
		{
			APlayerController* PC = FCsLibrary_Player::GetFirstLocalPlayerControllerChecked(Context, World);

			return GetManagerInputChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstLocalManagerInputChecked(const FString& Context, UObject* WorldContext)
		{
			APlayerController* PC = FCsLibrary_Player::GetFirstLocalPlayerControllerChecked(Context, WorldContext);

			return GetManagerInputChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstLocalManagerInputChecked(UWorld* World)
		{
			using namespace NCached;

			const FString& Context = Str::GetFirstLocalManagerInputChecked;

			return GetFirstLocalManagerInputChecked(Context, World);
		}

		UCsManager_Input* FLibrary::GetManagerInputChecked(const FString& Context, APlayerController* PC)
		{
			checkf(PC, TEXT("%s: PC is NULL"), *Context);

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			checkf(GetManagerInput, TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

			checkf(Manager_Input, TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			return Manager_Input;
		}

		bool FLibrary::HaveAllLocalManagerInputBeenCreated(UObject* WorldContext, const int32& NumLocalPlayers)
		{
			checkf(NumLocalPlayers > 0, TEXT("FLibrary::HaveAllLocalManagerInputBeenCreated: NumLocalPlayer: %d is NOT > 0."), NumLocalPlayers);

			TArray<APlayerController*> PlayerControllers;

			FCsLibrary_Player::GetAllLocalPlayerControllers(WorldContext, PlayerControllers);

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

		void FLibrary::SetFirstLocalCurrentInputActionMap(UWorld* World, const FECsInputActionMap& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirstLocalManagerInput(World))
			{
				Manager_Input->SetCurrentInputActionMap(Map);
			}
		}

		void FLibrary::SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, World);

			Manager_Input->SetCurrentInputActionMap(Context, Map);
		}

		void FLibrary::SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			SetFirstLocalCurrentInputActionMapChecked(Context, WorldContext->GetWorld(), Map);
		}

		void FLibrary::SetFirstLocalCurrentInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map)
		{
			using namespace NCached;

			const FString& Context = Str::SetFirstLocalCurrentInputActionMapChecked;

			SetFirstLocalCurrentInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::SetFirstLocalCurrentInputActionMap(UWorld* World, const int32& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirstLocalManagerInput(World))
			{
				Manager_Input->SetCurrentInputActionMap(Map);
			}
		}

		void FLibrary::SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, World);

			Manager_Input->SetCurrentInputActionMap(Context, Map);
		}

		void FLibrary::SetFirstLocalCurrentInputActionMapChecked(UWorld* World, const int32& Map)
		{
			using namespace NCached;

			const FString& Context = Str::SetFirstLocalCurrentInputActionMapChecked;

			SetFirstLocalCurrentInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::SetLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
		{
			TArray<APlayerController*> PlayerControllers;

			FCsLibrary_Player::GetAllLocalPlayerControllersChecked(Context, World, PlayerControllers);

			for (APlayerController* PC : PlayerControllers)
			{
				UCsManager_Input* Manager_Input = GetManagerInputChecked(Context, PC);

				Manager_Input->SetCurrentInputActionMap(Context, Map);
			}
		}

		void FLibrary::SetLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			SetLocalCurrentInputActionMapChecked(Context, WorldContext->GetWorld(), Map);
		}

		#pragma endregion Set

			// Clear
		#pragma region

		void FLibrary::ClearFirstLocalCurrentInputActionMap(UWorld* World, const FECsInputActionMap& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirstLocalManagerInput(World))
			{
				Manager_Input->ClearCurrentInputActionMap(Map);
			}
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, World);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, WorldContext);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map)
		{
			using namespace NCached;

			const FString& Context = Str::ClearFirstLocalCurrentInputActionMapChecked;

			ClearFirstLocalCurrentInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMap(UWorld* World, const int32& Map)
		{
			if (UCsManager_Input* Manager_Input = GetFirstLocalManagerInput(World))
			{
				Manager_Input->ClearCurrentInputActionMap(Map);
			}
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, World);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, WorldContext);

			Manager_Input->ClearCurrentInputActionMap(Context, Map);
		}

		void FLibrary::ClearFirstLocalCurrentInputActionMapChecked(UWorld* World, const int32& Map)
		{
			using namespace NCached;

			const FString& Context = Str::ClearFirstLocalCurrentInputActionMapChecked;

			ClearFirstLocalCurrentInputActionMapChecked(Context, World, Map);
		}

		void FLibrary::ClearLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map)
		{
			TArray<APlayerController*> PlayerControllers;

			FCsLibrary_Player::GetAllLocalPlayerControllersChecked(Context, World, PlayerControllers);

			for (APlayerController* PC : PlayerControllers)
			{
				UCsManager_Input* Manager_Input = GetManagerInputChecked(Context, PC);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}
		}

		void FLibrary::ClearLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			ClearLocalCurrentInputActionMapChecked(Context, WorldContext->GetWorld(), Map);
		}

		#pragma endregion Clear

			// Reset
		#pragma region

		void FLibrary::ResetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World)
		{
			UCsManager_Input* Manager_Input = GetFirstLocalManagerInputChecked(Context, World);

			Manager_Input->ResetCurrentInputActionMap();
		}

		void FLibrary::ResetFirstLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			ResetFirstLocalCurrentInputActionMapChecked(Context, WorldContext->GetWorld());
		}

		void FLibrary::ResetLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World)
		{
			TArray<APlayerController*> PlayerControllers;

			FCsLibrary_Player::GetAllLocalPlayerControllersChecked(Context, World, PlayerControllers);

			for (APlayerController* PC : PlayerControllers)
			{
				UCsManager_Input* Manager_Input = GetManagerInputChecked(Context, PC);

				Manager_Input->ResetCurrentInputActionMap();
			}
		}

		void FLibrary::ResetLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."));

			ResetLocalCurrentInputActionMapChecked(Context, WorldContext->GetWorld());
		}

		#pragma endregion Reset

		#pragma endregion InputActionMap
	}
}