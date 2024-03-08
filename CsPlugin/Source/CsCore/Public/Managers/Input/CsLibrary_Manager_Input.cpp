// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsLibrary_Manager_Input.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Input/CsManager_Input.h"
// Player
#include "GameFramework/PlayerController.h"
// Pawn
#include "GameFramework/Pawn.h"
// Input
#include "Managers/Input/CsGetManagerInput.h"
#include "Managers/Input/Event/CsManager_Input_Event.h"

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
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NManager::FLibrary, GetSafe);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsInput::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsInput::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define PCLocalLibrary NCsPlayer::NController::NLocal::FLibrary
		#define PCFirstLocalLibrary NCsPlayer::NController::NLocal::NFirst::FLibrary

		// Get
		#pragma region

		ICsManager_Input* FLibrary::GetFirstChecked(const FString& Context, UWorld* World)
		{
			return GetChecked(Context, PCFirstLocalLibrary::GetChecked(Context, World));
		}

		ICsManager_Input* FLibrary::GetFirstChecked(UWorld* World)
		{
			SET_CONTEXT(GetFirstChecked);

			return GetFirstChecked(Context, World);
		}

		ICsManager_Input* FLibrary::GetFirstChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, PCFirstLocalLibrary::GetChecked(Context, WorldContext));
		}

		ICsManager_Input* FLibrary::GetFirstChecked(const UObject* WorldContext)
		{
			SET_CONTEXT(GetFirstChecked);

			return GetFirstChecked(Context, WorldContext);
		}

		ICsManager_Input* FLibrary::GetSafeFirst(const FString& Context, UWorld* World, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::GetSafe(Context, World, Log))
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

		ICsManager_Input* FLibrary::GetSafeFirst(UWorld* World)
		{
			SET_CONTEXT(GetFirstChecked);

			return GetSafeFirst(Context, World, nullptr);
		}

		ICsManager_Input* FLibrary::GetSafeFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::GetSafe(Context, WorldContext, Log))
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

		ICsManager_Input* FLibrary::GetSafeFirst(const UObject* WorldContext)
		{
			SET_CONTEXT(GetFirstChecked);

			return GetSafeFirst(Context, WorldContext, nullptr);
		}

		ICsManager_Input* FLibrary::GetChecked(const FString& Context, APlayerController* PC)
		{
			CS_IS_PTR_NULL_CHECKED(PC)

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			checkf(GetManagerInput, TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));

			ICsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

			checkf(Manager_Input, TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName()));
			return Manager_Input;
		}

		ICsManager_Input* FLibrary::GetSafe(const FString& Context, APlayerController* PC, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(PC)

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			if (!GetManagerInput)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
				return nullptr;
			}

			ICsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

			if (!Manager_Input)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Input from PlayerController: %s with Class: %s."), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
			}
			return Manager_Input;
		}

		ICsManager_Input* FLibrary::GetSafe(const FString& Context, APlayerController* PC, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutSuccess = false;

			CS_IS_PTR_NULL_RET_NULL(PC)

			ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

			if (!GetManagerInput)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerController: %s with Class: %s does NOT implement interface: ICsGetManagerInput"), *Context, *(PC->GetName()), *(PC->GetClass()->GetName())));
				return nullptr;
			}

			ICsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

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

		ICsManager_Input* FLibrary::GetSafe(APawn* Pawn)
		{
			SET_CONTEXT(GetSafe);

			if (!Pawn)
				return nullptr;

			if (APlayerController* PC = Cast<APlayerController>(Pawn->Controller))
				return GetSafe(Context, PC, nullptr);
			return nullptr;
		}

		ICsManager_Input* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked(Context, PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId));
		}

		ICsManager_Input* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PC)
				return nullptr;
			return GetSafe(Context, PC, Log);
		}

		ICsManager_Input* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (ICsManager_Input* Manager_Input = GetSafe(Context, WorldContext, ControllerId, Log))
			{
				UObject* Manager_Input_Object = GetChecked(Context, WorldContext, ControllerId)->_getUObject();

				CS_IS_PENDING_KILL_RET_NULL(Manager_Input_Object)
				return Manager_Input_Object;
			}
			return nullptr;
		}

		#pragma endregion Get

		// ICsManager_Input_Event
		#pragma region

		#define OnGameEventInfoEventType NCsInput::NManager::FOnGameEventInfo
		#define OnGameEventInfosEventType NCsInput::NManager::FOnGameEventInfos
		#define OnAnyKeyPressedEventType NCsInput::NManager::FOnAnyKey_Pressed
		#define OnAnyKeyReleasedEventType NCsInput::NManager::FOnAnyKey_Released
		#define ModeOnChangeEventType NCsInput::NManager::NMode::FOnChange

		ICsManager_Input_Event* FLibrary::GetChecked_ICsManager_Input_Event(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			UObject* Manager_Input = GetAsObjectChecked(Context, WorldContext, ControllerId);

			//check(ImplementsChecked(Context, Player));
		
			return CS_INTERFACE_CAST_CHECKED(Manager_Input, UObject, ICsManager_Input_Event);
		}

		ICsManager_Input_Event* FLibrary::GetSafe_ICsManager_Input_Event(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UObject* Manager_Input = GetSafeAsObject(Context, WorldContext, ControllerId, Log))
			{
				return CS_INTERFACE_CAST(Manager_Input, UObject, ICsManager_Input_Event);
			}
			return nullptr;
		}

		OnGameEventInfoEventType& FLibrary::GetOnGameEventInfo_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetOnGameEventInfo_Event();
		}

		OnGameEventInfosEventType& FLibrary::GetOnGameEventInfos_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetOnGameEventInfos_Event();
		}

		OnAnyKeyPressedEventType& FLibrary::GetOnAnyKey_Pressed_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetOnAnyKey_Pressed_Event();
		}

		FCsManagerInput_OnAnyKey_Pressed FLibrary::GetOnAnyKey_Pressed_ScriptEventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetOnAnyKey_Pressed_ScriptEvent();
		}

		OnAnyKeyReleasedEventType& FLibrary::GetOnAnyKey_Released_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetOnAnyKey_Released_Event();
		}

		FCsManagerInput_OnAnyKey_Released FLibrary::GetOnAnyKey_Released_ScriptEventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetOnAnyKey_Released_ScriptEvent();
		}

		ModeOnChangeEventType& FLibrary::GetActiveMode_OnChange_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetActiveMode_OnChange_Event();
		}

		FCsManagerInput_OnActiveMode_Change FLibrary::GetActiveMode_OnChange_ScriptEventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return GetChecked_ICsManager_Input_Event(Context, WorldContext, ControllerId)->GetActiveMode_OnChange_ScriptEvent();
		}

		#undef OnGameEventInfoEventType
		#undef OnGameEventInfosEventType
		#undef OnAnyKeyPressedEventType
		#undef OnAnyKeyReleasedEventType
		#undef ModeOnChangeEventType

		#pragma endregion ICsManager_Input_Event

		bool FLibrary::Exists(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return GetSafe(Context, WorldContext, ControllerId, Log) != nullptr;
		}

		bool FLibrary::HaveAllBeenCreated(UObject* WorldContext, const int32& NumLocalPlayers)
		{
			checkf(NumLocalPlayers > 0, TEXT("FLibrary::HaveAllBeenCreated: NumLocalPlayer: %d is NOT > 0."), NumLocalPlayers);

			TArray<APlayerController*> PlayerControllers;

			NCsPlayer::NController::NLocal::FLibrary::GetAll(WorldContext, PlayerControllers);

			int32 Count = 0;

			for (APlayerController* PC : PlayerControllers)
			{
				ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

				if (!GetManagerInput)
					return false;

				ICsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

				if (!Manager_Input)
					return false;
				++Count;
			}
			return Count == NumLocalPlayers;
		}

		bool FLibrary::SafeInit(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (ICsManager_Input* ManagerInput = GetSafe(Context, WorldContext, ControllerId, Log))
			{
				ManagerInput->Init();
				return true;
			}
			return false;
		}

		bool FLibrary::SafeInit(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			TArray<APlayerController*> PlayerControllers;

			NCsPlayer::NController::NLocal::FLibrary::GetAll(WorldContext, PlayerControllers);

			int32 Count = 0;

			for (APlayerController* PC : PlayerControllers)
			{
				ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PC);

				if (!GetManagerInput)
					continue;

				ICsManager_Input* Manager_Input = GetManagerInput->GetManager_Input();

				if (!Manager_Input)
					continue;

				Manager_Input->Init();
				++Count;
			}
			
			if (Count == 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No PlayerControllers found that implement the interface: ICsGetManagerInput."), *Context));
				return false;
			}
			return Count > CS_EMPTY;
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef PCLocalLibrary
		#undef PCFirstLocalLibrary

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

			#define USING_NS_CACHED using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsInput::NManager::NInputActionMap::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName
			#define PCLocalLibrary NCsPlayer::NController::NLocal::FLibrary

			// Set
			#pragma region

					// First
			#pragma region

			void FLibrary::SetFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				GetFirstManagerChecked(Context, World)->SetCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SetFirstChecked(UWorld* World, const FECsInputActionMap& Map)
			{
				SET_CONTEXT(SetFirstChecked);

				SetFirstChecked(Context, World, Map);
			}

			void FLibrary::SetFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				GetFirstManagerChecked(Context, WorldContext)->SetCurrentInputActionMap(Context, Map);
			}	

			bool FLibrary::SetSafeFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

				if (ICsManager_Input* Manager_Input = GetSafeFirstManager(Context, WorldContext, Log))
				{
					Manager_Input->SetCurrentInputActionMap(Map);
					return true;
				}
				return false;
			}

			bool FLibrary::SetSafeFirst(const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				SET_CONTEXT(SetSafeFirst);

				return SetSafeFirst(Context, WorldContext, Map, nullptr);
			}

			void FLibrary::SetFirstChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				GetFirstManagerChecked(Context, World)->SetCurrentInputActionMap(Context, Map);
			}

			void FLibrary::SetFirstChecked(UWorld* World, const int32& Map)
			{
				SET_CONTEXT(SetFirstChecked);

				SetFirstChecked(Context, World, Map);
			}

			bool FLibrary::SetSafeFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_INT_GREATER_THAN(Map, 0)

				if (ICsManager_Input* Manager_Input = GetSafeFirstManager(Context, World, Log))
				{
					Manager_Input->SetCurrentInputActionMap(Map);
					return true;
				}
				return false;
			}

			#pragma endregion First

			void FLibrary::SetChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
			{
				GetManagerChecked(Context, PC)->SetCurrentInputActionMap(Context, Map);
			}

			bool FLibrary::SetSafe(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

				ICsManager_Input* Manager_Input = GetSafeManager(Context, PC, Log);

				if (!Manager_Input)
					return false;

				Manager_Input->SetCurrentInputActionMap(Context, Map);
				return true;
			}

			void FLibrary::SetChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAllChecked(Context, World, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					SetChecked(Context, PC, Map);
				}
			}

			void FLibrary::SetChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAllChecked(Context, WorldContext, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					SetChecked(Context, PC, Map);
				}
			}

			void FLibrary::SetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map)
			{
				APlayerController* PC = PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);

				SetChecked(Context, PC, Map);
			}

			bool FLibrary::SetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

				return SetSafe(Context, PC, Map);
			}

			#pragma endregion Set

			// Clear
			#pragma region

				// First
			#pragma region

			void FLibrary::ClearFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map)
			{
				GetFirstManagerChecked(Context, World)->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(UWorld* World, const FECsInputActionMap& Map)
			{
				SET_CONTEXT(ClearFirstChecked);

				ClearFirstChecked(Context, World, Map);
			}

			bool FLibrary::SafeClearFirst(const FString& Context, UWorld* World, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

				if (ICsManager_Input* Manager_Input = GetSafeFirstManager(Context, World, Log))
				{
					Manager_Input->ClearCurrentInputActionMap(Map);
					return true;
				}
				return false;
			}

			bool FLibrary::SafeClearFirst(UWorld* World, const FECsInputActionMap& Map)
			{
				SET_CONTEXT(SafeClearFirst);

				return SafeClearFirst(Context, World, Map, nullptr);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map)
			{
				GetFirstManagerChecked(Context, WorldContext)->ClearCurrentInputActionMap(Context, Map);
			}
			
			bool FLibrary::SafeClearFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

				ICsManager_Input* Manager_Input = GetSafeFirstManager(Context, WorldContext, Log);

				if (!Manager_Input)
					return false;

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
				return true;
			}

			void FLibrary::ClearFirstChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				GetFirstManagerChecked(Context, World)->ClearCurrentInputActionMap(Context, Map);
			}

			void FLibrary::ClearFirstChecked(UWorld* World, const int32& Map)
			{
				SET_CONTEXT(ClearFirstChecked);

				ClearFirstChecked(Context, World, Map);
			}

			bool FLibrary::SafeClearFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_INT_GREATER_THAN(Map, 0)

				if (ICsManager_Input* Manager_Input = GetSafeFirstManager(Context, World, Log))
				{
					Manager_Input->ClearCurrentInputActionMap(Map);
					return true;
				}
				return false;
			}

			bool FLibrary::SafeClearFirst(UWorld* World, const int32& Map)
			{
				SET_CONTEXT(SafeClearFirst);

				return SafeClearFirst(Context, World, Map, nullptr);
			}

			void FLibrary::ClearFirstChecked(const FString& Context, const UObject* WorldContext, const int32& Map)
			{
				GetFirstManagerChecked(Context, WorldContext)->ClearCurrentInputActionMap(Context, Map);
			}

			#pragma endregion First

			void FLibrary::ClearChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map)
			{
				GetManagerChecked(Context, PC)->ClearCurrentInputActionMap(Context, Map);
			}

			bool FLibrary::SafeClear(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

				ICsManager_Input* Manager_Input = GetSafeManager(Context, PC, Log);

				if (!Manager_Input)
					return false;

				Manager_Input->ClearCurrentInputActionMap(Context, Map);
				return true;
			}

			void FLibrary::ClearChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map)
			{
				APlayerController* PC = PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);

				ClearChecked(Context, PC, Map);
			}

			bool FLibrary::SafeClear(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

				return SafeClear(Context, PC, Map, Log);
			}

			void FLibrary::ClearChecked(const FString& Context, UWorld* World, const int32& Map)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAllChecked(Context, World, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					GetManagerChecked(Context, PC)->ClearCurrentInputActionMap(Context, Map);
				}
			}

			void FLibrary::ClearChecked(const FString& Context, const UObject* WorldContext, const int32& Map)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAllChecked(Context, WorldContext, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					GetManagerChecked(Context, PC)->ClearCurrentInputActionMap(Context, Map);
				}
			}

			void FLibrary::ClearChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const int32& Map)
			{
				APlayerController* PC = PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);

				ClearChecked(Context, PC, Map);
			}

			#pragma endregion Clear

			// Reset
			#pragma region

			void FLibrary::ResetFirstChecked(const FString& Context, UWorld* World)
			{
				GetFirstManagerChecked(Context, World)->ResetCurrentInputActionMap();
			}

			void FLibrary::ResetFirstChecked(const FString& Context, const UObject* WorldContext)
			{
				GetFirstManagerChecked(Context, WorldContext)->ResetCurrentInputActionMap();
			}

			bool FLibrary::SafeResetFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				ICsManager_Input* Manager_Input = GetSafeFirstManager(Context, WorldContext, Log);

				if (!Manager_Input)
					return false;

				Manager_Input->ResetCurrentInputActionMap();
				return true;
			}

			void FLibrary::ResetChecked(const FString& Context, APlayerController* PC)
			{
				GetManagerChecked(Context, PC)->ResetCurrentInputActionMap();
			}

			bool FLibrary::SafeReset(const FString& Context, APlayerController* PC, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				ICsManager_Input* Manager_Input = GetSafeManager(Context, PC, Log);

				if (!Manager_Input)
					return false;

				Manager_Input->ResetCurrentInputActionMap();
				return true;
			}

			void FLibrary::ResetChecked(const FString& Context, UWorld* World)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAllChecked(Context, World, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					GetManagerChecked(Context, PC)->ResetCurrentInputActionMap();
				}
			}

			void FLibrary::ResetChecked(const FString& Context, const UObject* WorldContext)
			{
				TArray<APlayerController*> PlayerControllers;

				PCLocalLibrary::GetAllChecked(Context, WorldContext, PlayerControllers);

				for (APlayerController* PC : PlayerControllers)
				{
					GetManagerChecked(Context, PC)->ResetCurrentInputActionMap();
				}
			}

			bool FLibrary::SafeReset(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				TArray<APlayerController*> PlayerControllers;

				if (PCLocalLibrary::GetSafeAll(Context, WorldContext, PlayerControllers, Log))
				{
					for (APlayerController* PC : PlayerControllers)
					{
						ICsManager_Input* Manager_Input = GetSafeManager(Context, PC, Log);

						if (!Manager_Input)
							return false;

						Manager_Input->ResetCurrentInputActionMap();
					}
					return true;
				}
				return false;
			}

			void FLibrary::ResetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
			{
				APlayerController* PC = PCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);

				ResetChecked(Context, PC);
			}

			bool FLibrary::SafeReset(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				APlayerController* PC = PCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

				return SafeReset(Context, PC, Log);
			}

			#pragma endregion Reset

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
			#undef PCLocalLibrary
		}

		namespace NProfile
		{
			void FLibrary::ResetToDefaultChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FCsInputActionMappings& Mappings, const ECsInputDevice& Device)
			{
				ICsManager_Input* Manager_Input			   = NCsInput::NManager::FLibrary::GetChecked(Context, WorldContext, ControllerId);
				const FCsInputProfile& DefaultInputProfile = Manager_Input->GetDefaultInputProfile();

				CS_IS_ENUM_VALID_CHECKED(EMCsInputDevice, Device)

				const FCsInputActionMappings& DefaultMappings = DefaultInputProfile.GetMappings(Device);

				Mappings.ConditionalCopyMappingsByActionChecked(Context, DefaultMappings);
			}

			void FLibrary::ResetToDefaultChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, TArray<FCsInputActionMappings>& Mappings)
			{
				ICsManager_Input* Manager_Input			   = NCsInput::NManager::FLibrary::GetChecked(Context, WorldContext, ControllerId);
				const FCsInputProfile& DefaultInputProfile = Manager_Input->GetDefaultInputProfile();

				CS_IS_TARRAY_EMPTY_CHECKED(Mappings, FCsInputActionMappings)

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