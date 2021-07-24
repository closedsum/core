// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/Script/CsScriptLibrary_CoroutineScheduler.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

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

bool UCsScriptLibrary_CoroutineScheduler::IsHandleValid(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	using namespace NCsScriptLibraryCoroutineScheduler::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsHandleValid : Context;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	return CoroutineSchedulerLibrary::SafeIsHandleValid(Context, WorldContextObject, Group, Handle);
}

bool UCsScriptLibrary_CoroutineScheduler::IsRunning(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	using namespace NCsScriptLibraryCoroutineScheduler::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsRunning : Context;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	return CoroutineSchedulerLibrary::SafeIsRunning(Context, WorldContextObject, Group, Handle);
}

// End
#pragma region

bool UCsScriptLibrary_CoroutineScheduler::End(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	using namespace NCsScriptLibraryCoroutineScheduler::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::End : Context;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	return CoroutineSchedulerLibrary::SafeEnd(Context, WorldContextObject, Group, Handle);
}

#pragma endregion End