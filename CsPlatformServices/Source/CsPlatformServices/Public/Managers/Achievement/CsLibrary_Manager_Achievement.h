// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Achievement/CsTypes_Achievement.h"
// Log
#include "Utility/CsPlatformServicesLog.h"

class UObject;
class UCsManager_Achievement;

namespace NCsAchievement
{
	namespace NManager
	{
		/**
		*/
		struct CSPLATFORMSERVICES_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Achievement from a ContextObject.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Achievement.
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
			* Safely get the Context (Root) for UCsManager_Achievement from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Achievement.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, LogLevel);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, LogLevel)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Achievement from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Achievement.
			*/
			static UObject* GetSafeContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Achievement from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Achievement.
			*/
			static UCsManager_Achievement* GetChecked(const FString& Context, UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Achievement from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Achievement.
			*/
			static UCsManager_Achievement* GetSafe(const FString& Context, UObject* ContextObject, LogLevel);

		#pragma endregion Get

		// Complete
		#pragma region
		public:

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			*/
			static void CompleteChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement);

			/**
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			* @param Log
			*/
			static void SafeComplete(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, LogLevel);

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			* return				If the Achievement is already complete.
			*/
			static bool IsCompletedChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement);

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			* @param Log
			* return				If the Achievement is already complete.
			*/
			static bool IsSafeCompleted(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, LogLevel);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Number of achievements already completed.
			*/
			static int32 GetNumCompletedChecked(const FString& Context, UObject* ContextObject);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Number of achievements already completed.
			*/
			static int32 GetSafeNumCompleted(const FString& Context, UObject* ContextObject, LogLevel);

		#pragma endregion Complete

		// Reset
		#pragma region
		public:

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			*/
			static void ResetChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, const float& Percent = 0.0f);

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			* @param Log
			*/
			static void SafeReset(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, const float& Percent = 0.0f, LogLevel);

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			*/
			static void ResetAllChecked(const FString& Context, UObject* ContextObject);

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			*/
			static void SafeResetAll(const FString& Context, UObject* ContextObject, LogLevel);

		#pragma endregion Reset

		// Progress
		#pragma region
		public:

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			* return				Progress completed. Value range is dictated by ProgressType.
			*/
			static float GetProgressChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Achievement
			* @param Log
			* return				Progress completed. Value range is dictated by ProgressType.
			*/
			static float GetSafeProgress(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, LogLevel);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Total progress completed [0-1] as a percent.
			*/
			static float GetTotalProgressChecked(const FString& Context, UObject* ContextObject);

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Total progress completed [0-1] as a percent.
			*/
			static float GetSafeTotalProgress(const FString& Context, UObject* ContextObject, LogLevel);

		#pragma endregion Progress

		#undef LogLevel
		};
	}
}