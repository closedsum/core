// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/CsLibrary_Coordinator_GameplayTag.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Coordinators
#include "Coordinators/GameplayTag/CsCoordinator_GameplayTag.h"
// Settings
#include "Coordinators/GameplayTag/CsSettings_Coordinator_GameplayTag.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsGameplayTag
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCoordinator::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCoordinator::FLibrary, GetSafeContextRoot);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsGameplayTag::NCoordinator::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameplayTag::NCoordinator::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsGameplayTags::FLog::Warning*/

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			return CsGameInstanceLibrary::GetSafe(Context, ContextObject, Log);
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

		UCsCoordinator_GameplayTag* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot						        = GetContextRootChecked(Context, ContextObject);
			UCsCoordinator_GameplayTag* Coordinator_GameplayTag = UCsCoordinator_GameplayTag::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Coordinator_GameplayTag)
			return Coordinator_GameplayTag;
		}

		UCsCoordinator_GameplayTag* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoordinator_GameplayTag* Coordinator_GameplayTag = UCsCoordinator_GameplayTag::Get(ContextRoot);

			if (!Coordinator_GameplayTag)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Coordinator_GameplayTag."), *Context));
				return nullptr;
			}
			return Coordinator_GameplayTag;
		}

		UCsCoordinator_GameplayTag* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoordinator_GameplayTag* Coordinator_GameplayTag = UCsCoordinator_GameplayTag::Get(ContextRoot);

			if (!Coordinator_GameplayTag)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Coordinator_GameplayTag."), *Context));
				return nullptr;
			}

			OutSuccess = true;
			return Coordinator_GameplayTag;
		}

		#pragma endregion Get

		// Class
		#pragma region
		
		TSubclassOf<UCsCoordinator_GameplayTag> FLibrary::GetClassChecked(const FString& Context)
		{
			const FCsSettings_Coordinator_GameplayTag& Settings = FCsSettings_Coordinator_GameplayTag::Get();

			return TSubclassOf<UCsCoordinator_GameplayTag>(Settings.LoadClassChecked(Context));
		}

		#pragma endregion Class

		// StartPlay
		#pragma region

		void FLibrary::StartPlayChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->StartPlay();
		}

		#pragma endregion StartPlay

		// Event
		#pragma region

		void FLibrary::ProcessGameplayTagEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameplayTagCoordinatorGroup, Group)
			CS_IS_VALID_CHECKED(Event);

			// If Group == None, Process Immediately
			if (Group == NCsGameplayTagCoordinatorGroup::None)
			{
				GetChecked(Context, ContextObject)->ProcessGameplayTagEvent(Group, Event);
			}
			else
			{
				GetChecked(Context, ContextObject)->ProcessGameplayTagEvent(Group, Event);
			}
		}

		bool FLibrary::SafeProcessGameplayTagEvent(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event, LogLevel)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsGameplayTagCoordinatorGroup, FECsGameplayTagCoordinatorGroup, Group)
			CS_IS_VALID(Event)

			if (UCsCoordinator_GameplayTag* Coordinator_GameplayTag = GetSafe(Context, ContextObject, Log))
			{ 
				// If Group == None, Process Immediately
				if (Group == NCsGameplayTagCoordinatorGroup::None)
				{
					Coordinator_GameplayTag->ProcessGameplayTagEvent(Group, Event);
				}
				else
				{
					Coordinator_GameplayTag->ProcessGameplayTagEvent(Group, Event);
				}
				return true;
			}
			return false;
		}

		void FLibrary::BroadcastGameplayTagEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const  FCsGameplayTagEvent& Event)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameplayTagCoordinatorGroup, Group)
			CS_IS_VALID_CHECKED(Event);

			// If Group == None, Process Immediately
			if (Group == NCsGameplayTagCoordinatorGroup::None)
			{
				GetChecked(Context, ContextObject)->ProcessGameplayTagEvent(Group, Event);
			}
			else
			{
				GetChecked(Context, ContextObject)->ProcessGameplayTagEvent(Group, Event);
			}
		}

		bool FLibrary::SafeBroadcastGameplayTagEvent(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const  FCsGameplayTagEvent& Event, LogLevel)
		{
			// Check Group is Valid.
			CS_IS_ENUM_STRUCT_VALID(EMCsGameplayTagCoordinatorGroup, FECsGameplayTagCoordinatorGroup, Group)
			CS_IS_VALID(Event)

			if (UCsCoordinator_GameplayTag* Coordinator_GameplayTag = GetSafe(Context, ContextObject, Log))
			{ 
				// If Group == None, Process Immediately
				if (Group == NCsGameplayTagCoordinatorGroup::None)
				{
					Coordinator_GameplayTag->ProcessGameplayTagEvent(Group, Event);
				}
				else
				{
					Coordinator_GameplayTag->ProcessGameplayTagEvent(Group, Event);
				}
				return true;
			}
			return false;
		}

		/*#define OnProccessEventGameInfoEventType NCsGameEvent::NCoordinator::FOnProcessGameEventInfo
		OnProccessEventGameInfoEventType& FLibrary::GetOnProcessGameEventInfo_EventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameplayTagCoordinatorGroup, Group)

			return GetChecked(Context, ContextObject)->GetOnProcessGameEventInfo_Event(Group);
		}
		#undef OnProccessEventGameInfoEventType*/

		#pragma endregion Event

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}