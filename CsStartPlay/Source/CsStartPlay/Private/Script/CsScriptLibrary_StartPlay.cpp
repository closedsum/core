// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Script/CsScriptLibrary_StartPlay.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "CsLibrary_StartPlay.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_StartPlay)

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

UCsScriptLibrary_StartPlay::UCsScriptLibrary_StartPlay(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryStartPlay::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryStartPlay::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_StartPlay::HasStartedPlay(const FString& Context, const UObject* Object)
{
	CONDITIONAL_SET_CTXT(HasStartedPlay);

	return CsStartPlayLibrary::SafeHasStartedPlay(Ctxt, Object);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT