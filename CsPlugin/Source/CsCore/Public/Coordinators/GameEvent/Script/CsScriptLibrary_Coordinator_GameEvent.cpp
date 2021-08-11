// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/GameEvent/Script/CsScriptLibrary_Coordinator_GameEvent.h"
#include "CsCore.h"

// Library
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"

namespace NCsScriptLibraryCoordinatorGameEvent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameEvent, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameEvent, BroadcastGameEvent);
		}
	}
}

UCsScriptLibrary_Coordinator_GameEvent::UCsScriptLibrary_Coordinator_GameEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

UCsCoordinator_GameEvent* UCsScriptLibrary_Coordinator_GameEvent::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	typedef NCsGameEvent::NCoordinator::FLibrary GameEventCoordinatorLibrary;

	return GameEventCoordinatorLibrary::GetSafe(Context, WorldContextObject);
}

#pragma endregion Get

bool UCsScriptLibrary_Coordinator_GameEvent::BroadcastGameEvent(const FString& Context, const UObject* WorldContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info)
{
	using namespace NCsScriptLibraryCoordinatorGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BroadcastGameEvent : Context;

	typedef NCsGameEvent::NCoordinator::FLibrary GameEventCoordinatorLibrary;

	return GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Context, WorldContextObject, Group, Info);
}