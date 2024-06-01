// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_Routine.generated.h"

UCLASS()
class CSCOROUTINE_API UCsScriptLibrary_Routine : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCoroutine|Library|Routine")
	static FCsRoutineHandle CreateNew();

	UFUNCTION(BlueprintCallable, Category = "CsCoroutine|Library|Routine")
	static FCsRoutineHandle New(UPARAM(ref) FCsRoutineHandle& Handle);

	UFUNCTION(BlueprintPure, Category = "CsCoroutine|Library|Routine")
	static bool IsValid(const FCsRoutineHandle& Handle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (RoutineHandle)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCoroutine|Library|Routine")
	static bool EqualEqual(const FCsRoutineHandle& A, const FCsRoutineHandle& B);

	UFUNCTION(BlueprintCallable, Category = "CsCoroutine|Library|Routine")
	static FCsRoutineHandle Reset(UPARAM(ref) FCsRoutineHandle& Handle);

	UFUNCTION(BlueprintPure, Category = "CsCoroutine|Library|Routine")
	static FString ToString(const FCsRoutineHandle& Handle);
};