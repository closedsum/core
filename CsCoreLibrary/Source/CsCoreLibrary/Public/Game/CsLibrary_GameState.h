// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class AGameStateBase;
class UObject;

namespace NCsGameState
{
	class CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static FString PrintGameStateAndClass(AGameStateBase* GameState);

		/**
		* Get GameState from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static AGameStateBase* GetChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Get GameState of type: T from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		template<typename T>
		static T* GetChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameStateBase* GameState = GetChecked(Context, WorldContext);
			T* Other				  = Cast<T>(GameState);

			checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintGameStateAndClass(GameState), *(T::StaticClass()->GetName()));
			return Other;
		}

		/**
		* Safely get GameState from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				GameState
		*/
		static AGameStateBase* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

		/**
		* Safely get GameState of type: T from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				GameState
		*/
		template<typename T>
		static T* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			AGameStateBase* GameState = GetSafe(Context, WorldContext, Log);

			if (!GameState)
				return nullptr;

			T* GameStateT = Cast<T>(GameState);

			if (!GameStateT)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintGameStateAndClass(GameState), *(T::StaticClass()->GetName())));
			}
			return GameStateT;
		}

		/**
		* Safely get GameState from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static AGameStateBase* GetSafe(const UObject* WorldContext);

		/**
		* Get GameState from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get GameState from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log
		* return				GameState
		*/
		static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, LogLevel);

		/**
		* Safely get GameState from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameState
		*/
		static UObject* GetSafeAsObject(const UObject* WorldContext);

	#undef LogLevel
	};
}