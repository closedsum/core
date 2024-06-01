// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsConsoleCommandLog.h"

class UObject;

namespace NCsConsoleCommand
{
	namespace NCoordinator
	{
		/**
		*/
		struct CSCONSOLECOMMAND_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsConsoleCommand::FLog::Warning

		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_ConsoleCommand from a WorldContext.
			* 
			* @param Context		The calling context.
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
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsCoordinator_ConsoleCommand.
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
			* Safely get the Context (Root) for UCsCoordinator_ConsoleCommand from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_ConsoleCommand.
			*/
			static UObject* GetSafeContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#undef LogLevel
		};
	}
}