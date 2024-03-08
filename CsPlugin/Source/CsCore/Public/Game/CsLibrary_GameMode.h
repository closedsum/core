// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Game/CsGameMode_Delegates.h"
// Log
#include "Utility/CsLog.h"

class AGameModeBase;
class UObject;

namespace NCsGameMode
{
	class CSCORE_API FLibrary final
	{
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
		static AGameModeBase* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get GameMode of type: T from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				GameMode
		*/
		template<typename T>
		static T* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
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
		static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get GameMode from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				GameMode
		*/
		static UObject* GetSafeAsObject(const UObject* WorldContext);

	// ICsGameMode_Event
	#pragma region
	public:

	#define OnPostSeamlessTravelCompleteEventType NCsGameMode::NSeamlessTravel::NPost::FOnComplete

		static OnPostSeamlessTravelCompleteEventType& GetPostSeamlessTravel_OnComplete_EventChecked(const FString& Context, const UObject* WorldContext);

	#undef OnPostSeamlessTravelCompleteEventType

	#pragma endregion ICsGameMode_Event
	};
}