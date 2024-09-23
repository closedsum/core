// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/Script/CsScriptLibrary_PIE_Event.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Event/CsLibrary_PIE_Event.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_PIE_Event)

// Cached
#pragma region

namespace NCsScriptLibraryPIEEvent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PIE_Event, Implements);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_PIE_Event::UCsScriptLibrary_PIE_Event(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryPIEEvent::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryPIEEvent::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_PIE_Event::Implements(const FString& Context, const UObject* Object)
{
	CONDITIONAL_SET_CTXT(Implements);

	return CsPIEEventLibrary::SafeImplements(Ctxt, Object);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT