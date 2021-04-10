// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/Script/CsScriptLibrary_Routine.h"
#include "CsCore.h"

UCsScriptLibrary_Routine::UCsScriptLibrary_Routine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsRoutineHandle UCsScriptLibrary_Routine::FCsRoutineHandle_CreateNew()
{
	FCsRoutineHandle Handle;
	Handle.New();
	return Handle;
}

FCsRoutineHandle UCsScriptLibrary_Routine::FCsRoutineHandle_New(FCsRoutineHandle& Handle)
{
	Handle.New();
	return Handle;
}

bool UCsScriptLibrary_Routine::FCsRoutineHandle_IsValid(FCsRoutineHandle& Handle)
{
	return Handle.IsValid();
}

bool UCsScriptLibrary_Routine::EqualEqual_RoutineHandleRoutineHandle(const FCsRoutineHandle& A, const FCsRoutineHandle& B)
{
	return A == B;
}