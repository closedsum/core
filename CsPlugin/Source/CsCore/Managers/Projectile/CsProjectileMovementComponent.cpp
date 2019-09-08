// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsProjectileMovementComponent.h"

UCsProjectileMovementComponent::UCsProjectileMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

bool UCsProjectileMovementComponent::ShouldUseSubStepping() const
{
	if (MovementType == ECsProjectileMovement::Function)
		return false;
	return Super::ShouldUseSubStepping();
}