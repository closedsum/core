// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;

namespace NCsJs
{
	namespace NManager
	{
		struct CSJS_API FLibrary final
		{
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
			static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject) { return nullptr; }
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
			static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString& Context) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString& Context) = &FCsLog::Warning) { return nullptr; }
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
			static UObject* GetSafeContextRoot(UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

			static UObject* GetEngineContextRoot();
		};
	}
}