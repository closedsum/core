// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Script/CsScriptLibrary_GameInstanceImpl.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstanceImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GameInstanceImpl)

// Cached
#pragma region

namespace NCsScriptLibraryGameInstanceImpl
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameInstanceImpl, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameInstanceImpl, GetChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameInstanceImpl, IsMobilePreviewEditor);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameInstanceImpl::UCsScriptLibrary_GameInstanceImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryGameInstanceImpl::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryGameInstanceImpl::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &FCsLog::Error

// Get
#pragma region

UCsGameInstance* UCsScriptLibrary_GameInstanceImpl::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsGameInstanceImplLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsGameInstance* UCsScriptLibrary_GameInstanceImpl::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsGameInstanceImplLibrary::GetChecked(Context, WorldContextObject), CsGameInstanceImplLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_GameInstanceImpl::IsMobilePreviewEditor(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(IsMobilePreviewEditor);

	return CsGameInstanceImplLibrary::SafeIsMobilePreviewEditor(Ctxt, WorldContextObject);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError