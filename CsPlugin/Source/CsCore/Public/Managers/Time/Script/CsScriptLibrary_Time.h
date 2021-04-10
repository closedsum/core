// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

// Managers
#include "Managers/Time/CsTypes_Time.h"

#include "CsScriptLibrary_Time.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Time : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Time", meta = (DisplayName = "FCsTime - Create"))
	static FCsTime FCsTime_Create();

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Time", meta = (DisplayName = "FCsTime - Copy"))
	static FCsTime FCsTime_Copy(const FCsTime& Time);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Time", meta = (DisplayName = "FCsDeltaTime - Copy"))
	static FCsDeltaTime FCsDeltaTime_Copy(const FCsDeltaTime& DeltaTime);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "DeltaTime + DeltaTime", CompactNodeTitle = "+", ScriptMethod = "Add", ScriptOperator = "+;+=", Keywords = "+ add plus", AutoCreateRefTerm = "A,B"), Category = "CsCore|Library|Time")
	static FCsDeltaTime Add_DeltaTime(const FCsDeltaTime& A, const FCsDeltaTime& B);
};