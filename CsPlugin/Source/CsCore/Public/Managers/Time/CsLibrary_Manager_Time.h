// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsManager_Time_Delegates.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UCsManager_Time;

namespace NCsTime
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Time from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Time
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Time from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Time
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Time from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Time
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Time from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Time.
			*/
			static UCsManager_Time* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Time from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Time.
			*/
			static UCsManager_Time* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Time from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Time.
			*/
			static UCsManager_Time* GetSafe(const UObject* ContextObject);

		#pragma endregion Get

		// Pause
		#pragma region
		public:

			/**
			* Pause the update of Group.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group			
			*/
			static void PauseChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			* Safely pause the update of Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Log			(optional)
			* return				Whether the pause was successfully executed or not.
			*/
			static bool SafePause(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SafePause(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SafePause(Context, ContextObject, Group, Log);
				return OutSuccess;
			}

			/**
			* Unpause the update of Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			*/
			static void UnpauseChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			* Safely unpause the update of Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Log			(optional)
			* return				Whether the unpause was successfully executed or not.
			*/
			static bool SafeUnpause(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SafeUnpause(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SafeUnpause(Context, ContextObject, Group, Log);
				return OutSuccess;
			}

		#pragma endregion Pause

		// Update
		#pragma region
		public:

			/**
			* Set the update for Group to Custom for DeltaTime. The next update for Group will "tick" with DeltaTime.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param DeltaTime
			* @param ClearOnUpdate	Whether to Clear the Custom flag after calling Update.
			*/
			static void SetSafeCustomUpdate(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime, const bool& ClearOnUpdate, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Update

		// Time
		#pragma region
		public:

			/**
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param DeltaTime
			*/
			static void UpdateTimeAndCoroutineScheduler(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime);

			/**
			* Get the Current Time for Group (this takes into account Paused Time).
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* return
			*/
			static const FCsTime& GetTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			* Get the Current Time for Group (this takes into account Paused Time).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Log			(optional)
			* return
			*/
			static const FCsTime& GetSafeTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* return
			*/
			static const FCsDeltaTime& GetTimeSinceStartChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Log			(optional)
			* return
			*/
			static const FCsDeltaTime& GetSafeTimeSinceStart(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Scale
			*/
			static void SetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Scale
			*/
			static void SetScaledDeltaTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Scale
			* @param Log			(optional)
			* return
			*/
			static bool SetSafeScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* return				scaled DeltaTime.
			*/
			static const FCsDeltaTime& GetScaledDeltaTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			* Resets the Scale (to 1.0f) applied to the delta time for the specified Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			*/
			static void ResetScaledDeltaTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			* Resets the Scale (to 1.0f) applied to the delta time for the specified Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Log			(optional)
			* return
			*/
			static bool SafeResetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Resets the Scale (to 1.0f) applied to the delta time for the specified Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Group
			*/
			static void ResetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group);

		#pragma endregion Time

		// Events
		#pragma region
		public:

		#define OnUpdateEventType NCsTime::NManager::FOnUpdate
		#define OnSetScaledDeltaTimeEventType NCsTime::NManager::FOnSetScaledDeltaTime
		#define OnResetScaledDeltaTimeEventType NCsTime::NManager::FOnResetScaledDeltaTime

			static OnUpdateEventType& GetChecked_OnUpdate_Event(const FString& Context, const UObject* ContextObject);

			static OnSetScaledDeltaTimeEventType& GetChecked_OnSetScaledDeltaTime_Event(const FString& Context, const UObject* ContextObject);

			static OnResetScaledDeltaTimeEventType& GetChecked_OnResetScaledDeltaTime_Event(const FString& Context, const UObject* ContextObject);

		#undef OnUpdateEventType
		#undef OnSetScaledDeltaTimeEventType
		#undef OnResetScaledDeltaTimeEventType

		#pragma endregion Events
		};
	}
}