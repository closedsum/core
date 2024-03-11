// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Game/CsGameInstance_Delegates.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UEngine;
class UGameInstance;
class UCsGameInstance;

namespace NCsGameInstance
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetSafe;
				extern CSCORE_API const FString GetSafeAsObject;
				extern CSCORE_API const FString IsSafe;
			}
		}
	}

	class CSCORE_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &FCsLog::Warning

	public:

		static FString PrintObjectAndClass(const UGameInstance* Object);

		static FString PrintNameAndClass(const UGameInstance* Object);

	// Get
	#pragma region
	public:

		/**
		* Get GameInstance from ContextObject.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UGameInstance* GetChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Get GameInstance from ContextObject.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		template<typename T>
		static T* GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UGameInstance* O = GetChecked(Context, ContextObject);
			T* Other		 = Cast<T>(O);

			checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintNameAndClass(O), *(T::StaticClass()->GetName()));
			return Other;
		}

		/**
		* Safely get GameInstance from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		static UGameInstance* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely get GameInstance from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		template<typename T>
		static T* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			UGameInstance* O = GetSafe(Context, ContextObject, Log);

			if (!O)
				return nullptr;

			T* Other = Cast<T>(O);

			if (!Other)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintNameAndClass(O), *(T::StaticClass()->GetName())));
			}
			return Other;
		}

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UGameInstance* GetSafe(const UObject* ContextObject);

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		template<typename T>
		static T* GetSafe(const UObject* ContextObject)
		{
			using namespace NCsGameInstance::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe<T>(Context, ContextObject, nullptr);
		}

	// NOTE: MAYBE: FUTURE: Get version should return the UCsGameInstance version.

		/**
		* Get GameInstance from ContextObject.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UCsGameInstance* GetCsChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely get GameInstance from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		static UCsGameInstance* GetCsSafe(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UCsGameInstance* GetCsSafe(const UObject* ContextObject);

		/**
		* Get GameInstance from ContextObject.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UObject* GetAsObjectChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely get GameInstance from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		static UObject* GetSafeAsObject(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UObject* GetSafeAsObject(const UObject* ContextObject);

	#pragma endregion Get

	// Is
	#pragma region
	public:

		/**
		* Check if the ContextObject is of type: UGameInstance
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return
		*/
		static bool IsChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely check if the ContextObject is of type: UGameInstance
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log			(optional)
		* return
		*/
		static bool IsSafe(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely check if the ContextObject is of type: UGameInstance
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return
		*/
		static bool IsSafe(const UObject* ContextObject);

		FORCEINLINE static bool SafeIsReachable(const UObject* ContextObject)
		{
			return GetSafe(ContextObject) != nullptr;
		}

	#pragma endregion Is

	// Engine
	#pragma endregion
	public:

		static UEngine* GetEngineChecked(const FString& Context, const UObject* ContextObject);

		static UEngine* GetSafeEngine(const FString& Context, const UObject* ContextObject, LogLevel);

	#pragma endregion Engine

	// Start
	#pragma region
	public:

		static bool HasStartedFromEntryChecked(const FString& Context, const UObject* ContextObject);

		static bool SafeHasStartedFromEntry(const FString& Context, const UObject* ContextObject, LogLevel);

	#pragma endregion Start

	// Editor
	#pragma region
	public:

		/**
		* Check if the instance currently running is PIE.
		* NOTE: Assumes the GameInstance is of type: UCsGameInstance.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is PIE.
		*/
		static bool IsPIEChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Check if the instance currently running is simulating Mobile Preview in PIE.
		* NOTE: Assumes the GameInstance is of type: UCsGameInstance.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is simulating Mobile Preview in PIE.
		*/
		static bool IsMobilePIEChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Check if the instance currently running is Standalone from Editor.
		* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is Standalone from Editor.
		*/
		static bool IsStandaloneFromEditorChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Check if the instance currently running is Standalone Mobile from Editor.
		* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is Standalone Mobile from Editor.
		*/
		static bool IsStandaloneMobileFromEditorChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Check if the instance currently running is a Mobile Preview with Editor (WITH_EDITOR == 1).
		* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is a Mobile Preview with Editor.
		*/
		static bool IsMobilePreviewEditorChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely check if the instance currently running is a Mobile Preview with Editor (WITH_EDITOR == 1).
		* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log			(optional)
		* return				Whether the instance running is a Mobile Preview with Editor.
		*/
		static bool SafeIsMobilePreviewEditor(const FString& Context, const UObject* ContextObject, LogLevel);

	#pragma endregion Editor

	// Transition
	#pragma region
	public:

		static bool HasFinishedTransitionChecked(const FString& Context, const UObject* ContextObject);

	#pragma endregion Transition

	// Events
	#pragma region
	public:

	#define OnQueueExitGameEventType NCsGameInstance::FOnQueueExitGame
		static OnQueueExitGameEventType& GetOnQueueExitGame_EventChecked(const FString& Context, const UObject* ContextObject);
	#undef OnQueueExitGameEventType

		// Transition
	#pragma region
	public:

	#define OnStartTransitionOutEventType NCsGameInstance::NTransition::FOut_OnStart
	#define OnFinishTransitionEventType NCsGameInstance::NTransition::FOnFinish

		static OnStartTransitionOutEventType& GetTransitionOut_OnStart_EventChecked(const FString& Context, const UObject* ContextObject);
		static OnFinishTransitionEventType& GetTransition_OnFinish_EventChecked(const FString& Context, const UObject* ContextObject);

	#undef OnStartTransitionOutEventType
	#undef OnFinishTransitionEventType

	#pragma endregion Transition

	#pragma endregion Events

	#undef LogLevel
	};
}