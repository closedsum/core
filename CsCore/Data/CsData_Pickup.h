// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Interactive.h"
#include "Types/CsTypes_Interactive.h"
#include "CsData_Pickup.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Pickup : public ACsData_Interactive
{
	GENERATED_UCLASS_BODY()

// Movement
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual FVector GetSpawnVelocity();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual FVector GetSpawnAcceleration();

#pragma endregion Movement

// FX
#pragma region

	virtual FCsFxElement* GetFX(const TCsPickupFX &FxType);

#pragma endregion FX

// Sound
#pragma region

	virtual FCsSoundElement* GetSound(const TCsPickupSound &SoundType);

#pragma endregion Sound
};