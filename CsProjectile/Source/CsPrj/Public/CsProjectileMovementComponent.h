// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

protected:

#define ResultType UProjectileMovementComponent::EHandleBlockingHitResult 
	virtual ResultType HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector3d& MoveDelta, float& SubTickTimeRemaining) override;
#undef ResultType

#pragma endregion UProjectileMovementComponent Interface

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation)
	ECsProjectileMovement MovementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileSimulation)
	bool bHandleDeflection;
};