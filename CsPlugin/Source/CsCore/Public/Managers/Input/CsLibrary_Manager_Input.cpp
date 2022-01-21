// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsLibrary_Manager_Input.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
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
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, GetFirstChecked);
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, GetSafeFirst);
				}
			}
		}

		// Get
		#pragma region

		UCsManager_Input* FLibrary::GetFirstChecked(const FString& Context, UWorld* World)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, World);

			return GetChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetFirstChecked(UWorld* World)
		{
			using namespace NCsInput::NManager::NLibrary::NCached;

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
			using namespace NCsInput::NManager::NLibrary::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetFirstChecked(Context, WorldContext);
		}

		UCsManager_Input* FLibrary::GetSafeFirst(const FString& Context, UWorld* World, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetSafeFirstLocal(Context, World, Log))
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
			using namespace NCsInput::NManager::NLibrary::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetSafeFirst(Context, World, nullptr);
		}

		UCsManager_Input* FLibrary::GetSafeFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			if (APlayerController* PC = PlayerControllerLibrary::GetSafeFirstLocal(Context, WorldContext, Log))
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
			using namespace NCsInput::NManager::NLibrary::NCached;

			const FString& Context = Str::GetFirstChecked;

			return GetSafeFirst(Context, WorldContext, nullptr);
		}

		UCsManager_Input* FLibrary::GetChecked(const FString& Context, APlayerController* PC)
		{
			CS_IS_PTR_NULL_CHECKED(PC)

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			checkf(GetManagerInput, TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

			checkf(Manager_Input, TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			return Manager_Input;
		}

		UCsManager_Input* FLibrary::GetSafe(const FString& Context, APlayerController* PC, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(PC)

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			if (!GetManagerInput)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
				return nullptr;
			}

			UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

			if (!Manager_Input)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
			}
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

		UCsManager_Input* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			typedef NCsPlayer::NController::FLibrary PlayerLibrary;

			APlayerController* PC = PlayerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

			return GetChecked(Context, PC);
		}

		UCsManager_Input* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerLibrary;

			APlayerController* PC = PlayerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log);

			if (!PC)
				return nullptr;

			return GetSafe(Context, PC, Log);
		}

		#pragma endregion Get

		bool FLibrary::Exists(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return GetSafe(Context, WorldContext, ControllerId, Log) != nullptr;
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

		bool FLibrary::SafeInit(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Input* ManagerInput = GetSafe(Context, WorldContext, ControllerId, Log))
			{
				ManagerInput->Init();
				return true;
			}
			return false;
		}

		bool FLibrary::SafeInit(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			TArray<APlayerController*> PlayerControllers;

			PlayerControllerLibrary::GetAllLocal(WorldContext, PlayerControllers);

			int32 Count = 0;

			for (APlayerController* PC : PlayerControllers)
			{
				ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

				if (!GetManagerInput)
					continue;

				UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

				if (!Manager_Input)
					continue;

				Manager_Input->Init();
				++Count;
			}
			
			if (Count == 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No PlayerControllers found that implement the interface: ICsGetManagerInput."), *Context));
			}
			return Count > CS_EMPTY;
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
						CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::NInputActionMap::FLibrary, SafeClearFirst);
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

			void FLibrary::SetSafeFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, WorldContext, Log))
				{
					Manager_Input->SetCurrentInputActionMap(Map);
				}
			}

			void FLibrary::SetSafeFirst(const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::SetSafeFirst;

				SetSafeFirst(Context, WorldContext, Map, nullptr);
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
				CS_IS_INT_GREATER_THAN_EXIT(Map, 0)

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

			void FLibrary::SetSafe(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafe(Context, PC, Log);

				if (!Manager_Input)
					return;

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

			void FLibrary::SetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log);

				SetSafe(Context, PC, Map);
			}

			#pragma endregion Set

			// Clear
			#pragma region

				// First
			#pragma region

			void FLibrary::ClearFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(UWorld* World, const FECsInputActionMap& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::ClearFirstChecked;

				ClearFirstChecked(Context, World, Map);
			}

			void FLibrary::SafeClearFirst(const FString& Context, UWorld* World, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(World))
				{
					Manager_Input->ClearCurrentInputActionMap(Map);
				}
			}

			void FLibrary::SafeClearFirst(UWorld* World, const FECsInputActionMap& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::SafeClearFirst;

				SafeClearFirst(Context, World, Map, nullptr);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, WorldContext);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}
			
			void FLibrary::SafeClearFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, WorldContext, Log);

				if (!Manager_Input)
					return;

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, World);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(UWorld* World, const int32& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::ClearFirstChecked;

				ClearFirstChecked(Context, World, Map);
			}

			void FLibrary::SafeClearFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_INT_GREATER_THAN_EXIT(Map, 0)

				if (UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, World, Log))
				{
					Manager_Input->ClearCurrentInputActionMap(Map);
				}
			}

			void FLibrary::SafeClearFirst(UWorld* World, const int32& Map)
			{
				using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;

				const FString& Context = Str::SafeClearFirst;

				SafeClearFirst(Context, World, Map, nullptr);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, const UObject* WorldContext, const int32& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetFirstChecked(Context, WorldContext);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			#pragma endregion First

			void FLibrary::ClearChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SafeClear(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafe(Context, PC, Log);

				if (!Manager_Input)
					return;

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

				ClearChecked(Context, PC, Map);
			}

			void FLibrary::SafeClear(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log);

				SafeClear(Context, PC, Map, Log);
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

			void FLibrary::SafeResetFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafeFirst(Context, WorldContext, Log);

				if (!Manager_Input)
					return;

				Manager_Input->ResetCurrentInputActionMap();
			}

			void FLibrary::ResetChecked(const FString& Context, APlayerController* PC)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetChecked(Context, PC);

				Manager_Input->ResetCurrentInputActionMap();
			}

			void FLibrary::SafeReset(const FString& Context, APlayerController* PC, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				UCsManager_Input* Manager_Input = NCsInput::NManager::FLibrary::GetSafe(Context, PC, Log);

				if (!Manager_Input)
					return;

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

			void FLibrary::SafeReset(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log);

				SafeReset(Context, PC, Log);
			}

			#pragma endregion Reset
		}

		namespace NProfile
		{
			void FLibrary::ResetToDefaultChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FCsInputActionMappings& Mappings, const ECsInputDevice& Device)
			{
				UCsManager_Input* Manager_Input			   = NCsInput::NManager::FLibrary::GetChecked(Context, WorldContext, ControllerId);
				const FCsInputProfile& DefaultInputProfile = Manager_Input->GetDefaultInputProfile();

				check(EMCsInputDevice::Get().IsValidEnumChecked(Context, Device));

				const FCsInputActionMappings& DefaultMappings = DefaultInputProfile.GetMappings(Device);

				Mappings.ConditionalCopyMappingsByActionChecked(Context, DefaultMappings);
			}

			void FLibrary::ResetToDefaultChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, TArray<FCsInputActionMappings>& Mappings)
			{
				UCsManager_Input* Manager_Input			   = NCsInput::NManager::FLibrary::GetChecked(Context, WorldContext, ControllerId);
				const FCsInputProfile& DefaultInputProfile = Manager_Input->GetDefaultInputProfile();

				CS_IS_ARRAY_EMPTY_CHECKED(Mappings, FCsInputActionMappings)

				const int32 Count = Mappings.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const FCsInputActionMappings& DefaultMappings = DefaultInputProfile.GetMappings((ECsInputDevice)I);

					Mappings[I].ConditionalCopyMappingsByActionChecked(Context, DefaultMappings);
				}
			}
		}
	}
}