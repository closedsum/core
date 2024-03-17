// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/Script/CsScriptLibrary_Coordinator_GameEvent.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"

namespace NCsScriptLibraryCoordinatorGameEvent
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameEvent, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameEvent, GetChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameEvent, BroadcastGameEventInfo);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameEvent, BroadcastGameEvent_GameInstance);
		}
	}
}

UCsScriptLibrary_Coordinator_GameEvent::UCsScriptLibrary_Coordinator_GameEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &FCsLog::Error
#define GameEventCoordinatorLibrary NCsGameEvent::NCoordinator::FLibrary

// Get
#pragma region

UCsCoordinator_GameEvent* UCsScriptLibrary_Coordinator_GameEvent::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return GameEventCoordinatorLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsCoordinator_GameEvent* UCsScriptLibrary_Coordinator_GameEvent::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return CS_SCRIPT_GET_CHECKED(GameEventCoordinatorLibrary::GetChecked(Ctxt, WorldContextObject), GameEventCoordinatorLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Coordinator_GameEvent::BroadcastGameEventInfo(const FString& Context, const UObject* WorldContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
{
	using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BroadcastGameEventInfo : Context;

	return GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Ctxt, WorldContextObject, Group, Info);
}

bool UCsScriptLibrary_Coordinator_GameEvent::BroadcastGameEvent_GameInstance(const FString& Context, const UObject* WorldContextObject, const FECsGameEvent& Event)
{
	using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BroadcastGameEvent_GameInstance : Context;

	FCsGameEventInfo Info;
	Info.Event = Event;

	return GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Ctxt, WorldContextObject, NCsGameEventCoordinatorGroup::GameInstance, Info);
}

#undef LogError
#undef GameEventCoordinatorLibrary