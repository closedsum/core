// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_CoroutineScheduler.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_CoroutineScheduler : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Check whether a Coroutine with the given Handle for Group is valid.
	* 
	* @param Context			The calling context
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* @param Handle
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|CoroutineScheduler", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Group,Handle"))
	static bool IsHandleValid(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle);

	/**
	* Check whether a Coroutine with the given Handle for Group is running.
	*
	* @param Context			The calling context
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* @param Handle
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|CoroutineScheduler", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Group,Handle"))
	static bool IsRunning(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle);
};