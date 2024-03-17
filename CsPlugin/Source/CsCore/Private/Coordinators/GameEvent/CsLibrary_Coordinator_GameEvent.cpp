// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Coordinators
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Settings
#include "Coordinators/GameEvent/CsSettings_Coordinator_GameEvent.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameEvent::NCoordinator::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameEvent::NCoordinator::FLibrary, GetSafeContextRoot);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsGameEvent::NCoordinator::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameEvent::NCoordinator::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define GameInstanceLibrary NCsGameInstance::FLibrary

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
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

		UCsCoordinator_GameEvent* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot						    = GetContextRootChecked(Context, ContextObject);
			UCsCoordinator_GameEvent* Coordinator_GameEvent = UCsCoordinator_GameEvent::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Coordinator_GameEvent)
			return Coordinator_GameEvent;
		}

		UCsCoordinator_GameEvent* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoordinator_GameEvent* Coordinator_GameEvent = UCsCoordinator_GameEvent::Get(ContextRoot);

			if (!Coordinator_GameEvent)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Coordinator_GameEvent."), *Context));
				return nullptr;
			}
			return Coordinator_GameEvent;
		}

		UCsCoordinator_GameEvent* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoordinator_GameEvent* Coordinator_GameEvent = UCsCoordinator_GameEvent::Get(ContextRoot);

			if (!Coordinator_GameEvent)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Coordinator_GameEvent."), *Context));
				return nullptr;
			}

			OutSuccess = true;
			return Coordinator_GameEvent;
		}

		#pragma endregion Get

		// Class
		#pragma region
		
		TSubclassOf<UCsCoordinator_GameEvent> FLibrary::GetClassChecked(const FString& Context)
		{
			const FCsSettings_Coordinator_GameEvent& Settings = FCsSettings_Coordinator_GameEvent::Get();

			return TSubclassOf<UCsCoordinator_GameEvent>(Settings.LoadClassChecked(Context));
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

		void FLibrary::ProcessGameEventInfoChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameEventCoordinatorGroup, Group)
			CS_IS_VALID_CHECKED(Info);

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				GetChecked(Context, ContextObject)->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				GetChecked(Context, ContextObject)->QueueGameEventInfo(Group, Info);
			}
		}

		bool FLibrary::SafeProcessGameEventInfo(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup, Group)
			CS_IS_VALID(Info)

			if (UCsCoordinator_GameEvent* Coordinator_GameEvent = GetSafe(Context, ContextObject, Log))
			{ 
				// If Group == None, Process Immediately
				if (Group == NCsGameEventCoordinatorGroup::None)
				{
					Coordinator_GameEvent->ProcessGameEventInfo(Group, Info);
				}
				else
				{
					Coordinator_GameEvent->QueueGameEventInfo(Group, Info);
				}
				return true;
			}
			return false;
		}

		void FLibrary::BroadcastGameEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameEventCoordinatorGroup, Group)
			CS_IS_VALID_CHECKED(Info);

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				GetChecked(Context, ContextObject)->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				GetChecked(Context, ContextObject)->QueueGameEventInfo(Group, Info);
			}
		}

		bool FLibrary::SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check Group is Valid.
			CS_IS_ENUM_STRUCT_VALID(EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup, Group)
			CS_IS_VALID(Info)

			if (UCsCoordinator_GameEvent* Coordinator_GameEvent = GetSafe(Context, ContextObject, Log))
			{ 
				// If Group == None, Process Immediately
				if (Group == NCsGameEventCoordinatorGroup::None)
				{
					Coordinator_GameEvent->ProcessGameEventInfo(Group, Info);
				}
				else
				{
					Coordinator_GameEvent->QueueGameEventInfo(Group, Info);
				}
				return true;
			}
			return false;
		}

		void FLibrary::BroadcastGameEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value /*=0*/, const FVector3f& Location /*=FVector3f::ZeroVector*/)
		{
			FCsGameEventInfo Info;
			Info.Event = GameEvent;
			Info.Value = Value;
			Info.Location = Location;

			BroadcastGameEventChecked(Context, ContextObject, Group, Info);
		}

		bool FLibrary::SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value, const FVector3f& Location, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			FCsGameEventInfo Info;
			Info.Event = GameEvent;
			Info.Value = Value;
			Info.Location = Location;

			return SafeBroadcastGameEvent(Context, ContextObject, Group, Info, Log);
		}

		#define OnProccessEventGameInfoEventType NCsGameEvent::NCoordinator::FOnProcessGameEventInfo
		OnProccessEventGameInfoEventType& FLibrary::GetOnProcessGameEventInfo_EventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameEventCoordinatorGroup, Group)

			return GetChecked(Context, ContextObject)->GetOnProcessGameEventInfo_Event(Group);
		}
		#undef OnProccessEventGameInfoEventType

		#pragma endregion Event

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef GameInstanceLibrary
	}
}