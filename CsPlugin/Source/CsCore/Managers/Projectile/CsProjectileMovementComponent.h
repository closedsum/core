// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/ProjectileMovementComponent.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsProjectileMovementComponent.generated.h"

UCLASS()
class CSCORE_API UCsProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation)
	TEnumAsByte<ECsProjectileMovement::Type> MovementType;

	virtual bool ShouldUseSubStepping() const;
};

