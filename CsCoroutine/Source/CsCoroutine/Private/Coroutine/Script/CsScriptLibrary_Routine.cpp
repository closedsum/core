// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/Script/CsScriptLibrary_Routine.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Routine)

UCsScriptLibrary_Routine::UCsScriptLibrary_Routine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsRoutineHandle UCsScriptLibrary_Routine::CreateNew()
{
	FCsRoutineHandle Handle;
	Handle.New();
	return Handle;
}

FCsRoutineHandle UCsScriptLibrary_Routine::New(FCsRoutineHandle& Handle)
{
	Handle.New();
	return Handle;
}

bool UCsScriptLibrary_Routine::IsValid(const FCsRoutineHandle& Handle)
{
	return Handle.IsValid();
}

bool UCsScriptLibrary_Routine::EqualEqual(const FCsRoutineHandle& A, const FCsRoutineHandle& B)
{
	return A == B;
}

FCsRoutineHandle UCsScriptLibrary_Routine::Reset(FCsRoutineHandle& Handle)
{
	Handle.Reset();
	return Handle;
}

FString UCsScriptLibrary_Routine::ToString(const FCsRoutineHandle& Handle)
{
	return Handle.ToString();
}