// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GameFramework/ProjectileMovementComponent.h"
#include "Types/CsTypes_Projectile.h"

#include "CsProjectileMovementComponent.generated.h"
#pragma once

UCLASS()
class CSPRJ_API UCsProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_UCLASS_BODY()

// UProjectileMovementComponent Interface
#pragma region
public:

	virtual void StopSimulating(const FHitResult& HitResult) override;

	virtual bool ShouldUseSubStepping() const override;

protected:

#define ResultType UProjectileMovementComponent::EHandleBlockingHitResult 
	virtual ResultType HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector& MoveDelta, float& SubTickTimeRemaining) override;
#undef ResultType

#pragma endregion UProjectileMovementComponent Interface

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation)
	ECsProjectileMovement MovementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation)
	bool bHandleDeflection;
};