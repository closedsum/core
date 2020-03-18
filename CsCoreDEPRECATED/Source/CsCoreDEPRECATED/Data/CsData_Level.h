// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "CsData_Level.generated.h"

/* Current Order of Categories

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCOREDEPRECATED_API UCsData_Level : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Level")
	virtual FString GetMapName();

	virtual TArray<FName>* GetShortCodes();
};