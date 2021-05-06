// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsCoroutineScheduler;

namespace NCsCoroutine
{
	namespace NScheduler
	{
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetSafeContextRoot(UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsCoroutineScheduler from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoroutineScheduler.
			*/
			static UCsCoroutineScheduler* GetChecked(const FString& Context, UObject* ContextObject);

			/**
			* Safely get the reference to UCsCoroutineScheduler from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsCoroutineScheduler.
			*/
			static UCsCoroutineScheduler* GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Time from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Time.
			*/
			static UCsCoroutineScheduler* GetSafe(UObject* ContextObject);

		#pragma endregion Get
		};
	}
}