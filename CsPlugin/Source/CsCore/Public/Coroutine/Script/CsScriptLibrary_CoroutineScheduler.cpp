// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/Script/CsScriptLibrary_CoroutineScheduler.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsScriptLibraryCoroutineScheduler
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_CoroutineScheduler, IsHandleValid);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_CoroutineScheduler, IsRunning);
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

	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Group: %s is NOT Valid."), *Ctxt, Group.ToChar());
		return false;
	}

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	if (UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		return Scheduler->IsHandleValid(Group, Handle);
	}
	return false;
}

bool UCsScriptLibrary_CoroutineScheduler::IsRunning(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	using namespace NCsScriptLibraryCoroutineScheduler::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsRunning : Context;

	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Group: %s is NOT Valid."), *Ctxt, Group.ToChar());
		return false;
	}

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	if (UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		return Scheduler->IsRunning(Group, Handle);
	}
	return false;
}