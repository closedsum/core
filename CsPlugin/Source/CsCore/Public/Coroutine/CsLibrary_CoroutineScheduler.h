// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.


#pragma once

class UObject;

namespace NCsCoroutine
{
	namespace NScheduler
	{
		struct CSCORE_API FLibrary final
		{
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRoot(UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetSafeContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR
		};
	}
}