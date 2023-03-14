// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Coroutine
#include "Coroutine/CsRoutineHandle.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsCoroutineScheduler;

namespace NCsCoroutine
{
	namespace NScheduler
	{
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoroutineScheduler from a WorldContext.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoroutineScheduler from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoroutineScheduler from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsCoroutineScheduler from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoroutineScheduler.
			*/
			static UCsCoroutineScheduler* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get the reference to UCsCoroutineScheduler from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsCoroutineScheduler.
			*/
			static UCsCoroutineScheduler* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsCoroutineScheduler from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoroutineScheduler.
			*/
			static UCsCoroutineScheduler* GetSafe(const UObject* ContextObject);

		#pragma endregion Get
		
		// Update
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param DeltaTime
			*/
			static void UpdateChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime);

		#pragma endregion Update

		// End
		#pragma region
		public:

			/**
			* End the Handle running on update group: Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* return
			*/
			static bool EndChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle);

			/**
			* Safely end the Handle running on update group: Group. 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* @param Log			(optional)
			* return
			*/
			static bool SafeEnd(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely end the Handle running on update group: Group.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* return
			*/
			static bool SafeEnd(const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle);

			/**
			* Safely end all Handles with update group: Group.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* return
			*/
			static bool SafeEnd(const UObject* ContextObject, const FECsUpdateGroup& Group);

			/**
			* End the Handles running on update group: Group.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* return
			*/
			static bool EndChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const TArray<FCsRoutineHandle>& Handles);

			/**
			* End the Handle running on update group: Group
			* and Invalidate the Handle.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* return
			*/
			static bool EndAndInvalidateChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle);

			/**
			* Safely end the Handle running on update group: Group
			* and Invalidate the Handle.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* @param Log			(optional)
			* return
			*/
			static bool SafeEndAndInvalidate(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion End

		// Handle
		#pragma region
		public:

			/**
			* Check whether a Coroutine with the given Handle for Group is valid.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* return
			*/
			static bool IsHandleValidChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle);

			/**
			* Safely check whether a Coroutine with the given Handle for Group is valid.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* @param Log			(optional)
			* return
			*/
			static bool SafeIsHandleValid(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Check whether a Coroutine with the given Handle for Group is running.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* return
			*/
			static bool IsRunningChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle);

			/**
			* Safely check whether a Coroutine with the given Handle for Group is running.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Group
			* @param Handle
			* @param Log				(optional)
			* return
			*/
			static bool SafeIsRunning(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Handle
		};
	}
}