// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Spawner
#include "Spawner/Params/CsSpawnerParamsImpl.h"
#include "Spawner/Params/Shape/CsSpawnerParams_ShapeCircleImpl.h"

#include "CsScriptLibrary_Spawner.generated.h"

class ACsSpawnerImpl;

UCLASS()
class CSCORE_API UCsScriptLibrary_Spawner : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	static ACsSpawnerImpl* GetSpawnerImpl(const FString& Context, UObject* Spawner);

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

	/**
	*
	*
	* @param Context			The calling context
	* @param Spawner
	* @param Params
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Spawner", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool SetParams_ShapeCircleImpl(const FString& Context, UObject* Spawner, const FCsSpawnerParams_ShapeCircleImpl& Params);

	//static bool PointImpl_SetCenterAsActor();

	//static bool PointImpl_SetCenterAsTransform();
};