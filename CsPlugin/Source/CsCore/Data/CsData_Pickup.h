// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Interactive.h"
#include "Types/CsTypes_Interactive.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Sound.h"
#include "CsData_Pickup.generated.h"

UCLASS(Abstract)
class CSCORE_API UCsData_Pickup : public UCsData_Interactive
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

	virtual FCsFxElement* GetFX(const FECsPickupFX& FxType);

#pragma endregion FX

// Sound
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Sound")
	virtual const bool& UseCollectSound();

	virtual FCsSoundElement* GetSound(const FECsPickupSound& SoundType);
	virtual void PlaySound(UWorld* InWorld, const FECsPickupSound& SoundType, UObject* InOwner, UObject* InParent);

#pragma endregion Sound
};