// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "CsData_Level.generated.h"

/* Current Order of Categories

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Level : public ACsData
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Level")
	virtual FString GetMapName();

	virtual TArray<FName>* GetShortCodes();
};