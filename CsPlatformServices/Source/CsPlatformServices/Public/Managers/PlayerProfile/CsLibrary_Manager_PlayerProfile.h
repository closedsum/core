// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
// Log
#include "Utility/CsPlatformServicesLog.h"

class UObject;
class UCsManager_PlayerProfile;

namespace NCsPlayer
{
	namespace NProfile
	{
		namespace NManager
		{
			/**
			*/
			struct CSPLATFORMSERVICES_API FLibrary final
			{

			// ContextRoot
			#pragma region
			public:

			#if WITH_EDITOR
				/**
				* Get the Context (Root) for UCsManager_PlayerProfile from a ContextObject.
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				Context for UCsManager_PlayerProfile.
				*/
				static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
			#else
				FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject)
				{
					return nullptr;
				}
			#endif // #if WITH_EDITOR

			#if WITH_EDITOR
				/**
				* Safely get the Context (Root) for UCsManager_PlayerProfile from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Log			(optional)
				* return				Context for UCsManager_PlayerProfile.
				*/
				static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			#else
				FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
				{
					return nullptr;
				}
			#endif // #if WITH_EDITOR

			#if WITH_EDITOR
				/**
				* Safely get the Context (Root) for UCsManager_PlayerProfile from a ContextObject.
				*
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				Context for UCsManager_PlayerProfile.
				*/
				static UObject* GetSafeContextRoot(const UObject* ContextObject);
			#else
				FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject)
				{
					return nullptr;
				}
			#endif // #if WITH_EDITOR

			#pragma endregion ContextRoot

			// Get
			#pragma region
			public:

				/**
				* Get the reference to UCsManager_PlayerProfile from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				UCsManager_PlayerProfile.
				*/
				static UCsManager_PlayerProfile* GetChecked(const FString& Context, const UObject* ContextObject);

				/**
				* Safely get the reference to UCsManager_PlayerProfile from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Log			(optional)
				* return				UCsManager_PlayerProfile.
				*/
				static UCsManager_PlayerProfile* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);

			#pragma endregion Get

			public:

				/**
				* Set current active profile. 
				* Active profile is used by the Manager_Save to determine which Save (slot) to save to.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param ProfileType	Profile to set as the active profile.
				*/
				static void SetCurrentActiveProfileChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& ProfileType);

				/**
				* Safely set current active profile.
				* Active profile is used by the Manager_Save to determine which Save (slot) to save to.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param ProfileType	Profile to set as the active profile.
				* @param Log			(optional)
				* return
				*/
				static bool SetSafeCurrentActiveProfile(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& ProfileType, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			};
		}
	}
} 