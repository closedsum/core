// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/Script/CsScriptLibrary_CoroutineScheduler.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_CoroutineScheduler)

namespace NCsScriptLibraryCoroutineScheduler
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_CoroutineScheduler, IsHandleValid);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_CoroutineScheduler, IsRunning);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_CoroutineScheduler, End);
		}
	}
}

UCsScriptLibrary_CoroutineScheduler::UCsScriptLibrary_CoroutineScheduler(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryCoroutineScheduler::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryCoroutineScheduler::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_CoroutineScheduler::IsHandleValid(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	CONDITIONAL_SET_CTXT(IsHandleValid);

	return CsCoroutineSchedulerLibrary::SafeIsHandleValid(Ctxt, WorldContextObject, Group, Handle);
}

bool UCsScriptLibrary_CoroutineScheduler::IsRunning(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	CONDITIONAL_SET_CTXT(IsRunning);

	return CsCoroutineSchedulerLibrary::SafeIsRunning(Ctxt, WorldContextObject, Group, Handle);
}

// End
#pragma region

bool UCsScriptLibrary_CoroutineScheduler::End(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	CONDITIONAL_SET_CTXT(End);

	return CsCoroutineSchedulerLibrary::SafeEnd(Ctxt, WorldContextObject, Group, Handle);
}

#pragma endregion End

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT