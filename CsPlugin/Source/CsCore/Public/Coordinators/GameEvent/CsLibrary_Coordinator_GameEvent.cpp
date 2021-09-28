// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Coordinators
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameEvent::NCoordinator::FLibrary, GetSafeContextRoot);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsGameEvent::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

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
			}
			return Coordinator_GameEvent;
		}

		#pragma endregion Get

		void FLibrary::ProcessGameEventInfoChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			// Check Group is Valid.
			checkf(EMCsGameEventCoordinatorGroup::Get().IsValidEnum(Group), TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar());
			// Check Info is Valid.
			check(Info.IsValidChecked(Context));

			UCsCoordinator_GameEvent* Coordinator_GameEvent = GetChecked(Context, ContextObject);

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				Coordinator_GameEvent->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				Coordinator_GameEvent->QueueGameEventInfo(Group, Info);
			}
		}

		void FLibrary::BroadcastGameEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info)
		{
			// Check Group is Valid.
			check(EMCsGameEventCoordinatorGroup::Get().IsValidEnumChecked(Context, Group));
			// Check GameEvent is Valid.
			check(Info.IsValidChecked(Context));

			UCsCoordinator_GameEvent* Coordinator_GameEvent = GetChecked(Context, ContextObject);

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				Coordinator_GameEvent->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				Coordinator_GameEvent->QueueGameEventInfo(Group, Info);
			}
		}

		bool FLibrary::SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check Group is Valid.
			CS_IS_ENUM_STRUCT_VALID(EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup, Group)

			if (!Info.IsValid(Context, Log))
				return false;

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

		void FLibrary::BroadcastGameEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value /*=0*/, const FVector& Location /*=FVector::ZeroVector*/)
		{
			FCsGameEventInfo Info;
			Info.Event = GameEvent;
			Info.Value = Value;
			Info.Location = Location;

			BroadcastGameEventChecked(Context, ContextObject, Group, Info);
		}

		bool FLibrary::SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value, const FVector& Location, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			FCsGameEventInfo Info;
			Info.Event = GameEvent;
			Info.Value = Value;
			Info.Location = Location;

			return SafeBroadcastGameEvent(Context, ContextObject, Group, Info, Log);
		}
	}
}