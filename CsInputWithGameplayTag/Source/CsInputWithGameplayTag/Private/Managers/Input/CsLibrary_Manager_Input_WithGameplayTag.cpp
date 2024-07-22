// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsLibrary_Manager_Input_WithGameplayTag.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Input/CsManager_Input_WithGameplayTag.h"
// Player
#include "GameFramework/PlayerController.h"
// Pawn
#include "GameFramework/Pawn.h"
// Input
#include "Managers/Input/CsGetManagerInputWithGameplayTag.h"

namespace NCsInput
{
	namespace NWithGameplayTag
	{
		namespace NManager
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NWithGameplayTag::NManager::FLibrary, GetSafe);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NWithGameplayTag::NManager::FLibrary, HaveAllBeenCreated);
					}
				}
			}

			#define USING_NS_CACHED using namespace NCsInput::NWithGameplayTag::NManager::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsInput::NWithGameplayTag::NManager::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName
			#define LogLevel void(*Log)(const FString&) /*=&NCsInput::NWithGameplayTag::FLog::Warning*/
			#define PCLocalLibrary NCsPlayer::NController::NLocal::FLibrary

			// Get
			#pragma region

			ICsManager_Input_WithGameplayTag* FLibrary::GetChecked(const FString& Context, APlayerController* PC)
			{
				CS_IS_PTR_NULL_CHECKED(PC)

				ICsGetManagerInputWithGameplayTag* GetManagerInput = CS_INTERFACE_CAST_CHECKED(PC, APlayerController, ICsGetManagerInputWithGameplayTag);
				ICsManager_Input_WithGameplayTag* Manager_Input    = GetManagerInput->GetManager_Input_WithGameplayTag();

				checkf(Manager_Input, TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));
				checkf(IsValid(Manager_Input->_getUObject()), TEXT("%s: Manager_Input from PlayerController: %s with Class: %s is NULL or Pending Kill."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));
				return Manager_Input;
			}

			ICsManager_Input_WithGameplayTag* FLibrary::GetSafe(const FString& Context, APlayerController* PC, LogLevel)
			{
				CS_IS_PTR_NULL_RET_NULL(PC)

				ICsGetManagerInputWithGameplayTag* GetManagerInput = CS_INTERFACE_CAST(PC, APlayerController, ICsGetManagerInputWithGameplayTag);

				if (!GetManagerInput)
					return nullptr;

				ICsManager_Input_WithGameplayTag* Manager_Input = GetManagerInput->GetManager_Input_WithGameplayTag();

				if (!Manager_Input)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
				}

				if (!IsValid(Manager_Input->_getUObject()))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Manager_Input from PlayerController: %s with Class: %s is NULL or Pending Kill."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
					return nullptr;
				}
				return Manager_Input;
			}

			ICsManager_Input_WithGameplayTag* FLibrary::GetSafe(const FString& Context, APlayerController* PC, bool& OutSuccess, LogLevel)
			{
				OutSuccess = false;

				CS_IS_PTR_NULL_RET_NULL(PC)

				ICsGetManagerInputWithGameplayTag* GetManagerInput = CS_INTERFACE_CAST(PC, APlayerController, ICsGetManagerInputWithGameplayTag);

				if (!GetManagerInput)
					return nullptr;

				ICsManager_Input_WithGameplayTag* Manager_Input = GetManagerInput->GetManager_Input_WithGameplayTag();

				if (!Manager_Input)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
					return nullptr;
				}

				if (!IsValid(Manager_Input->_getUObject()))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s:Manager_Input from PlayerController: %s with Class: %s is NULL or Pending Kill."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
					return nullptr;
				}
				OutSuccess = true;
				return Manager_Input;
			}

			ICsManager_Input_WithGameplayTag* FLibrary::GetSafe(APawn* Pawn)
			{
				SET_CONTEXT(GetSafe);

				if (!Pawn)
					return nullptr;

				if (APlayerController* PC = Cast<APlayerController>(Pawn->Controller))
					return GetSafe(Context, PC, nullptr);
				return nullptr;
			}

			ICsManager_Input_WithGameplayTag* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
			{
				return GetChecked(Context, PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId));
			}

			ICsManager_Input_WithGameplayTag* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
			{
				APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

				if (!PC)
					return nullptr;
				return GetSafe(Context, PC, Log);
			}

			ICsManager_Input_WithGameplayTag* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, LogLevel)
			{
				APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, OutSuccess, Log);

				if (!PC)
					return nullptr;
				return GetSafe(Context, PC, OutSuccess, Log);
			}

			UObject* FLibrary::GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
			{
			#if UE_BUILD_SHIPPING
				return GetChecked(Context, WorldContext, ControllerId)->_getUObject();
			#else
				UObject* Manager_Input = GetChecked(Context, WorldContext, ControllerId)->_getUObject();
				check(IsValid(Manager_Input));
				return Manager_Input;
			#endif // #if UE_BUILD_SHIPPING
			}

			UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
			{
				if (ICsManager_Input_WithGameplayTag* Manager_Input = GetSafe(Context, WorldContext, ControllerId, Log))
				{
					UObject* Manager_Input_Object = GetChecked(Context, WorldContext, ControllerId)->_getUObject();

					CS_IS_PENDING_KILL_RET_NULL(Manager_Input_Object)
					return Manager_Input_Object;
				}
				return nullptr;
			}

			#pragma endregion Get

			bool FLibrary::Exists(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
			{
				return GetSafe(Context, WorldContext, ControllerId, Log) != nullptr;
			}

			bool FLibrary::HaveAllBeenCreated(UObject* WorldContext, const int32& NumLocalPlayers)
			{
				SET_CONTEXT(HaveAllBeenCreated);

				CS_IS_INT_GREATER_THAN_CHECKED(NumLocalPlayers, 0)

				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAll(WorldContext, PlayerControllers);

				int32 Count = 0;

				for (APlayerController* PC : PlayerControllers)
				{
					ICsGetManagerInputWithGameplayTag* GetManagerInput = Cast<ICsGetManagerInputWithGameplayTag>(PC);

					if (!GetManagerInput)
						return false;

					ICsManager_Input_WithGameplayTag* Manager_Input = GetManagerInput->GetManager_Input_WithGameplayTag();

					if (!Manager_Input)
						return false;
					++Count;
				}
				return Count == NumLocalPlayers;
			}

			bool FLibrary::SafeInit(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel)
			{
				if (ICsManager_Input_WithGameplayTag* ManagerInput = GetSafe(Context, WorldContext, ControllerId, Log))
				{
					ManagerInput->Init();
					return true;
				}
				return false;
			}

			bool FLibrary::SafeInit(const FString& Context, const UObject* WorldContext, LogLevel)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAll(WorldContext, PlayerControllers);

				int32 Count = 0;

				for (APlayerController* PC : PlayerControllers)
				{
					ICsGetManagerInputWithGameplayTag* GetManagerInput = Cast<ICsGetManagerInputWithGameplayTag>(PC);

					if (!GetManagerInput)
						continue;

					ICsManager_Input_WithGameplayTag* Manager_Input = GetManagerInput->GetManager_Input_WithGameplayTag();

					if (!Manager_Input)
						continue;

					Manager_Input->Init();
					++Count;
				}
			
				if (Count == 0)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No PlayerControllers found that implement the interface: ICsGetManagerInputWithGameplayTag."), *Context));
					return false;
				}
				return Count > CS_EMPTY;
			}

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
			#undef LogLevel
			#undef PCLocalLibrary
		}
	}
}