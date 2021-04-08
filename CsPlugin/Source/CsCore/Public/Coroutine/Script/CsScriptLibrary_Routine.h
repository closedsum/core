// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Routine.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Routine : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Routine", meta = (DisplayName = "FCsRoutineHandle - CreateNew"))
	static FCsRoutineHandle FCsRoutineHandle_CreateNew();

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Routine", meta = (DisplayName = "FCsRoutineHandle - CreateNew"))
	static FCsRoutineHandle FCsRoutineHandle_New(UPARAM(ref) FCsRoutineHandle& Handle);
};