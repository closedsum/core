// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Game/SeamlessTransition/CsGameMode_SeamlessTransition_Delegates.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class UObject;
class ICsGameMode_SeamlessTransition;
class AActor;

namespace NCsGameMode
{
	namespace NSeamlessTransition
	{
		struct CSSEAMLESSTRANSITION_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

		// Interface
		#pragma region
		public:

			/**
			* Get the Interface: ICsGameMode_SeamlessTransition from the GameMode from WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static ICsGameMode_SeamlessTransition* GetInterfaceChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the Interface: ICsGameMode_SeamlessTransition GameMode from WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static ICsGameMode_SeamlessTransition* GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			* Safely get the Interface: ICsGameMode_SeamlessTransition GameMode from WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static ICsGameMode_SeamlessTransition* GetSafeInterface(const UObject* WorldContext);

		#pragma endregion Interface

		// Seamless  Travel
		#pragma region
		public:

			static void QueueForSeamlessTravelChecked(const FString& Context, const UObject* WorldContext, AActor* Actor);

			static bool SafeQueueForSeamlessTravel(const FString& Context, const UObject* WorldContext, AActor* Actor, LogLevel);
			FORCEINLINE static bool SafeQueueForSeamlessTravel(const FString& Context, const UObject* WorldContext, AActor* Actor, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeQueueForSeamlessTravel(Context, WorldContext, Actor, Log);
				return OutSuccess;
			}

			static void ClearQueueForSeamlessTravelChecked(const FString& Context, const UObject* WorldContext);

		#pragma endregion Seamless Travel

		// Event
		#pragma region
		public:

		#define OnPostSeamlessTravelCompleteEventType NCsGameMode::NSeamlessTravel::NPost::FOnComplete

			static OnPostSeamlessTravelCompleteEventType& GetPostSeamlessTravel_OnComplete_EventChecked(const FString& Context, const UObject* WorldContext);

		#undef OnPostSeamlessTravelCompleteEventType

		#pragma endregion Event

		#undef LogLevel
		};
	}
}