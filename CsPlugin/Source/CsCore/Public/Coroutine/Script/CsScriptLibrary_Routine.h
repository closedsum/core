// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_Routine.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Routine : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Routine")
	static FCsRoutineHandle CreateNew();

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Routine")
	static FCsRoutineHandle New(UPARAM(ref) FCsRoutineHandle& Handle);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Routine")
	static bool IsValid(const FCsRoutineHandle& Handle);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (RoutineHandle)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Routine")
	static bool EqualEqual(const FCsRoutineHandle& A, const FCsRoutineHandle& B);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Routine")
	static FCsRoutineHandle Reset(UPARAM(ref) FCsRoutineHandle& Handle);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Routine")
	static FString ToString(const FCsRoutineHandle& Handle);
};