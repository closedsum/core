// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Input
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/Profile/CsTypes_InputProfile.h"
#include "Managers/Input/Event/CsManager_Input_Event.h"
// Log
#include "Utility/CsLog.h"

class UWorld;
class ICsManager_Input;
class ICsManager_Input_Event;
class APlayerController;
class APawn;

namespace NCsInput
{
	namespace NManager
	{
		class CSCORE_API FLibrary
		{
		// Get
		#pragma region
		public:

			static ICsManager_Input* GetFirstChecked(const FString& Context, UWorld* World);

			static ICsManager_Input* GetFirstChecked(UWorld* World);

			static ICsManager_Input* GetFirstChecked(const FString& Context, const UObject* WorldContext);

			static ICsManager_Input* GetFirstChecked(const UObject* WorldContext);

			static ICsManager_Input* GetSafeFirst(const FString& Context, UWorld* World, void(*Log)(const FString&) = &FCsLog::Warning);

			static ICsManager_Input* GetSafeFirst(UWorld* World);

			static ICsManager_Input* GetSafeFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			static ICsManager_Input* GetSafeFirst(const UObject* WorldContext);

			static ICsManager_Input* GetChecked(const FString& Context, APlayerController* PC);

			static ICsManager_Input* GetSafe(const FString& Context, APlayerController* PC, void(*Log)(const FString&) = &FCsLog::Warning);

			static ICsManager_Input* GetSafe(const FString& Context, APlayerController* PC, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

			static ICsManager_Input* GetSafe(APawn* Pawn);

			/**
			* Get the Manager_Input associated with the player controller with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* return				Manager_Input
			*/
			static ICsManager_Input* GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			/**
			* Safely get the Manager_Input associated with the player controller with ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param Log			(optional)
			* return				Manager_Input
			*/
			static ICsManager_Input* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the Manager_Input associated with the player controller with ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				Manager_Input
			*/
			static ICsManager_Input* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

			static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				UObject* O = GetSafeAsObject(Context, WorldContext, ControllerId, Log);
				OutSuccess = O != nullptr;
				return O;
			}

		#pragma endregion Get

		// ICsManager_Input_Event
		#pragma region
		public:

		#define OnGameEventInfoEventType NCsInput::NManager::FOnGameEventInfo
		#define OnGameEventInfosEventType NCsInput::NManager::FOnGameEventInfos
		#define OnAnyKeyPressedEventType NCsInput::NManager::FOnAnyKey_Pressed
		#define OnAnyKeyReleasedEventType NCsInput::NManager::FOnAnyKey_Released
		#define ModeOnChangeEventType NCsInput::NManager::NMode::FOnChange

