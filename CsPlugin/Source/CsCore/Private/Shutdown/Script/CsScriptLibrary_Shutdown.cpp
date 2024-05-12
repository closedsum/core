// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Shutdown/Script/CsScriptLibrary_Shutdown.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Shutdown/CsLibrary_Shutdown.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Shutdown)

// Cached
#pragma region

namespace NCsScriptLibraryShutdown
{
	namespace NCached
	{
		namespace Str
		{
			// Shutdown
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Shutdown, HasShutdown);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Shutdown::UCsScriptLibrary_Shutdown(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryShutdown::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryShutdown::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define ShutdownLibrary NCsShutdown::FLibrary

// Shutdown
#pragma region

bool UCsScriptLibrary_Shutdown::HasShutdown(const FString& Context, UObject* Object)
{
	CONDITIONAL_SET_CTXT(HasShutdown);

	return ShutdownLibrary::SafeHasShutdown(Context, Object);
}

bool UCsScriptLibrary_Shutdown::HasShutdown_NoLog(UObject* Object)
{
	return ShutdownLibrary::SafeHasShutdown(Object);
}

#pragma endregion Shutdown

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef ShutdownLibrary