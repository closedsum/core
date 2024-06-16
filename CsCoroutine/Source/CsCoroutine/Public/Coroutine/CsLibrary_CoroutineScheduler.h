// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Coroutine
#include "Coroutine/CsRoutineHandle.h"
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Misc.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"
// Log
#include "Utility/CsCoroutineLog.h"

class UObject;
class UCsCoroutineScheduler;

// NCsCoroutine::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsCoroutine, NPayload, FImpl)

namespace NCsCoroutine
{
	namespace NScheduler
	{
		struct CSCOROUTINE_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsCoroutine::FLog::Warning

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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel) { return nullptr; }
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
			static UCsCoroutineScheduler* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

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
		
		// Default
		#pragma region

			// Start
		#pragma region
		public:

		#define PayloadType NCsCoroutine::NPayload::FImpl
			static const FCsRoutineHandle& StartChecked(const FString& Context, const UObject* ContextObject, PayloadType* Payload);
		#undef PayloadType
			
		#pragma endregion Start

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
			static bool SafeEnd(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, LogLevel);

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
			static bool SafeEndAndInvalidate(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle, LogLevel);

		#pragma endregion End

			// Payload
		#pragma region
		public:

		#define PayloadType NCsCoroutine::NPayload::FImpl
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup);
		#undef PayloadType

		#pragma endregion Payload

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
			static bool SafeIsHandleValid(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, LogLevel);

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
			static bool SafeIsRunning(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, LogLevel);

		#pragma endregion Handle

		#pragma endregion Default

		// Custom
		#pragma region
		public:

			static void AllocateCustomGroupIndexAndOwnerIdChecked(const FString& Context, const UObject* ContextObject, int32& OutGroupIndex, int32& OutOwnerID);

			static void DeallocateOwnerIdChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const int32& OwnerID);

			// Start
		#pragma region
		public:

		#define PayloadType NCsCoroutine::NPayload::FImpl
			static const FCsRoutineHandle& CustomStartChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const int32& OwnerID, PayloadType* Payload);
		#undef PayloadType
			
		#pragma endregion Start

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
			* @param GroupIndex
			* @param OwnerID
			* @param DeltaTime
			*/
			static void CustomUpdateChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const int32& OwnerID, const FCsDeltaTime& DeltaTime);

		#pragma endregion Update

			// End
		#pragma region
		public:

			/**
			* End the Handle running on update group: Custom and GroupIndex.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* return
			*/
			static bool CustomEndChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle);

			/**
			* Safely end the Handle running on update group: Custom and GroupIndex. 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* @param Log			(optional)
			* return
			*/
			static bool SafeCustomEnd(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle, LogLevel);

			/**
			* Safely end the Handle running on update group: Custom and GroupIndex.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* return
			*/
			static bool SafeCustomEnd(const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle);

			/**
			* End the Handles running on update group: Custom and GroupIndex.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* return
			*/
			static bool CustomEndChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const TArray<FCsRoutineHandle>& Handles);

			/**
			* End the Handle running on update group: Custom and GroupIndex
			* and Invalidate the Handle.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* return
			*/
			static bool CustomEndAndInvalidateChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, FCsRoutineHandle& Handle);

			/**
			* Safely end the Handle running on update group: Custom and GroupIndex
			* and Invalidate the Handle.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* @param Log			(optional)
			* return
			*/
			static bool SafeCustomEndAndInvalidate(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, FCsRoutineHandle& Handle, LogLevel);

		#pragma endregion End

			// Payload
		#pragma region
		public:

		#define PayloadType NCsCoroutine::NPayload::FImpl
			static PayloadType* AllocateCustomPayloadChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex);
		#undef PayloadType

		#pragma endregion Payload

			// Handle
		#pragma region
		public:

			/**
			* Check whether a Coroutine with the given Handle for Group: Custom and GroupIndex is valid.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* return
			*/
			static bool IsCustomHandleValidChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle);

			/**
			* Safely check whether a Coroutine with the given Handle for Group: Custom and GroupIndex is valid.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* @param Log			(optional)
			* return
			*/
			static bool SafeIsCustomHandleValid(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle, LogLevel);

			/**
			* Check whether a Coroutine with the given Handle for Group: Custom and GroupIndex is running.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* return
			*/
			static bool IsCustomRunningChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle);

			/**
			* Safely check whether a Coroutine with the given Handle for Group: Custom and GroupIndex is running.
			*
			* @param Context		The calling context
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param GroupIndex
			* @param Handle
			* @param Log				(optional)
			* return
			*/
			static bool SafeIsCustomRunning(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle, LogLevel);

		#pragma endregion Handle

		#pragma endregion Custom

		#undef LogLevel
		};
	}
}