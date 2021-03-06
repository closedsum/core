// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/FX/CsTypes_Library_FX.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_FX.generated.h"

class UNiagaraSystem;

UCLASS()
class CSCORE_API UCsScriptLibrary_FX : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Name"))
	static FECsFX Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Index"))
	static FECsFX GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsFX& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|FX")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|FX")
	static void GetAll(TArray<FECsFX>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Name"))
	static FECsFX GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (FX)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|FX")
	static bool EqualEqual(const FECsFX& A, const FECsFX& B);

#pragma endregion Enum

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
	* @param Path
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Context,Path"))
	static UNiagaraSystem* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Spawn a Niagara System over time with the give spawn params.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* return					Handle to spawn coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle Spawn(const FString& Context, UObject* WorldContextObject, const FCsFX_Spawn_Params& Params);
};