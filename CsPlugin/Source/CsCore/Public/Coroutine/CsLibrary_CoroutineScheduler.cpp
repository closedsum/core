// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsTypes_Macro.h"
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
#include "Managers/Singleton/CsGetManagerSingleton.h"
// Engine
#include "Engine/Engine.h"
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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, SafeEnd);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(ContextObject, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(ContextObject, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

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
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

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

		bool FLibrary::SafeEnd(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::SafeEnd;

			return SafeEnd(Context, ContextObject, Group, Handle, nullptr);
		}

		bool FLibrary::SafeEnd(const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::SafeEnd;

			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject, nullptr))
			{
				return Scheduler->End(Group);
			}
			return false;
		}

		bool FLibrary::EndAndInvalidateChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			const bool Result = GetChecked(Context, ContextObject)->End(Group, Handle);

			Handle.Invalidate();

			return Result;
		}

		bool FLibrary::SafeEndAndInvalidate(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, FCsRoutineHandle& Handle, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		// Handle
		#pragma region
		
		bool FLibrary::IsHandleValidChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			return GetChecked(Context, ContextObject)->IsHandleValid(Group, Handle);
		}

		bool FLibrary::SafeIsHandleValid(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		bool FLibrary::SafeIsRunning(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

			if (UCsCoroutineScheduler* Scheduler = GetSafe(Context, ContextObject))
			{
				return Scheduler->IsRunning(Group, Handle);
			}
			return false;
		}

		#pragma endregion Handle
	}
}