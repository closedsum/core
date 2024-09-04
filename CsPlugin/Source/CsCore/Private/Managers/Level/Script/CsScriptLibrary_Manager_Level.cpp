// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/Script/CsScriptLibrary_Manager_Level.h"

// CVars
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Level/CsLibrary_Manager_Level.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Level)

// Cached
#pragma region

namespace NCsScriptLibraryManagerLevel
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Level, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Level, GetChecked);
			// Change Map
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Level, HasChangeMapCompleted);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Level, ChangeMap);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_Manager_Level::LogError)(const FString&) = &FCsLog::Error;

UCsScriptLibrary_Manager_Level::UCsScriptLibrary_Manager_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerLevel::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerLevel::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

UCsManager_Level* UCsScriptLibrary_Manager_Level::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsLevelManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Level* UCsScriptLibrary_Manager_Level::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Get);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(GetChecked, GetSafe, WorldContextObject);
}

#pragma endregion Get

// Change Map
#pragma region

bool UCsScriptLibrary_Manager_Level::HasChangeMapCompleted(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(HasChangeMapCompleted);

	return CsLevelManagerLibrary::SafeHasChangeMapCompleted(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Manager_Level::ChangeMap(const FString& Context, const UObject* WorldContextObject, const FCsManagerLevel_ChangeMapParams& Params)
{
	CONDITIONAL_SET_CTXT(ChangeMap);

	return CsLevelManagerLibrary::SafeChangeMap(Ctxt, WorldContextObject, Params);
}

#pragma endregion Change Map

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT