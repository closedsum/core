// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsLibrary_Manager_Time.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Game
#include "Engine/GameInstance.h"
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

namespace NCsTime
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FLibrary, GetSafe);
				}
			}
		}

		#define WorldLibrary NCsWorld::FLibrary
		#define GameInstanceLibrary NCsGameInstance::FLibrary

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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
			using namespace NCsTime::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Time* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Time)
			return Manager_Time;
		}

		UCsManager_Time* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Time* Manager_Time = UCsManager_Time::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Time)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Time."), *Context));
			}
			return Manager_Time;
		}

		UCsManager_Time* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsTime::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Pause
		#pragma region

		void FLibrary::PauseChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			GetChecked(Context, ContextObject)->Pause(Group);
		}

		bool FLibrary::SafePause(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				if (Manager_Time->IsPaused(Group))
					return false;

				Manager_Time->Pause(Group);
				return true;
			}
			return false;
		}

		void FLibrary::UnpauseChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			GetChecked(Context, ContextObject)->Unpause(Group);
		}

		bool FLibrary::SafeUnpause(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				if (!Manager_Time->IsPaused(Group))
					return false;

				Manager_Time->Unpause(Group);
				return true;
			}
			return false;
		}

		#pragma endregion Pause

		// Update
		#pragma region
	
		void FLibrary::SetSafeCustomUpdate(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime, const bool& ClearOnUpdate, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsUpdateGroup, FECsUpdateGroup, Group)

			CS_IS_FLOAT_GREATER_THAN_EXIT(DeltaTime, 0.0f)

			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				Manager_Time->SetCustom(Group, ClearOnUpdate);
				Manager_Time->SetCustomDeltaTime(Group, FCsDeltaTime(DeltaTime));
			}
		}

		#pragma endregion Update

		// Time
		#pragma region

		void FLibrary::UpdateTimeAndCoroutineScheduler(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime)
		{
			UCsManager_Time* Manager_Time = GetChecked(Context, ContextObject);

			Manager_Time->Update(Group, DeltaTime);

			const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// Update CoroutineScheduler
			typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

			CoroutineSchedulerLibrary::UpdateChecked(Context, ContextObject, Group, ScaledDeltaTime);
		}

		const FCsTime& FLibrary::GetTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			return GetChecked(Context, ContextObject)->GetTime(Group);
		}

		const FCsTime& FLibrary::GetSafeTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_STRUCT_VALID_RET_VALUE(EMCsUpdateGroup, FECsUpdateGroup, Group, FCsTime::Zero)

				return Manager_Time->GetTime(Group);
			}
			return FCsTime::Zero;
		}

		const FCsDeltaTime& FLibrary::GetTimeSinceStartChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			return GetChecked(Context, ContextObject)->GetTimeSinceStart(Group);
		}

		const FCsDeltaTime& FLibrary::GetSafeTimeSinceStart(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_STRUCT_VALID_RET_VALUE(EMCsUpdateGroup, FECsUpdateGroup, Group, FCsDeltaTime::Zero)

				return Manager_Time->GetTimeSinceStart(Group);
			}
			return FCsDeltaTime::Zero;
		}

		void FLibrary::SetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale)
		{
			GetChecked(Context, ContextObject)->SetScaledDeltaTime(Group, Scale);
		}

		void FLibrary::SetScaledDeltaTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)
			CS_IS_FLOAT_GREATER_THAN_CHECKED(Scale, 0.0f)

			GetChecked(Context, ContextObject)->SetScaledDeltaTime(Group, Scale);
		}

		bool FLibrary::SetSafeScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
				CS_IS_FLOAT_GREATER_THAN(Scale, 0.0f)

				Manager_Time->SetScaledDeltaTime(Group, Scale);
				return true;
			}
			return false;
		}

		const FCsDeltaTime& FLibrary::GetScaledDeltaTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			return GetChecked(Context, ContextObject)->GetScaledDeltaTime(Group);
		}

		void FLibrary::ResetScaledDeltaTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)

			GetChecked(Context, ContextObject)->ResetScaledDeltaTime(Group);
		}

		bool FLibrary::SafeResetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)

				Manager_Time->ResetScaledDeltaTime(Group);
				return true;
			}
			return false;
		}

		void FLibrary::ResetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			GetChecked(Context, ContextObject)->ResetScaledDeltaTime(Group);
		}

		#pragma endregion Time

		// Events
		#pragma region

		#define OnUpdateEventType NCsTime::NManager::FOnUpdate
		#define OnSetScaledDeltaTimeEventType NCsTime::NManager::FOnSetScaledDeltaTime
		#define OnResetScaledDeltaTimeEventType NCsTime::NManager::FOnResetScaledDeltaTime

		OnUpdateEventType& FLibrary::GetChecked_OnUpdate_Event(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetOnUpdate_Event();
		}

		OnSetScaledDeltaTimeEventType& FLibrary::GetChecked_OnSetScaledDeltaTime_Event(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetOnSetScaledDeltaTime_Event();
		}

		OnResetScaledDeltaTimeEventType& FLibrary::GetChecked_OnResetScaledDeltaTime_Event(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetOnResetScaledDeltaTime_Event();
		}

		#undef OnUpdateEventType
		#undef OnSetScaledDeltaTimeEventType
		#undef OnResetScaledDeltaTimeEventType

		#pragma endregion Events

		#undef WorldLibrary
		#undef GameInstanceLibrary
	}
}