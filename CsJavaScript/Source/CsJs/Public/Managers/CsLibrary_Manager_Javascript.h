// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsJsLog.h"

class UObject;
class UCsManager_Javascript;

namespace NCsJs
{
	namespace NManager
	{
		struct CSJS_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString& Context) = &NCsJs::FLog::Warning

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Javascript from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Javascript
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR
		
		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Javascript from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Javascript
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Javascript from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Javascript
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

			static UObject* GetEngineContextRoot();

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Javascript from a WorldContext.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Javascript.
			*/
			static UCsManager_Javascript* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Javascript from a WorldContext.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Javascript.
			*/
			static UCsManager_Javascript* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

			/**
			* Safely get the reference to UCsManager_Javascript from a WorldContext.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Javascript.
			*/
			static UCsManager_Javascript* GetSafe(const UObject* ContextObject);

		#pragma endregion Get

		#undef LogLevel
		};
	}
}

using CsJavascriptManagerLibrary = NCsJs::NManager::FLibrary;