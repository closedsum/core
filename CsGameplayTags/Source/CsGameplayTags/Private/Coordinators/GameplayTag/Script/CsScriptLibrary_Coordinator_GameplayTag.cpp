// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/Script/CsScriptLibrary_Coordinator_GameplayTag.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Coordinators/GameplayTag/CsLibrary_Coordinator_GameplayTag.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Coordinator_GameplayTag)

namespace NCsScriptLibraryCoordinatorGameplayTag
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameplayTag, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameplayTag, GetChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameplayTag, BroadcastGameplayTagEvent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Coordinator_GameplayTag, BroadcastGameplayTagEvent_GameInstance);
		}
	}
}

void(*UCsScriptLibrary_Coordinator_GameplayTag::LogError)(const FString&) = &NCsGameplayTags::FLog::Error;

UCsScriptLibrary_Coordinator_GameplayTag::UCsScriptLibrary_Coordinator_GameplayTag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryCoordinatorGameplayTag::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryCoordinatorGameplayTag::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

UCsCoordinator_GameplayTag* UCsScriptLibrary_Coordinator_GameplayTag::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsGameplayTagCoordinatorLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsCoordinator_GameplayTag* UCsScriptLibrary_Coordinator_GameplayTag::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	return CS_SCRIPT_GET_CHECKED(CsGameplayTagCoordinatorLibrary::GetChecked(Ctxt, WorldContextObject), CsGameplayTagCoordinatorLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Coordinator_GameplayTag::BroadcastGameplayTagEvent(const FString& Context, const UObject* WorldContextObject, const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event)
{
	CONDITIONAL_SET_CTXT(BroadcastGameplayTagEvent);

	return CsGameplayTagCoordinatorLibrary::SafeBroadcastGameplayTagEvent(Ctxt, WorldContextObject, Group, Event);
}

bool UCsScriptLibrary_Coordinator_GameplayTag::BroadcastGameplayTag_GameInstance(const FString& Context, const UObject* WorldContextObject, const FGameplayTag& Tag)
{
	CONDITIONAL_SET_CTXT(BroadcastGameplayTagEvent);

	FCsGameplayTagEvent Event;
	Event.Tag = Tag;

	return CsGameplayTagCoordinatorLibrary::SafeBroadcastGameplayTagEvent(Ctxt, WorldContextObject, NCsGameplayTagCoordinatorGroup::GameInstance, Event);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT