// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/Script/CsScriptLibrary_Coordinator_GameEvent.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Coordinator_GameEvent)

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

#define USING_NS_CACHED using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryCoordinatorGameEvent::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &FCsLog::Error

// Get
#pragma region

UCsCoordinator_GameEvent* UCsScriptLibrary_Coordinator_GameEvent::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsGameEventCoordinatorLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsCoordinator_GameEvent* UCsScriptLibrary_Coordinator_GameEvent::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	return CS_SCRIPT_GET_CHECKED(CsGameEventCoordinatorLibrary::GetChecked(Ctxt, WorldContextObject), CsGameEventCoordinatorLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Coordinator_GameEvent::BroadcastGameEventInfo(const FString& Context, const UObject* WorldContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
{
	CONDITIONAL_SET_CTXT(BroadcastGameEventInfo);

	return CsGameEventCoordinatorLibrary::SafeBroadcastGameEvent(Ctxt, WorldContextObject, Group, Info);
}

bool UCsScriptLibrary_Coordinator_GameEvent::BroadcastGameEvent_GameInstance(const FString& Context, const UObject* WorldContextObject, const FECsGameEvent& Event)
{
	CONDITIONAL_SET_CTXT(BroadcastGameEvent_GameInstance);

	FCsGameEventInfo Info;
	Info.Event = Event;

	return CsGameEventCoordinatorLibrary::SafeBroadcastGameEvent(Ctxt, WorldContextObject, NCsGameEventCoordinatorGroup::GameInstance, Info);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError