// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Achievement/CsTypes_Achievement.h"
// Log
#include "Utility/CsLog.h"

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
			static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
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
			static UCsManager_Achievement* GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Get

		// Complete
		#pragma region
		public:

			/**
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Achievement
			*/
			static void SafeComplete(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Achievement
			* return				If the Achievement is already complete.
			*/
			static bool SafeIsCompleted(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			*
			* @param Context			The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Number of achievements already completed.
			*/
			static int32 GetSafeNumCompleted(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Complete
		};
	}
}