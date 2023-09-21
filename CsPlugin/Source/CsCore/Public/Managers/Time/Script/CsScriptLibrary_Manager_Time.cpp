// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/Script/CsScriptLibrary_Manager_Time.h"
#include "CsCore.h"

// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"

namespace NCsScriptLibraryManagerTime
{
	namespace NCached
	{
		namespace Str
		{
			// Pause
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, Pause);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, Unpause);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, GetTime);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, GetTimeSinceStart);
		}
	}
}

UCsScriptLibrary_Manager_Time::UCsScriptLibrary_Manager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define TimeManagerLibrary NCsTime::NManager::FLibrary

// Pause
#pragma region

bool UCsScriptLibrary_Manager_Time::Pause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	using namespace NCsScriptLibraryManagerTime::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Pause : Context;

	return TimeManagerLibrary::SafePause(Ctxt, WorldContextObject, Group);
}

bool UCsScriptLibrary_Manager_Time::Unpause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	using namespace NCsScriptLibraryManagerTime::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Pause : Context;

	return TimeManagerLibrary::SafeUnpause(Ctxt, WorldContextObject, Group);
}

#pragma endregion Pause

FCsTime UCsScriptLibrary_Manager_Time::GetTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	using namespace NCsScriptLibraryManagerTime::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTime : Context;

	return TimeManagerLibrary::GetSafeTime(Ctxt, WorldContextObject, Group);
}

FCsDeltaTime UCsScriptLibrary_Manager_Time::GetTimeSinceStart(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	using namespace NCsScriptLibraryManagerTime::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTimeSinceStart : Context;

	return TimeManagerLibrary::GetSafeTimeSinceStart(Ctxt, WorldContextObject, Group);
}

#undef TimeManagerLibrary