// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Movement_Interp.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_Actor_Movement.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Actor_Movement : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Move
#pragma region
public:

	/**
	* Move an Object via interpolation (i.e. an simple easing function) with the given Params.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params				Information describing how to interpolate the Object.
	* return					Handle to the movement coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle MoveByInterp(const FString& Context, const UObject* WorldContextObject, const FCsMoveByInterp_Params& Params);

#pragma endregion Move
};