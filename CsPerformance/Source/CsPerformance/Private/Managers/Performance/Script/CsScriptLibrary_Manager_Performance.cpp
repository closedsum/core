// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Performance/Script/CsScriptLibrary_Manager_Performance.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Performance/CsLibrary_Manager_Performance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Performance)

// Cached
#pragma region

namespace NCsScriptLibraryManagerPerformance
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Performance, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Performance, GetChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Performance::UCsScriptLibrary_Manager_Performance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerPerformance::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerPerformance::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsPerformance::FLog::Error
#define PerformanceManagerLibrary NCsPerformance::NManager::FLibrary

// Get
#pragma region

UCsManager_Performance* UCsScriptLibrary_Manager_Performance::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return PerformanceManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Performance* UCsScriptLibrary_Manager_Performance::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	return CS_SCRIPT_GET_CHECKED(PerformanceManagerLibrary::GetChecked(Ctxt, WorldContextObject), PerformanceManagerLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef PerformanceManagerLibrary