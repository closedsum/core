// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/ProjectileMovementComponent.h"
#include "Types/CsTypes_Projectile.h"
#include "CsProjectileMovementComponent.generated.h"

UCLASS()
class CSPRJ_API UCsProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_UCLASS_BODY()

// UProjectileMovementComponent Interface
#pragma region
public:

	virtual void StopSimulating(const FHitResult& HitResult) override;

	virtual bool ShouldUseSubStepping() const override;

#pragma endregion UProjectileMovementComponent Interface

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation, meta = (UIMin = "0", ClampMin = "0"))
	int32 HitCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation)
	ECsProjectileMovement MovementType;
};