// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "GameplayTagContainer.h"
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
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

			// Get
			#pragma region
			public:

				static ICsManager_Input_WithGameplayTag* GetChecked(const FString& Context, APlayerController* PC);

				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, APlayerController* PC, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, APlayerController* PC, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

				static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					UObject* O = GetSafeAsObject(Context, WorldContext, ControllerId, Log);
					OutSuccess = O != nullptr;
					return O;
				}

			#pragma endregion Get

			public:

				static bool Exists(const FString& Context, const UObject* WorldContext, const int32& ControllerId, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static bool SafeInit(const FString& Context, const UObject* WorldContext, const int32& ControllerId, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely call Manager_Input->Input() on all PlayerControllers that implement the interface: ICsGetManagerInput
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log			(optional)
				* return				Whether Manager_Input->Input() was successfully called or not.
				*/
				static bool SafeInit(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			// Tag
			#pragma region
			public:

				// HasMapping

				static bool HasMappingChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag);
				static bool HasMappingChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag);
				static bool HasMappingChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag);

				static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeHasMapping(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}
				static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeHasMapping(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}
				static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeHasMapping(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}

				// SetMappingActive

				static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag);
				static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag);
				static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag);

				static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);		
				FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeSetMappingActive(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}
				static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);		
				FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeSetMappingActive(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}
				static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);		
				FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeSetMappingActive(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}

				// SetMappingInactive

				static void SetMappingInactiveChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag);
				static void SetMappingInactiveChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag);
				static void SetMappingInactiveChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag);

				static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}
				static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}
				static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, Log);
					return OutSuccess;
				}

				// BlockMapping

				FORCEINLINE static void BlockMappingChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag)
				{
					SetMappingInactiveChecked(Context, WorldContext, ControllerId, Tag);
				}
				FORCEINLINE static void BlockMappingChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag)
				{
					SetMappingInactiveChecked(Context, WorldContext, ControllerId, Tag);
				}
				FORCEINLINE static void BlockMappingChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag)
				{
					SetMappingInactiveChecked(Context, WorldContext, ControllerId, Tag);
				}

				FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					return SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, Log);
				}
				FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					return SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, OutSuccess, Log);
				}
				FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					return SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, Log);
				}
				FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					return SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, OutSuccess, Log);
				}
				FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					return SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, Log);
				}
				FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					return SafeSetMappingInactive(Context, WorldContext, ControllerId, Tag, OutSuccess, Log);
				}

			#pragma endregion Tag
			};
		}
	}
}

using CsInputWithGameplayTagManagerLibrary = NCsInput::NWithGameplayTag::NManager::FLibrary;
using CsInputWithTagManagerLibrary = NCsInput::NWithGameplayTag::NManager::FLibrary;

namespace NCsInput
{
	namespace NWithGameplayTag
	{
		namespace NManager
		{	
			namespace NFirst
			{
				class CSINPUTWITHGAMEPLAYTAG_API FLibrary
				{
				private:

					CS_DECLARE_STATIC_LOG_LEVEL

					using InputManagerLibrary = NCsInput::NWithGameplayTag::NManager::FLibrary;

				// Get
				#pragma region
				public:

					FORCEINLINE static ICsManager_Input_WithGameplayTag* GetChecked(const FString& Context, const UObject* WorldContext)
					{
						return InputManagerLibrary::GetChecked(Context, WorldContext, 0);
					}

					FORCEINLINE static ICsManager_Input_WithGameplayTag* GetSafe(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::GetSafe(Context, WorldContext, 0, Log);
					}

					FORCEINLINE static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
					{
						return InputManagerLibrary::GetAsObjectChecked(Context, WorldContext, 0);
					}

				#pragma endregion Get

				public:

					FORCEINLINE static bool Exists(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::Exists(Context, WorldContext, 0, Log);
					}

				// Tag
				#pragma region
				public:

					// HasMapping

