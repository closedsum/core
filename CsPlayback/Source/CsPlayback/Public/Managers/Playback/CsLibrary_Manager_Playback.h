// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsPlaybackLog.h"

class UObject;
class UCsManager_Playback;

namespace NCsPlayback
{
	namespace NManager
	{
		/**
		*/
		struct CSPLAYBACK_API FLibrary final
		{

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Playback from a ContextObject.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Playback.
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Playback from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Playback.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Playback from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Playback.
			*/
			static UObject* GetSafeContextRoot(UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* ContextObject)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Playback from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Playback.
			*/
			static UCsManager_Playback* GetChecked(const FString& Context, UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Playback from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Playback.
			*/
			static UCsManager_Playback* GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);

		#pragma endregion Get

		// Playback
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			*/
			static void SafePlayLatest(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);

		#pragma endregion Playback
		};
	}
} 