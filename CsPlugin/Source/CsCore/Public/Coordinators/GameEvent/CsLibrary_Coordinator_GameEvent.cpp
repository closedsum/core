// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_World.h"
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

	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) /*= nullptr*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			// Check World is Valid.
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			// Check GameInstance is Valid.
			UGameInstance* GameInstance = World->GetGameInstance();

			if (!GameInstance)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GameInstance is NULL."), *Context));
			}
			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			using namespace NCsGameEvent::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

	#endif // #if WITH_EDITOR

		void FLibrary::ProcessGameEventInfoChecked(const FString& Context, UObject* WorldContext, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			// Check Group is Valid.
			checkf(EMCsGameEventCoordinatorGroup::Get().IsValidEnum(Group), TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar());
			// Check Info is Valid.
			check(Info.IsValidChecked(Context));

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->QueueGameEventInfo(Group, Info);
			}
		}

		void FLibrary::BroadcastGameEventChecked(const FString& Context, UObject* WorldContext, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value /*=0*/, const FVector& Location /*=FVector::ZeroVector*/)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			FCsGameEventInfo Info;
			Info.Event = GameEvent;
			Info.Value = Value;
			Info.Location = Location;

			// Check Group is Valid.
			check(EMCsGameEventCoordinatorGroup::Get().IsValidEnumChecked(Context, Group));
			// Check GameEvent is Valid.
			check(EMCsGameEvent::Get().IsValidEnumChecked(Context, GameEvent));

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->QueueGameEventInfo(Group, Info);
			}
		}

		void FLibrary::SafeBroadcastGameEvent(const FString& Context, UObject* WorldContext, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value, const FVector& Location, void(*Log)(const FString&) /*= nullptr*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

			// Check ContextRoot is Valid.
			if (!ContextRoot)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: ContextRoot is NULL."), *Context));
				return;
			}
			// Check Group is Valid.
			if (!EMCsGameEventCoordinatorGroup::Get().IsValidEnum(Group))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar()));
				return;
			}
			// Check GameEvent is Valid.
			if (!EMCsGameEvent::Get().IsValidEnum(GameEvent))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: GameEvent: %s is NOT Valid."), *Context, GameEvent.ToChar()));
				return;
			}

			FCsGameEventInfo Info;
			Info.Event	  = GameEvent;
			Info.Value	  = Value;
			Info.Location = Location;

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->QueueGameEventInfo(Group, Info);
			}
		}
	}
}