					FORCEINLINE static bool HasMappingChecked(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag)
					{
						return InputManagerLibrary::HasMappingChecked(Context, WorldContext, 0, Tag);
					}
					FORCEINLINE static bool HasMappingChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
					{
						return InputManagerLibrary::HasMappingChecked(Context, WorldContext, 0, Tag);
					}
					FORCEINLINE static bool HasMappingChecked(const FString& Context, const UObject* WorldContext, const FString& Tag)
					{
						return InputManagerLibrary::HasMappingChecked(Context, WorldContext, 0, Tag);
					}

					FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeHasMapping(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeHasMapping(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}
					FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeHasMapping(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeHasMapping(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}
					FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeHasMapping(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeHasMapping(const FString& Context, const UObject* WorldContext, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeHasMapping(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}

					// SetMappingActive

					FORCEINLINE static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag)
					{
						InputManagerLibrary::SetMappingActiveChecked(Context, WorldContext, 0, Tag);
					}
					FORCEINLINE static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
					{
						InputManagerLibrary::SetMappingActiveChecked(Context, WorldContext, 0, Tag);
					}
					FORCEINLINE static void SetMappingActiveChecked(const FString& Context, const UObject* WorldContext, const FString& Tag)
					{
						InputManagerLibrary::SetMappingActiveChecked(Context, WorldContext, 0, Tag);
					}

					FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeSetMappingActive(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeSetMappingActive(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}
					FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeSetMappingActive(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeSetMappingActive(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}
					FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeSetMappingActive(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeSetMappingActive(const FString& Context, const UObject* WorldContext, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeSetMappingActive(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}


					// SetMappingInactive

					FORCEINLINE static void SetMappingInactiveChecked(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag)
					{
						InputManagerLibrary::SetMappingInactiveChecked(Context, WorldContext, 0, Tag);
					}
					FORCEINLINE static void SetMappingInactiveChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
					{
						InputManagerLibrary::SetMappingInactiveChecked(Context, WorldContext, 0, Tag);
					}
					FORCEINLINE static void SetMappingInactiveChecked(const FString& Context, const UObject* WorldContext, const FString& Tag)
					{
						InputManagerLibrary::SetMappingInactiveChecked(Context, WorldContext, 0, Tag);
					}

					FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeSetMappingInactive(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeSetMappingInactive(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}
					FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeSetMappingInactive(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeSetMappingInactive(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}
					FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return InputManagerLibrary::SafeSetMappingInactive(Context, WorldContext, 0, Tag, Log);
					}
					FORCEINLINE static bool SafeSetMappingInactive(const FString& Context, const UObject* WorldContext, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						OutSuccess = SafeSetMappingInactive(Context, WorldContext, Tag, Log);
						return OutSuccess;
					}

					// BlockMapping

					FORCEINLINE static void BlockMappingChecked(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag)
					{
						SetMappingActiveChecked(Context, WorldContext, Tag);
					}
					FORCEINLINE static void BlockMappingChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
					{
						SetMappingActiveChecked(Context, WorldContext, Tag);
					}
					FORCEINLINE static void BlockMappingChecked(const FString& Context, const UObject* WorldContext, const FString& Tag)
					{
						SetMappingActiveChecked(Context, WorldContext, Tag);
					}

					FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return SafeSetMappingInactive(Context, WorldContext, Tag, Log);
					}
					FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const FGameplayTag& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return SafeSetMappingInactive(Context, WorldContext, Tag, OutSuccess, Log);
					}
					FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return SafeSetMappingInactive(Context, WorldContext, Tag, Log);
					}
					FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const FName& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return SafeSetMappingInactive(Context, WorldContext, Tag, OutSuccess, Log);
					}
					FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const FString& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return SafeSetMappingInactive(Context, WorldContext, Tag, Log);
					}
					FORCEINLINE static bool SafeBlockMapping(const FString& Context, const UObject* WorldContext, const FString& Tag, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
					{
						return SafeSetMappingInactive(Context, WorldContext, Tag, OutSuccess, Log);
					}

				#pragma endregion Tag
				};
			}
		}
	}
}

using CsFirstInputWithTagManagerLibrary = NCsInput::NWithGameplayTag::NManager::NFirst::FLibrary;