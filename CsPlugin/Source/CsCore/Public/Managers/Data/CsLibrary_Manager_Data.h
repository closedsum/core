// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;

namespace NCsData
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Data from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Data
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Data from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Data
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString& Context) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString& Context) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Data from a WorldContext.
			*
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Data
			*/
			static UObject* GetSafeContextRoot(UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		};
	}
}