// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/FX/Script/CsTypes_ScriptLibrary_FX.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_FX.generated.h"

class UNiagaraSystem;

UCLASS()
class CSCORE_API UCsScriptLibrary_FX : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* 
	* 
	* @param Context	The calling context.
	* @param Path
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Context,Path"))
	static UNiagaraSystem* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* 
	* 
	* @param Context	The calling context.
	* @parma Path
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Context,Path"))
	static UNiagaraSystem* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Spawn a Niagara System over time with the give spawn params.
	*
	* @param Context	The calling context.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static FCsRoutineHandle Spawn(const FString& Context, UObject* WorldContextObject, const FCsScriptLibrary_FX_Spawn_Params& Params);
};