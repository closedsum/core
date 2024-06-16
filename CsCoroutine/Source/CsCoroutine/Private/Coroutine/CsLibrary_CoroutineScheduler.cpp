// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameInstance.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

namespace NCsCoroutine
{
	namespace NScheduler
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, GetContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, GetSafe);
					// Default
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, SafeEnd);
					// Custom
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, SafeCustomEnd);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsCoroutine::NScheduler::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsCoroutine::NScheduler::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsCoroutine::FLog::Warning*/
	#if WITH_EDITOR
		#define WorldLibrary NCsWorld::FLibrary
		#define GameInstanceLibrary NCsGameInstance::FLibrary
	#endif // #if WITH_EDITOR

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(ContextObject, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}

			if (ContextObject == GEngine)
				return GEngine;
			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(ContextObject, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}

			if (ContextObject == GEngine)
				return GEngine;
			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafeContextRoot);

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsCoroutineScheduler* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot			 = GetContextRootChecked(Context, ContextObject);
			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Scheduler)
			return Scheduler;
		}

		UCsCoroutineScheduler* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::GetSafe(Context, ContextRoot, Log);

			if (!Scheduler)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Scheduler."), *Context));
			}
			return Scheduler;
		}

		UCsCoroutineScheduler* FLibrary::GetSafe(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Default
		#pragma region

			// Start
		#pragma region

		#define PayloadType NCsCoroutine::NPayload::FImpl
		const FCsRoutineHandle& FLibrary::StartChecked(const FString& Context, const UObject* ContextObject, PayloadType* Payload)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			return GetChecked(Context, ContextObject)->Start(Payload);
		}
		#undef PayloadType
			
		#pragma endregion Start

			// Update
		#pragma region

		void FLibrary::UpdateChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			GetChecked(Context, ContextObject)->Update(Group, DeltaTime);
		}

		#pragma endregion Update

			// End
		#pragma region
		
		bool FLibrary::EndChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			return GetChecked(Context, ContextObject)->End(Group, Handle);
		}

		bool FLibrary::SafeEnd(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, LogLevel)
		{
			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

				return Scheduler->End(Group, Handle);
			}
			return false;
		}

		bool FLibrary::SafeEnd(const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
		{
			SET_CONTEXT(SafeEnd);

			return SafeEnd(Context, ContextObject, Group, Handle, nullptr);
		}

		bool FLibrary::SafeEnd(const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			SET_CONTEXT(SafeEnd);

			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject, nullptr))
			{
				return Scheduler->End(Group);
			}
			return false;
		}

		bool FLibrary::EndChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const TArray<FCsRoutineHandle>& Handles)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			bool Result = true;

			for (const FCsRoutineHandle& Handle : Handles)
			{
				Result &= GetChecked(Context, ContextObject)->End(Group, Handle);
			}
			return Result;
		}

		bool FLibrary::EndAndInvalidateChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			const bool Result = GetChecked(Context, ContextObject)->End(Group, Handle);

			Handle.Invalidate();
			return Result;
		}

		bool FLibrary::SafeEndAndInvalidate(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle, LogLevel)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject, Log))
			{
				const bool Result = Scheduler->End(Group, Handle);

				Handle.Invalidate();

				return Result;
			}
			Handle.Invalidate();
			return false;	
		}

		#pragma endregion End

			// Payload
		#pragma region
		
		#define PayloadType NCsCoroutine::NPayload::FImpl
		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup)

			return GetChecked(Context, ContextObject)->AllocatePayload(UpdateGroup);
		}
		#undef PayloadType

		#pragma endregion Payload

			// Handle
		#pragma region
		
		bool FLibrary::IsHandleValidChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			return GetChecked(Context, ContextObject)->IsHandleValid(Group, Handle);
		}

		bool FLibrary::SafeIsHandleValid(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, LogLevel)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject))
			{
				return Scheduler->IsHandleValid(Group, Handle);
			}
			return false;
		}

		bool FLibrary::IsRunningChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			return GetChecked(Context, ContextObject)->IsRunning(Group, Handle);
		}

		bool FLibrary::SafeIsRunning(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, LogLevel)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject))
			{
				return Scheduler->IsRunning(Group, Handle);
			}
			return false;
		}

		#pragma endregion Handle

		#pragma endregion Default

		// Custom
		#pragma region

		void FLibrary::AllocateCustomGroupIndexAndOwnerIdChecked(const FString& Context, const UObject* ContextObject, int32& OutGroupIndex, int32& OutOwnerID)
		{
			GetChecked(Context, ContextObject)->AllocateCustomGroupIndexAndOwnerID(OutGroupIndex, OutOwnerID);
		}

		void FLibrary::DeallocateOwnerIdChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const int32& OwnerID)
		{
			GetChecked(Context, ContextObject)->DeallocateOwnerID(GroupIndex, OwnerID);
		}

			// Start
		#pragma region

		#define PayloadType NCsCoroutine::NPayload::FImpl
		const FCsRoutineHandle& FLibrary::CustomStartChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const int32& OwnerID, PayloadType* Payload)
		{
			return GetChecked(Context, ContextObject)->CustomStart(GroupIndex, OwnerID, Payload);
		}
		#undef PayloadType
			
		#pragma endregion Start

			// Update
		#pragma region

		void FLibrary::CustomUpdateChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const int32& OwnerID, const FCsDeltaTime& DeltaTime)
		{
			GetChecked(Context, ContextObject)->CustomUpdate(GroupIndex, OwnerID, DeltaTime);
		}

		#pragma endregion Update

			// End
		#pragma region
	
		bool FLibrary::CustomEndChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle)
		{
			return GetChecked(Context, ContextObject)->CustomEnd(GroupIndex, Handle);
		}

		bool FLibrary::SafeCustomEnd(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle, LogLevel)
		{
			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject, Log))
			{
				if (Scheduler->IsValidGroupIndex(Context, GroupIndex, Log))
					return Scheduler->CustomEnd(GroupIndex, Handle);
			}
			return false;
		}

		bool FLibrary::SafeCustomEnd(const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle)
		{
			SET_CONTEXT(SafeCustomEnd);

			return SafeCustomEnd(Context, ContextObject, GroupIndex, Handle);
		}

		bool FLibrary::CustomEndChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const TArray<FCsRoutineHandle>& Handles)
		{
			bool Result = true;

			for (const FCsRoutineHandle& Handle : Handles)
			{
				Result &= GetChecked(Context, ContextObject)->CustomEnd(GroupIndex, Handle);
			}
			return Result;
		}

		bool FLibrary::CustomEndAndInvalidateChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, FCsRoutineHandle& Handle)
		{
			const bool Result = GetChecked(Context, ContextObject)->CustomEnd(GroupIndex, Handle);

			Handle.Invalidate();
			return Result;
		}

		bool FLibrary::SafeCustomEndAndInvalidate(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, FCsRoutineHandle& Handle, LogLevel)
		{
			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject, Log))
			{
				if (Scheduler->IsValidGroupIndex(Context, GroupIndex, Log))
				{
					const bool Result = Scheduler->CustomEnd(GroupIndex, Handle);

					Handle.Invalidate();
					return Result;
				}
			}
			Handle.Invalidate();
			return false;
		}

		#pragma endregion End

			// Payload
		#pragma region

		#define PayloadType NCsCoroutine::NPayload::FImpl
		PayloadType* FLibrary::AllocateCustomPayloadChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex)
		{	
			return GetChecked(Context, ContextObject)->AllocateCustomPayload(GroupIndex);
		}
		#undef PayloadType

		#pragma endregion Payload

			// Handle
		#pragma region

		bool FLibrary::IsCustomHandleValidChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle)
		{
			return GetChecked(Context, ContextObject)->IsCustomHandleValid(GroupIndex, Handle);
		}

		bool FLibrary::SafeIsCustomHandleValid(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle, LogLevel)
		{
			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject))
			{
				if (Scheduler->IsValidGroupIndex(Context, GroupIndex, Log))
					return Scheduler->IsCustomHandleValid(GroupIndex, Handle);
			}
			return false;
		}

		bool FLibrary::IsCustomRunningChecked(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle)
		{
			return GetChecked(Context, ContextObject)->IsCustomRunning(GroupIndex, Handle);
		}

		bool FLibrary::SafeIsCustomRunning(const FString& Context, const UObject* ContextObject, const int32& GroupIndex, const FCsRoutineHandle& Handle, LogLevel)
		{
			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject))
			{
				if (Scheduler->IsValidGroupIndex(Context, GroupIndex, Log))
					return Scheduler->IsCustomRunning(GroupIndex, Handle);
			}
			return false;
		}

		#pragma endregion Handle

		#pragma endregion Custom

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	#if WITH_EDITOR
		#undef WorldLibrary
		#undef GameInstanceLibrary
	#endif // #if WITH_EDITOR
	}
}