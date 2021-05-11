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
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, GetSafeFirst);
			}
		}

		UCsManager_Input* FLibrary::GetFirstChecked(const FString& Context, UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, World);

			return GetChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstChecked(UWorld* World)
		{
			using namespace NCsInput::NManager::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetFirstChecked(Context, World);
		}

		UCsManager_Input* FLibrary::GetFirstChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			return GetChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstChecked(const UObject* WorldContext)
		{
			using namespace NCsInput::NManager::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetFirstChecked(Context, WorldContext);
		}

		UCsManager_Input* FLibrary::GetSafeFirst(const FString& Context, UWorld* World, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(Context, World, Log))
			{
				if (ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC))
				{
					return GetManagerInput->GetManager_Input();
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetInterfaceMap."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
				}
			}
			return nullptr;
		}

		UCsManager_Input* FLibrary::GetSafeFirst(UWorld* World)
		{
			using namespace NCsInput::NManager::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetSafeFirst(Context, World, nullptr);
		}

		UCsManager_Input* FLibrary::GetSafeFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetFirstLocal(Context, WorldContext, Log))
			{
				if (ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC))
				{
					return GetManagerInput->GetManager_Input();
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetInterfaceMap."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
				}
			}
			return nullptr;
		}

		UCsManager_Input* FLibrary::GetSafeFirst(const UObject* WorldContext)
		{
			using namespace NCsInput::NManager::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetSafeFirst(Context, WorldContext, nullptr);
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

		namespace NInputActionMap
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::NInputActionMap::FLibrary, SetFirstChecked);
						CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::NInputActionMap::FLibrary, SetSafeFirst);
						CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::NInputActionMap::FLibrary, ClearFirstChecked);
					}
				}
			}

			// Set
			#pragma region

					// First
			#pragma region

			void FLibrary::SetFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->SetCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SetFirstChecked(UWorld* World, const FECsInputActionMap& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::SetFirstChecked;

				SetFirstChecked(Context, World, Map);
			}

			void FLibrary::SetFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, WorldContext);

				Manager_Input->SetCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SetSafeFirst(const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::SetSafeFirst;

				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, WorldContext, nullptr))
				{
					Manager_Input->SetCurrentInputActionMap(Map);
				}
			}

			void FLibrary::SetSafeFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, WorldContext, Log))
				{
					Manager_Input->SetCurrentInputActionMap(Map);
				}
			}

			void FLibrary::SetFirstChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->SetCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SetFirstChecked(UWorld* World, const int32& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::SetFirstChecked;

				SetFirstChecked(Context, World, Map);
			}

			void FLibrary::SetSafeFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, World, Log))
				{
					Manager_Input->SetCurrentInputActionMap(Map);
				}
			}

			#pragma endregion First

			void FLibrary::SetChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

				Manager_Input->SetCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SetChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				TArray<APlayerController*> PlayerControllers;

				PlayerControllerLibrary::GetAllLocalChecked(Context, World, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					SetChecked(Context, PC, Map);
				}
			}

			void FLibrary::SetChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				TArray<APlayerController*> PlayerControllers;

				PlayerControllerLibrary::GetAllLocalChecked(Context, WorldContext, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					SetChecked(Context, PC, Map);
				}
			}

			void FLibrary::SetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

				SetChecked(Context, PC, Map);
			}

			#pragma endregion Set

				// Clear
			#pragma region

			void FLibrary::ClearFirst(UWorld* World, const FECsInputActionMap& Map)
			{
				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(World))
				{
					Manager_Input->ClearCurrentInputActionMap(Map);
				}
			}

			void FLibrary::ClearFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, WorldContext);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(UWorld* World, const FECsInputActionMap& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::ClearFirstChecked;

				ClearFirstChecked(Context, World, Map);
			}

			void FLibrary::ClearFirst(UWorld* World, const int32& Map)
			{
				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(World))
				{
					Manager_Input->ClearCurrentInputActionMap(Map);
				}
			}

			void FLibrary::ClearFirstChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, const UObject* WorldContext, const int32& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, WorldContext);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(UWorld* World, const int32& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::ClearFirstChecked;

				ClearFirstChecked(Context, World, Map);
			}

			void FLibrary::ClearChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				TArray<APlayerController*> PlayerControllers;

				PlayerControllerLibrary::GetAllLocalChecked(Context, World, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

					Manager_Input->ClearCurrentInputActionMap(Context, Map);
				}
			}

			void FLibrary::ClearChecked(const FString& Context, const UObject* WorldContext, const int32& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				TArray<APlayerController*> PlayerControllers;

				PlayerControllerLibrary::GetAllLocalChecked(Context, WorldContext, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

					Manager_Input->ClearCurrentInputActionMap(Context, Map);
				}
			}

			void FLibrary::ClearChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const int32& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

				ClearChecked(Context, PC, Map);
			}

			#pragma endregion Clear

				// Reset
			#pragma region

			void FLibrary::ResetFirstChecked(const FString& Context, UWorld* World)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->ResetCurrentInputActionMap();
			}

			void FLibrary::ResetFirstChecked(const FString& Context, const UObject* WorldContext)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, WorldContext);

				Manager_Input->ResetCurrentInputActionMap();
			}

			void FLibrary::ResetChecked(const FString& Context, APlayerController* PC)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

				Manager_Input->ResetCurrentInputActionMap();
			}

			void FLibrary::ResetChecked(const FString& Context, UWorld* World)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				TArray<APlayerController*> PlayerControllers;

				PlayerControllerLibrary::GetAllLocalChecked(Context, World, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

					Manager_Input->ResetCurrentInputActionMap();
				}
			}

			void FLibrary::ResetChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				TArray<APlayerController*> PlayerControllers;

				PlayerControllerLibrary::GetAllLocalChecked(Context, WorldContext, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

					Manager_Input->ResetCurrentInputActionMap();
				}
			}

			void FLibrary::ResetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

				ResetChecked(Context, PC);
			}

			#pragma endregion Reset
		}
	}
}