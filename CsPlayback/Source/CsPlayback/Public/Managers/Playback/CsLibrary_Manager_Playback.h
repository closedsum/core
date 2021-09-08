// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Playback/CsTypes_Playback.h"
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
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject)
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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning)
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
			* Get the reference to UCsManager_Playback from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Playback.
			*/
			static UCsManager_Playback* GetChecked(const FString& Context, const UObject* ContextObject);

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
			static UCsManager_Playback* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);

		#pragma endregion Get

		// State
		#pragma region
		public:

		#define StateType NCsPlayback::EState

			/**
			* Set the Playback State
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param State
			*/
			static void SetPlaybackStateChecked(const FString& Context, const UObject* ContextObject, const StateType& State);

			/**
			* Get the Playback State
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				State
			*/

			static const StateType& GetPlaybackStateChecked(const FString& Context, const UObject* ContextObject);

		#undef StateType

		#pragma endregion State
		};

		namespace NPlayback
		{
			struct CSPLAYBACK_API FLibrary final
			{
			public:

				/**
				* Safely try to Play the latest Playback.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Log
				*/
				static void SafePlayLatest(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);

				/**
				* Safely check if the GameEvent is currently being Sustained (i.e. broadcasted every frame).
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Event			Game Event.
				* @param Log
				*/
				static bool IsSafeSustainedGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEvent& Event, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning);
			};
		}
	}
} 