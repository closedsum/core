// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/Script/CsScriptLibrary_Manager_Time.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Time)

namespace NCsScriptLibraryManagerTime
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, GetChecked);
			// Pause
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, Pause);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, Unpause);
			// Time
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, GetTime);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, GetTimeSinceStart);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, SetScaledDeltaTime);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Time, ResetScaledDeltaTime);
		}
	}
}

UCsScriptLibrary_Manager_Time::UCsScriptLibrary_Manager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerTime::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerTime::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsTime::FLog::Error

// Get
#pragma region

UCsManager_Time* UCsScriptLibrary_Manager_Time::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsTimeManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Time* UCsScriptLibrary_Manager_Time::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsTimeManagerLibrary::GetChecked(Ctxt, WorldContextObject), CsTimeManagerLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

// Pause
#pragma region

bool UCsScriptLibrary_Manager_Time::Pause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	CONDITIONAL_SET_CTXT(Pause);

	return CsTimeManagerLibrary::SafePause(Ctxt, WorldContextObject, Group);
}

bool UCsScriptLibrary_Manager_Time::Unpause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	CONDITIONAL_SET_CTXT(Unpause);

	return CsTimeManagerLibrary::SafeUnpause(Ctxt, WorldContextObject, Group);
}

#pragma endregion Pause

// Time
#pragma region

FCsTime UCsScriptLibrary_Manager_Time::GetTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	CONDITIONAL_SET_CTXT(GetTime);

	return CsTimeManagerLibrary::GetSafeTime(Ctxt, WorldContextObject, Group);
}

FCsDeltaTime UCsScriptLibrary_Manager_Time::GetTimeSinceStart(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	CONDITIONAL_SET_CTXT(GetTimeSinceStart);

	return CsTimeManagerLibrary::GetSafeTimeSinceStart(Ctxt, WorldContextObject, Group);
}

bool UCsScriptLibrary_Manager_Time::SetScaledDeltaTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const float& Scale)
{
	CONDITIONAL_SET_CTXT(SetScaledDeltaTime);

	return CsTimeManagerLibrary::SetSafeScaledDeltaTime(Ctxt, WorldContextObject, Group, Scale);
}

bool UCsScriptLibrary_Manager_Time::ResetScaledDeltaTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group)
{
	CONDITIONAL_SET_CTXT(ResetScaledDeltaTime);

	return CsTimeManagerLibrary::SafeResetScaledDeltaTime(Ctxt, WorldContextObject, Group);
}

#pragma endregion Time

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError