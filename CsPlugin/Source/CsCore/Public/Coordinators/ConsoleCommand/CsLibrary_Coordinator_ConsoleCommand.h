// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsConsoleCommand
{
	namespace NCoordinator
	{
		/**
		*/
		struct CSCORE_API FLibrary final
		{
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_ConsoleCommand from a WorldContext.
			* 
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_ConsoleCommand.
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoordinator_ConsoleCommand from a WorldContext.
			*
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_ConsoleCommand.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR
		};
	}
}