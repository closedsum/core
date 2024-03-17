// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Level/Script/CsScriptLibrary_Level_Streaming.h"

// CVars
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Level/CsLibrary_Level_Streaming.h"

// Cached
#pragma region

namespace NCsScriptLibraryLevelStreaming
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, Load);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, LoadChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, LoadByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, LoadByPathChecked);
			// Unload
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, Unload);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, UnloadChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, UnloadByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Level_Streaming, UnloadByPathChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Level_Streaming::UCsScriptLibrary_Level_Streaming(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
#define USING_NS_CACHED using namespace NCsScriptLibraryLevelStreaming::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryLevelStreaming::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &FCsLog::Error
#define LevelStreamingLibrary NCsLevel::NStreaming::NLocal::FLibrary

// Load
#pragma region

bool UCsScriptLibrary_Level_Streaming::Load(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadParams& Params)
{
	CONDITIONAL_SET_CTXT(Load);

	return LevelStreamingLibrary::SafeLoad(Ctxt, WorldContextObject, Params);
}

void UCsScriptLibrary_Level_Streaming::LoadChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadParams& Params, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(LoadChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(LevelStreamingLibrary::LoadChecked(Ctxt, WorldContextObject, Params), LevelStreamingLibrary::SafeLoad(Ctxt, WorldContextObject, Params, OutSuccess, LogError))
}

bool UCsScriptLibrary_Level_Streaming::LoadByPath(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadWithPathParams& Params)
{
	CONDITIONAL_SET_CTXT(LoadByPath);

	return LevelStreamingLibrary::SafeLoad(Ctxt, WorldContextObject, Params);
}

void UCsScriptLibrary_Level_Streaming::LoadByPathChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_LoadWithPathParams& Params, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(LoadByPathChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(LevelStreamingLibrary::LoadChecked(Ctxt, WorldContextObject, Params), LevelStreamingLibrary::SafeLoad(Ctxt, WorldContextObject, Params, OutSuccess, LogError))
}

#pragma endregion Load

// Unload
#pragma region

bool UCsScriptLibrary_Level_Streaming::Unload(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadParams& Params)
{
	CONDITIONAL_SET_CTXT(Unload);

	return LevelStreamingLibrary::SafeUnload(Ctxt, WorldContextObject, Params);
}

void UCsScriptLibrary_Level_Streaming::UnloadChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadParams& Params, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(UnloadChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(LevelStreamingLibrary::UnloadChecked(Ctxt, WorldContextObject, Params), LevelStreamingLibrary::SafeUnload(Ctxt, WorldContextObject, Params, OutSuccess, LogError))
}

bool UCsScriptLibrary_Level_Streaming::UnloadByPath(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadWithPathParams& Params)
{
	CONDITIONAL_SET_CTXT(UnloadByPath);

	return LevelStreamingLibrary::SafeUnload(Ctxt, WorldContextObject, Params);
}

void UCsScriptLibrary_Level_Streaming::UnloadByPathChecked(const FString& Context, const UObject* WorldContextObject, const FCsLevel_Streaming_UnloadWithPathParams& Params, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(UnloadByPathChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(LevelStreamingLibrary::UnloadChecked(Ctxt, WorldContextObject, Params), LevelStreamingLibrary::SafeUnload(Ctxt, WorldContextObject, Params, OutSuccess, LogError))
}

#pragma endregion Unload

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef LevelStreamingLibrary