// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Sound/CsTypes_Library_Sound.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_Sound.generated.h"

class USoundBase;

UCLASS()
class CSCORE_API UCsScriptLibrary_Sound : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Sound", meta = (AutoCreateRefTerm = "Name"))
	static FECsSound Get(const FString& Name);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Sound", meta = (AutoCreateRefTerm = "Index"))
	static FECsSound GetByIndex(const int32& Index);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Sound", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const FECsSound& Enum);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Sound")
	static uint8 GetCount();

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Sound")
	static void GetAll(TArray<FECsSound>& OutTypes);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Sound", meta = (AutoCreateRefTerm = "Name"))
	static FECsSound GetMax();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Sound)", CompactNodeTitle = "==", ScriptMethod = "Equals", Keywords = "== equal"), Category = "CsCore|Library|Sound")
	static bool EqualEqual(const FECsSound& A, const FECsSound& B);

#pragma endregion Enum

public:

	/**
	* 
	* 
	* @param Context	The calling context.
	* @param Path
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Sound", meta = (AutoCreateRefTerm = "Context,Path"))
	static USoundBase* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* 
	* 
	* @param Context	The calling context.
	* @param Path
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Sound", meta = (AutoCreateRefTerm = "Context,Path"))
	static USoundBase* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Spawn a Sound Base over time with the give spawn params.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params
	* return					Handle to spawn coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Sound", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle Spawn(const FString& Context, UObject* WorldContextObject, const FCsSound_Spawn_Params& Params);
};