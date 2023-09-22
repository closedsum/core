// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Input
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/Profile/CsTypes_InputProfile.h"
// Log
#include "Utility/CsLog.h"

class UWorld;
class UCsManager_Input;
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

			static UCsManager_Input* GetFirstChecked(const FString& Context, UWorld* World);

			static UCsManager_Input* GetFirstChecked(UWorld* World);

			static UCsManager_Input* GetFirstChecked(const FString& Context, const UObject* WorldContext);

			static UCsManager_Input* GetFirstChecked(const UObject* WorldContext);

			static UCsManager_Input* GetSafeFirst(const FString& Context, UWorld* World, void(*Log)(const FString&) = &FCsLog::Warning);

			static UCsManager_Input* GetSafeFirst(UWorld* World);

			static UCsManager_Input* GetSafeFirst(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			static UCsManager_Input* GetSafeFirst(const UObject* WorldContext);

			static UCsManager_Input* GetChecked(const FString& Context, APlayerController* PC);

			static UCsManager_Input* GetSafe(const FString& Context, APlayerController* PC, void(*Log)(const FString&) = &FCsLog::Warning);

			static UCsManager_Input* GetSafe(APawn* Pawn);

			/**
			* Get the Manager_Input associated with the player controller with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* return				Manager_Input
			*/
			static UCsManager_Input* GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			/**
			* Safely get the Manager_Input associated with the player controller with ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param Log			(optional)
			* return				Manager_Input
			*/
			static UCsManager_Input* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Get

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

		namespace NInputActionMap
		{
			struct CSCORE_API FLibrary final
			{
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
				static void SetSafeFirst(const FString& Context, UWorld* World, const int32& Map, void(*Log)(const FString&) = &FCsLog::Warning);

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