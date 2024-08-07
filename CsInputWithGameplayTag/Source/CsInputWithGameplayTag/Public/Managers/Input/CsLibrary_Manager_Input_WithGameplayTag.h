// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsInputWithGameplayTagLog.h"

class UWorld;
class ICsManager_Input_WithGameplayTag;
class APlayerController;
class APawn;

namespace NCsInput
{
	namespace NWithGameplayTag
	{
		namespace NManager
		{
			class CSINPUTWITHGAMEPLAYTAG_API FLibrary
			{
			#define LogLevel void(*Log)(const FString&) = &NCsInput::NWithGameplayTag::FLog::Warning

			// Get
			#pragma region
			public:

				static ICsManager_Input_WithGameplayTag* GetChecked(const FString& Context, APlayerController* PC);

				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, APlayerController* PC, LogLevel);

				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, APlayerController* PC, bool& OutSuccess, LogLevel);

				static ICsManager_Input_WithGameplayTag* GetSafe(APawn* Pawn);

				/**
				* Get the Manager_Input associated with the player controller with ControllerId.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* return				Manager_Input
				*/
				static ICsManager_Input_WithGameplayTag* GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

				/**
				* Safely get the Manager_Input associated with the player controller with ControllerId.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllerId
				* @param Log			(optional)
				* return				Manager_Input
				*/
				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel);

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
				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, LogLevel);

				static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

				static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel);
				FORCEINLINE static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, LogLevel)
				{
					UObject* O = GetSafeAsObject(Context, WorldContext, ControllerId, Log);
					OutSuccess = O != nullptr;
					return O;
				}

			#pragma endregion Get

			public:

				static bool Exists(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel);

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
				static bool SafeInit(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel);

				/**
				* Safely call Manager_Input->Input() on all PlayerControllers that implement the interface: ICsGetManagerInput
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log			(optional)
				* return				Whether Manager_Input->Input() was successfully called or not.
				*/
				static bool SafeInit(const FString& Context, const UObject* WorldContext, LogLevel);

			#undef LogLevel
			};

			namespace NFirst
			{
				class CSINPUTWITHGAMEPLAYTAG_API FLibrary
				{
				#define LogLevel void(*Log)(const FString&) = &NCsInput::NWithGameplayTag::FLog::Warning
				#define InputManagerLibrary NCsInput::NWithGameplayTag::NManager::FLibrary

				// Get
				#pragma region
				public:

					FORCEINLINE static ICsManager_Input_WithGameplayTag* GetChecked(const FString& Context, const UObject* WorldContext)
					{
						return InputManagerLibrary::GetChecked(Context, WorldContext, 0);
					}

					FORCEINLINE static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
					{
						return InputManagerLibrary::GetSafe(Context, WorldContext, 0, Log);
					}

					FORCEINLINE static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
					{
						return InputManagerLibrary::GetAsObjectChecked(Context, WorldContext, 0);
					}

				#pragma endregion Get

				public:

					FORCEINLINE static bool Exists(const FString& Context, const UObject* WorldContext, LogLevel)
					{
						return InputManagerLibrary::Exists(Context, WorldContext, 0, Log);
					}

				#undef LogLevel
				#undef InputManagerLibrary
				};
			}
		}
	}
}