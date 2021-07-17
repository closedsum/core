// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Spawner
#include "Spawner/Params/CsSpawnerParamsImpl.h"

#include "CsScriptLibrary_Spawner.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Spawner : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* 
	* 
	* @param Context			The calling context
	* @param Spawner
	* @param Params
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Spawner", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool SetParams_DefaultImpl(const FString& Context, UObject* Spawner, const FCsSpawnerParamsImpl& Params);
};