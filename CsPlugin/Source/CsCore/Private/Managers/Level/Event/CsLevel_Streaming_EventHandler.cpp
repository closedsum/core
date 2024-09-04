// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/Event/CsLevel_Streaming_EventHandler.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Level/CsLibrary_Manager_Level.h"
// Level
#include "Engine/LevelStreaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsLevel_Streaming_EventHandler)

// Cached
#pragma region

namespace NCsLevelStreamingEventHandler
{
	namespace NCached
	{
		namespace Str
		{		
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsLevel_Streaming_EventHandler, OnLevelLoaded);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsLevel_Streaming_EventHandler, OnLevelUnloaded);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsLevel_Streaming_EventHandler, OnLevelShown);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsLevel_Streaming_EventHandler, OnLevelHidden);
		}
	}
}

#pragma endregion Cached

ACsLevel_Streaming_EventHandler::ACsLevel_Streaming_EventHandler(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	Level(nullptr)
{
}

#define USING_NS_CACHED using namespace NCsLevelStreamingEventHandler::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsLevelStreamingEventHandler::NCached; \
	const FString& Context = Str::__FunctionName

ULevelStreaming* ACsLevel_Streaming_EventHandler::GetLevel() const
{
	return Level.IsValid() ? Level.Get() : nullptr;
}

void ACsLevel_Streaming_EventHandler::OnLevelLoaded()
{
	SET_CONTEXT(OnLevelLoaded);

	if (ULevelStreaming* L = GetLevel())
	{
		CsLevelManagerLibrary::BroadcastChecked_Level_Streaming_OnLoaded(Context, this, L);
	}
}

void ACsLevel_Streaming_EventHandler::OnLevelUnloaded()
{
	SET_CONTEXT(OnLevelUnloaded);

	if (ULevelStreaming* L = GetLevel())
	{
		CsLevelManagerLibrary::BroadcastChecked_Level_Streaming_OnUnloaded(Context, this, L);
	}
}

void ACsLevel_Streaming_EventHandler::OnLevelShown()
{
	SET_CONTEXT(OnLevelShown);

	if (ULevelStreaming* L = GetLevel())
	{
		CsLevelManagerLibrary::BroadcastChecked_Level_Streaming_OnShown(Context, this, L);
	}
}

void ACsLevel_Streaming_EventHandler::OnLevelHidden()
{
	SET_CONTEXT(OnLevelShown);

	if (ULevelStreaming* L = GetLevel())
	{
		CsLevelManagerLibrary::BroadcastChecked_Level_Streaming_OnHidden(Context, this, L);
	}
}

#undef USING_NS_CACHED
#undef SET_CONTEXT