			static ICsManager_Input_Event* GetChecked_ICsManager_Input_Event(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static ICsManager_Input_Event* GetSafe_ICsManager_Input_Event(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			static OnGameEventInfoEventType& GetOnGameEventInfo_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static OnGameEventInfosEventType& GetOnGameEventInfos_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static OnAnyKeyPressedEventType& GetOnAnyKey_Pressed_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static FCsManagerInput_OnAnyKey_Pressed GetOnAnyKey_Pressed_ScriptEventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static OnAnyKeyReleasedEventType& GetOnAnyKey_Released_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static FCsManagerInput_OnAnyKey_Released GetOnAnyKey_Released_ScriptEventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static ModeOnChangeEventType& GetActiveMode_OnChange_EventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
			static FCsManagerInput_OnActiveMode_Change GetActiveMode_OnChange_ScriptEventChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

		#undef OnGameEventInfoEventType
		#undef OnGameEventInfosEventType
		#undef OnAnyKeyPressedEventType
		#undef OnAnyKeyReleasedEventType
		#undef ModeOnChangeEventType

		#pragma endregion ICsManager_Input_Event

		public:

			static bool Exists(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			static bool HaveAllBeenCreated(UObject* WorldContext, const int32& NumLocalPlayers);

			/**
			* Safely call Manager_Input->Input() on the PlayerController with ControllerId and
			* implements the interface: ICsGetManagerInput
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param Log			(optional)
			* return				Whether Manager_Input->Input() was successfully called or not.
			*/
			static bool SafeInit(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely call Manager_Input->Input() on all PlayerControllers that implement the interface: ICsGetManagerInput
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				Whether Manager_Input->Input() was successfully called or not.
			*/
			static bool SafeInit(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		};

		namespace NFirst
		{
			class CSCORE_API FLibrary
			{
			#define InputManagerLibrary NCsInput::NManager::FLibrary

			// Get
			#pragma region
			public:

				//static ICsManager_Input* GetFirstChecked(const FString& Context, UWorld* World);

				//static ICsManager_Input* GetFirstChecked(UWorld* World);

				FORCEINLINE static ICsManager_Input* GetChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetChecked(Context, WorldContext, CS_FIRST);
				}

				//static ICsManager_Input* GetFirstChecked(const UObject* WorldContext);

				FORCEINLINE static ICsManager_Input* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return InputManagerLibrary::GetSafe(Context, WorldContext, CS_FIRST, Log);
				}

				//static ICsManager_Input* GetSafeFirst(const UObject* WorldContext);

				FORCEINLINE static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
				{
					return InputManagerLibrary::GetAsObjectChecked(Context, WorldContext, CS_FIRST);
				}

			#pragma endregion Get

			public:

				FORCEINLINE static bool Exists(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return InputManagerLibrary::Exists(Context, WorldContext, CS_FIRST, Log);
				}


			// ICsManager_Input_Event
			#pragma region
			public:

			#define OnGameEventInfoEventType NCsInput::NManager::FOnGameEventInfo
			#define OnGameEventInfosEventType NCsInput::NManager::FOnGameEventInfos
			#define OnAnyKeyPressedEventType NCsInput::NManager::FOnAnyKey_Pressed
			#define OnAnyKeyReleasedEventType NCsInput::NManager::FOnAnyKey_Released
			#define ModeOnChangeEventType NCsInput::NManager::NMode::FOnChange

				FORCEINLINE static ICsManager_Input_Event* GetChecked_ICsManager_Input_Event(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetChecked_ICsManager_Input_Event(Context, WorldContext, CS_FIRST);
				}

				FORCEINLINE static ICsManager_Input_Event* GetSafe_ICsManager_Input_Event(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return InputManagerLibrary::GetSafe_ICsManager_Input_Event(Context, WorldContext, CS_FIRST, Log);
				}

				FORCEINLINE static OnGameEventInfoEventType& GetOnGameEventInfo_EventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetOnGameEventInfo_EventChecked(Context, WorldContext, CS_FIRST);
				}

				FORCEINLINE static OnGameEventInfosEventType& GetOnGameEventInfos_EventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetOnGameEventInfos_EventChecked(Context, WorldContext, CS_FIRST);
				}
				
				FORCEINLINE static OnAnyKeyPressedEventType& GetOnAnyKey_Pressed_EventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetOnAnyKey_Pressed_EventChecked(Context, WorldContext, CS_FIRST);
				}
				
				FORCEINLINE static FCsManagerInput_OnAnyKey_Pressed GetOnAnyKey_Pressed_ScriptEventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetOnAnyKey_Pressed_ScriptEventChecked(Context, WorldContext, CS_FIRST);
				}
				
				FORCEINLINE static OnAnyKeyReleasedEventType& GetOnAnyKey_Released_EventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetOnAnyKey_Released_EventChecked(Context, WorldContext, CS_FIRST);
				}
				
				FORCEINLINE static FCsManagerInput_OnAnyKey_Released GetOnAnyKey_Released_ScriptEventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetOnAnyKey_Released_ScriptEventChecked(Context, WorldContext, CS_FIRST);
				}
				
				FORCEINLINE static ModeOnChangeEventType& GetActiveMode_OnChange_EventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetActiveMode_OnChange_EventChecked(Context, WorldContext, CS_FIRST);
				}
				
				FORCEINLINE static FCsManagerInput_OnActiveMode_Change GetActiveMode_OnChange_ScriptEventChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetActiveMode_OnChange_ScriptEventChecked(Context, WorldContext, CS_FIRST);
				}

			#undef OnGameEventInfoEventType
			#undef OnGameEventInfosEventType
			#undef OnAnyKeyPressedEventType
			#undef OnAnyKeyReleasedEventType
			#undef ModeOnChangeEventType

			#pragma endregion ICsManager_Input_Event

			#undef InputManagerLibrary
			};
		}

		namespace NInputActionMap
		{
			struct CSCORE_API FLibrary final
			{
			public:

			#define InputManagerLibrary NCsInput::NManager::FLibrary

				FORCEINLINE static ICsManager_Input* GetFirstManagerChecked(const FString& Context, const UObject* WorldContext)
				{
					return InputManagerLibrary::GetFirstChecked(Context, WorldContext);
				}

				FORCEINLINE static ICsManager_Input* GetSafeFirstManager(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return InputManagerLibrary::GetSafeFirst(Context, WorldContext, Log);
				}

				FORCEINLINE static ICsManager_Input* GetManagerChecked(const FString& Context, APlayerController* PC)
				{
					return InputManagerLibrary::GetChecked(Context, PC);
				}

				FORCEINLINE static ICsManager_Input* GetSafeManager(const FString& Context, APlayerController* PC, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return InputManagerLibrary::GetSafe(Context, PC, Log);
				}

			#undef InputManagerLibrary

			// Set
			#pragma region

				// First
			#pragma region
			public:

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A EnumStructFlag (contains a bit flag).
				*/
				static void SetFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param World
				* @param Map	A EnumStructFlag (contains a bit flag).
				*/
				static void SetFirstChecked(UWorld* World, const FECsInputActionMap& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A EnumStructFlag (contains a bit flag).
				*/
				static void SetFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A EnumStructFlag (contains a bit flag).
				* @param Log
				* return
				*/
				static bool SetSafeFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A EnumStructFlag (contains a bit flag).
				* return
				*/
				static bool SetSafeFirst(const UObject* WorldContext, const FECsInputActionMap& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A bit flag. See FECsInputActionMap.
				*/
				static void SetFirstChecked(const FString& Context, UWorld* World, const int32& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param World
				* @param Map	A bit flag. See FECsInputActionMap.
				*/
				static void SetFirstChecked(UWorld* World, const int32& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A bit flag. See FECsInputActionMap.
				* @param Log
				*/
				static bool SetSafeFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) = &FCsLog::Warning);

			#pragma endregion First

			public:

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the player controller (PC).
				*
				* @param Context	The calling context.
				* @param PC			Player Controller.
				* @param Map		A EnumStructFlag (contains a bit flag).
				*/
				static void SetChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for the player controller (PC).
				*
				* @param Context	The calling context.
				* @param PC			Player Controller.
				* @param Map		A EnumStructFlag (contains a bit flag).
				* @param Log		(optional)
				* return
				*/
				static bool SetSafe(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for all local player controllers.
				*
				* @param Context		The calling context.
				* @param World
				* @param Map			A EnumStructFlag (contains a bit flag).
				*/
				static void SetChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

				/**
				* Sets the bit (Map) in CurrentInputActionMap for all local player controllers.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A EnumStructFlag (contains a bit flag).
				*/
				static void SetChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map);

				/**
				* Set the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Map			A EnumStructFlag (contains a bit flag).
				*/
				static void SetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map);

				/**
				* Safely set the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Map			A EnumStructFlag (contains a bit flag).
				* @param Log			(optional)
				* return
				*/
				static bool SetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

			#pragma endregion Set

			// Clear
			#pragma region

				// First
			#pragma region
			public:

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A EnumStructFlag (contains a bit flag).
				*/
				static void ClearFirstChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param World
				* @param Map	A EnumStructFlag (contains a bit flag).
				*/
				static void ClearFirstChecked(UWorld* World, const FECsInputActionMap& Map);

				/**
				* safely clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A EnumStructFlag (contains a bit flag).
				* @param Log		(optional)
				* return
				*/
				static bool SafeClearFirst(const FString& Context, UWorld* World, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* safely clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param World
				* @param Map	A EnumStructFlag (contains a bit flag).
				*/
				static bool SafeClearFirst(UWorld* World, const FECsInputActionMap& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A EnumStructFlag (contains a bit flag).
				*/
				static void ClearFirstChecked(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map);

				/**
				* Safely clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A EnumStructFlag (contains a bit flag).
				* @param Log			(optional)
				* return
				*/
				static bool SafeClearFirst(const FString& Context, const UObject* WorldContext, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A bit flag. See FECsInputActionMap.
				*/
				static void ClearFirstChecked(const FString& Context, UWorld* World, const int32& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param World
				* @param Map	A bit flag. See FECsInputActionMap.
				*/
				static void ClearFirstChecked(UWorld* World, const int32& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context	The calling context.
				* @param World
				* @param Map		A bit flag. See FECsInputActionMap.
				* @param Log		(optional)
				* return
				*/
				static bool SafeClearFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param World
				* @param Map	A bit flag. See FECsInputActionMap.
				* return
				*/
				static bool SafeClearFirst(UWorld* World, const int32& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A bit flag. See FECsInputActionMap.
				*/
				static void ClearFirstChecked(const FString& Context, const UObject* WorldContext, const int32& Map);

			#pragma endregion First

			public:

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the player controller (PC).
				*
				* @param Context			The calling context.
				* @param PlayerController
				* @param Map				A EnumStructFlag (contains a bit flag).
				*/
				static void ClearChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map);

				/**
				* Safely clears the bit (Map) in CurrentInputActionMap for the player controller (PC).
				*
				* @param Context			The calling context.
				* @param PlayerController
				* @param Map				A EnumStructFlag (contains a bit flag).
				* @param Log				(optional)
				* return
				*/
				static bool SafeClear(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Map			A bit flag. See FECsInputActionMap.
				*/
				static void ClearChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map);

				/**
				* Safely clears the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Map			A bit flag. See FECsInputActionMap.
				* @param Log			(optional)
				* return
				*/
				static bool SafeClear(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
				* 
				* @param Context	The calling context.
				* @param World
				* @param Map		A bit flag. See FECsInputActionMap.
				*/
				static void ClearChecked(const FString& Context, UWorld* World, const int32& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Map			A bit flag. See FECsInputActionMap.
				*/
				static void ClearChecked(const FString& Context, const UObject* WorldContext, const int32& Map);

				/**
				* Clears the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Map			A bit flag. See FECsInputActionMap.
				*/
				static void ClearChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const int32& Map);

			#pragma endregion Clear

			// Reset
			#pragma region
			public:

				/**
				* Resets the CurrentInputActionMap to 0 for the first local player controller.
				* 
				* @param Context	The calling context.
				* @param World
				*/
				static void ResetFirstChecked(const FString& Context, UWorld* World);

				/**
				* Resets the CurrentInputActionMap to 0 for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				*/
				static void ResetFirstChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely resets the CurrentInputActionMap to 0 for the first local player controller.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log			(optional)
				* return
				*/
				static bool SafeResetFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Resets the CurrentInputActionMap to 0 for the Player Controller.
				*
				* @param Context			The calling context.
				* @param PlayerController
				*/
				static void ResetChecked(const FString& Context, APlayerController* PC);

				/**
				* Safely resets the CurrentInputActionMap to 0 for the Player Controller.
				*
				* @param Context			The calling context.
				* @param PlayerController
				* @param Log				(optional)
				* return
				*/
				static bool SafeReset(const FString& Context, APlayerController* PC, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Resets the CurrentInputActionMap to 0 for all local player controllers.
				* 
				* @param Context	The calling context.
				* @param World
				*/
				static void ResetChecked(const FString& Context, UWorld* World);

				/**
				* Resets the CurrentInputActionMap to 0 for all local player controllers.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				*/
				static void ResetChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely resets the CurrentInputActionMap to 0 for all local player controllers.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log			(optional)
				* return				Whether the reset was executed successfully or not.
				*/
				static bool SafeReset(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Resets the CurrentInputActionMap to 0 for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				*/
				static void ResetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

				/**
				* Safely resets the CurrentInputActionMap to 0 for the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Log			(optional)
				* return
				*/
				static bool SafeReset(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			#pragma endregion Reset
			};
		}

		namespace NProfile
		{
			struct CSCORE_API FLibrary final
			{
			public:

				/**
				* Reset the Mappings for Device to the "Default" Mappings located in Manager_Input associated with ControllerId.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Mappings
				* @param Device
				*/
				static void ResetToDefaultChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FCsInputActionMappings& Mappings, const ECsInputDevice& Device);

				/**
				* Reset the array Mappings to the "Default" Mappings located in Manager_Input associated with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Mappings
				* @param Device
				*/
				static void ResetToDefaultChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, TArray<FCsInputActionMappings>& Mappings);

				/**
				* Safley reset the array Mappings to the "Default" Mappings located in Manager_Input associated with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Mappings
				* @param Device
				* @param Log			(optional)
				*/
				static bool SafeResetToDefault(const FString& Context, const UObject* WorldContext, const int32& ControllerId, TArray<FCsInputActionMappings>& Mappings, void(*Log)(const FString&) = &FCsLog::Warning);
			};
		}
	}
}