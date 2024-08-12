// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class AGameModeBase;
class UObject;

namespace NCsGameMode
{
	class CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static FString PrintGameModeAndClass(AGameModeBase* GameMode);

		/**
		* Get GameMode from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameMode
		*/
		static AGameModeBase* GetChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Get GameMode of type: T from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameMode
		*/
		template<typename T>
		static T* GetChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameModeBase* GameMode = GetChecked(Context, WorldContext);
			T* Other				  = Cast<T>(GameMode);

			checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintGameModeAndClass(GameMode), *(T::StaticClass()->GetName()));

			return Other;
		}

		/**
		* Safely get GameMode from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				GameMode
		*/
		static AGameModeBase* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

		/**
		* Safely get GameMode of type: T from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				GameMode
		*/
		template<typename T>
		static T* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			AGameModeBase* GameMode = GetSafe(Context, WorldContext, Log);

			if (!GameMode)
				return nullptr;

			T* GameModeT = Cast<T>(GameMode);

			if (!GameModeT)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintGameModeAndClass(GameMode), *(T::StaticClass()->GetName())));
			}
			return GameModeT;
		}

		/**
		* Safely get GameMode from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameMode
		*/
		static AGameModeBase* GetSafe(const UObject* WorldContext);

		/**
		* Get GameMode from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameMode
		*/
		static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get GameMode from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log
		* return				GameMode
		*/
		static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, LogLevel);

		/**
		* Safely get GameMode from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameMode
		*/
		static UObject* GetSafeAsObject(const UObject* WorldContext);

	#undef LogLevel
	};
}

using CsGameModeLibrary = NCsGameMode::FLibrary;