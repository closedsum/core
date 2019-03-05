// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Interactive.h"
#include "CsData_Damageable.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Damageable : public ACsData_Interactive
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual int32 GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual float GetRespawnTime();

#pragma endregion Stats
};