// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Input/CsTypes_Input.h"

class UWorld;
class UCsManager_Input;
class APlayerController;

namespace NCsInput
{
	namespace NManager
	{
		class CSCORE_API FLibrary
		{
		public:

			static UCsManager_Input* GetFirst(UWorld* World);

			static UCsManager_Input* GetFirstChecked(const FString& Context, UWorld* World);

			static UCsManager_Input* GetFirstChecked(const FString& Context, UObject* WorldContext);

			static UCsManager_Input* GetFirstChecked(UWorld* World);

			static UCsManager_Input* GetChecked(const FString& Context, APlayerController* PC);

			static bool HaveAllBeenCreated(UObject* WorldContext, const int32& NumLocalPlayers);

		// InputActionMap
		#pragma region

			// Set
		#pragma region

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstInputActionMap(UWorld* World, const FECsInputActionMap& Map);
	
			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context	The calling context.
			* @param World
			* @param Map		A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map);
	
			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void SetFirstInputActionMap(UWorld* World, const int32& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void SetFirstInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void SetFirstInputActionMapChecked(UWorld* World, const int32& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for all local player controllers.
			*
			* @param Context			The calling context.
			* @param PlayerController
			* @param Map				A EnumStructFlag (contains a bit flag).
			*/
			static void SetInputActionMapChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for all local player controllers.
			*
			* @param Context		The calling context.
			* @param World
			* @param Map			A EnumStructFlag (contains a bit flag).
			*/
			static void SetInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for all local player controllers.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A EnumStructFlag (contains a bit flag).
			*/
			static void SetInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map);

			/**
			*
			
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param Map			A EnumStructFlag (contains a bit flag).
			*/
			static void SetInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, const FECsInputActionMap& Map);

		#pragma endregion Set

			// Clear
		#pragma region

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag). 
			*/
			static void ClearFirstInputActionMap(UWorld* World, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context	The calling context.
			* @param World
			* @param Map		A EnumStructFlag (contains a bit flag).
			*/
			static void ClearFirstInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A EnumStructFlag (contains a bit flag).
			*/
			static void ClearFirstInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag).
			*/
			static void ClearFirstInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstInputActionMap(UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context	The calling context.
			* @param World
			* @param Map		A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstInputActionMapChecked(UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
			*
			* @param Context			The calling context.
			* @param PlayerController
			* @param Map				A EnumStructFlag (contains a bit flag).
			*/
			static void ClearInputActionMapChecked(const FString& Context, APlayerController* PC, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
			* 
			* @param Context	The calling context.
			* @param World
			* @param Map		A bit flag. See FECsInputActionMap.
			*/
			static void ClearInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A bit flag. See FECsInputActionMap.
			*/
			static void ClearInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param Map			A bit flag. See FECsInputActionMap.
			*/
			static void ClearInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, const int32& Map);

		#pragma endregion Clear

			// Reset
		#pragma region

			/**
			* Resets the CurrentInputActionMap to 0 for the first local player controller.
			* 
			* @param Context	The calling context.
			* @param World
			*/
			static void ResetFirstInputActionMapChecked(const FString& Context, UWorld* World);

			/**
			* Resets the CurrentInputActionMap to 0 for the first local player controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ResetFirstInputActionMapChecked(const FString& Context, UObject* WorldContext);

			/**
			* Resets the CurrentInputActionMap to 0 for the Player Controller.
			*
			* @param Context			The calling context.
			* @param PlayerController
			*/
			static void ResetInputActionMapChecked(const FString& Context, APlayerController* PC);

			/**
			* Resets the CurrentInputActionMap to 0 for all local player controllers.
			* 
			* @param Context	The calling context.
			* @param World
			*/
			static void ResetInputActionMapChecked(const FString& Context, UWorld* World);

			/**
			* Resets the CurrentInputActionMap to 0 for all local player controllers.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ResetInputActionMapChecked(const FString& Context, UObject* WorldContext);

			/**
			* Resets the CurrentInputActionMap to 0 for all local player controllers.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			*/
			static void ResetInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId);

		#pragma endregion Reset

		#pragma endregion InputActionMap
		};
	}
}