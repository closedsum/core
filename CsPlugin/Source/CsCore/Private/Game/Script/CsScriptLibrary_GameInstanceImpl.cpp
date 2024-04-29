// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Script/CsScriptLibrary_GameInstanceImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstanceImpl.h"

// Cached
#pragma region

namespace NCsScriptLibraryGameInstanceImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameInstanceImpl, IsMobilePreviewEditor);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameInstanceImpl::UCsScriptLibrary_GameInstanceImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_GameInstanceImpl::IsMobilePreviewEditor(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryGameInstanceImpl::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsMobilePreviewEditor : Context;

	typedef NCsGameInstance::NImpl::FLibrary GameInstanceLibrary;

	return GameInstanceLibrary::SafeIsMobilePreviewEditor(Ctxt, WorldContextObject);
}