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

			static UCsManager_Input* GetFirstLocalManagerInput(UWorld* World);

			static UCsManager_Input* GetFirstLocalManagerInputChecked(const FString& Context, UWorld* World);

			static UCsManager_Input* GetFirstLocalManagerInputChecked(UWorld* World);

			static UCsManager_Input* GetManagerInputChecked(const FString& Context, APlayerController* PC);

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
			static void SetFirstLocalCurrentInputActionMap(UWorld* World, const FECsInputActionMap& Map);
	
			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context	The calling context.
			* @param World
			* @param Map		A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const FECsInputActionMap& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag).
			*/
			static void SetFirstLocalCurrentInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map);
	
			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void SetFirstLocalCurrentInputActionMap(UWorld* World, const int32& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

			/**
			* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void SetFirstLocalCurrentInputActionMapChecked(UWorld* World, const int32& Map);

		#pragma endregion Set

			// Clear
		#pragma region

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag). 
			*/
			static void ClearFirstLocalCurrentInputActionMap(UWorld* World, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context	The calling context.
			* @param World
			* @param Map		A EnumStructFlag (contains a bit flag).
			*/
			static void ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A EnumStructFlag (contains a bit flag).
			*/
			static void ClearFirstLocalCurrentInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstLocalCurrentInputActionMap(UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param Context	The calling context.
			* @param World
			* @param Map		A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
			*
			* @param World
			* @param Map	A bit flag. See FECsInputActionMap.
			*/
			static void ClearFirstLocalCurrentInputActionMapChecked(UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
			* 
			* @param Context	The calling context.
			* @param World
			* @param Map		A bit flag. See FECsInputActionMap.
			*/
			static void ClearLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

			/**
			* Clears the bit (Map) in CurrentInputActionMap for all local player controllers.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Map			A bit flag. See FECsInputActionMap.
			*/
			static void ClearLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext, const int32& Map);

		#pragma endregion Clear

			// Reset
		#pragma region

			/**
			* Resets the CurrentInputActionMap to 0 for the first local player controller.
			* 
			* @param Context	The calling context.
			* @param World
			*/
			static void ResetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World);

			/**
			* Resets the CurrentInputActionMap to 0 for the first local player controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ResetFirstLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext);

			/**
			* Resets the CurrentInputActionMap to 0 for all local player controllers.
			* 
			* @param Context	The calling context.
			* @param World
			*/
			static void ResetLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World);

			/**
			* Resets the CurrentInputActionMap to 0 for all local player controllers.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ResetLocalCurrentInputActionMapChecked(const FString& Context, UObject* WorldContext);

		#pragma endregion Reset

		#pragma endregion InputActionMap
		};
	}
}