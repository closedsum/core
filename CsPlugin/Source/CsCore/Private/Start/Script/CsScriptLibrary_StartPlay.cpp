// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Start/Script/CsScriptLibrary_StartPlay.h"
#include "CsCore.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Start/CsLibrary_StartPlay.h"

// Cached
#pragma region

namespace NCsScriptLibraryStartPlay
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_StartPlay, HasStartedPlay);
		}
	}
}

#pragma endregion Cached

#define StartPlayLibrary NCsStartPlay::FLibrary

UCsScriptLibrary_StartPlay::UCsScriptLibrary_StartPlay(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_StartPlay::HasStartedPlay(const FString& Context, const UObject* Object)
{
	using namespace NCsScriptLibraryStartPlay::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::HasStartedPlay : Context;

	return StartPlayLibrary::SafeHasStartedPlay(Ctxt, Object);
}


#undef StartPlayLibrary