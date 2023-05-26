// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/FX/CsTypes_Library_FX.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_FX.generated.h"

class UNiagaraSystem;
class USkeletalMeshComponent;

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

	/**
	* Spawn a Niagara System ONCE with a DELAY on the UpdateGroup: GameState.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param FX
	* @param Delay
	* return					Handle to spawn coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,FX,Delay"))
	static FCsRoutineHandle Spawn_GameState_OnceWithDelay(const FString& Context, UObject* WorldContextObject, const FCsFX& FX, const float& Delay);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Context,Param,Index"))
	static bool DataInterface_SkeletalMesh_SetComponent(const FString& Context, TArray<FCsFX_Parameters_DataInterface_SkeletalMesh>& Params, const int32& Index, USkeletalMeshComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|FX", meta = (AutoCreateRefTerm = "Context,Param,Index"))
	static bool DataInterface_SkeletalMesh_ClearComponent(const FString& Context, TArray<FCsFX_Parameters_DataInterface_SkeletalMesh>& Params, const int32& Index);
};