// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

// Managers
#include "Managers/Time/CsTypes_Time.h"

#include "CsScriptLibrary_Time.generated.h"

UCLASS()
class CSTIME_API UCsScriptLibrary_Time : public UObject
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

	UFUNCTION(BlueprintPure, meta = (DisplayName = "DeltaTime - DeltaTime", CompactNodeTitle = "-", ScriptMethod = "Subtract", ScriptOperator = "-;-=", Keywords = "+ subtract minus", AutoCreateRefTerm = "A,B"), Category = "CsCore|Library|Time")
	static FCsDeltaTime Subtract_DeltaTime(const FCsDeltaTime& A, const FCsDeltaTime& B);
};