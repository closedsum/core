// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectileMovementComponent.h"

UCsProjectileMovementComponent::UCsProjectileMovementComponent(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	HitCount(0),
	MovementType(ECsProjectileMovement::Simulated)
{
}

void UCsProjectileMovementComponent::StopSimulating(const FHitResult& HitResult)
{
	--HitCount;

	if (HitCount <= 0)
	{
		HitCount = 0;

		Super::StopSimulating(HitResult);
	}
}

bool UCsProjectileMovementComponent::ShouldUseSubStepping() const
{
	if (MovementType == ECsProjectileMovement::Function)
		return false;
	return Super::ShouldUseSubStepping();
}