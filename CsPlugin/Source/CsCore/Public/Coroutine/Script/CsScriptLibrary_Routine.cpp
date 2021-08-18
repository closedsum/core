// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/Script/CsScriptLibrary_Routine.h"
#include "CsCore.h"

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