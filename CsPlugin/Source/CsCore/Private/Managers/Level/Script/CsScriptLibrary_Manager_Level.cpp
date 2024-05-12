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
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Level::UCsScriptLibrary_Manager_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
#define USING_NS_CACHED using namespace NCsScriptLibraryManagerLevel::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerLevel::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &FCsLog::Error
#define LevelManagerLibrary NCsLevel::NManager::FLibrary

// Get
#pragma region

UCsManager_Level* UCsScriptLibrary_Manager_Level::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return LevelManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Level* UCsScriptLibrary_Manager_Level::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Get);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(LevelManagerLibrary::GetChecked(Ctxt, WorldContextObject), LevelManagerLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef LevelManagerLibrary