// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsProjectileMovementComponent.h"

// Interface
#include "Collision/CsGetCollisionHitCount.h"

UCsProjectileMovementComponent::UCsProjectileMovementComponent(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	MovementType(ECsProjectileMovement::Simulated),
	bHandleDeflection(true)
{
}

// UProjectileMovementComponent Interface
#pragma region

void UCsProjectileMovementComponent::StopSimulating(const FHitResult& HitResult)
{
	int32 HitCount = 0;

	if (ICsGetCollisionHitCount* GetCollisionHitCount = Cast<ICsGetCollisionHitCount>(GetOwner()))
	{
		HitCount = GetCollisionHitCount->GetCollisionHitCount();
	}

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

#define ResultType UProjectileMovementComponent::EHandleBlockingHitResult 
ResultType UCsProjectileMovementComponent::HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector3d& MoveDelta, float& SubTickTimeRemaining)
{
	ResultType Result = Super::HandleBlockingHit(Hit, TimeTick, MoveDelta, SubTickTimeRemaining);

	if (Result == ResultType::Deflect)
	{
		if (bHandleDeflection)
			return Result;
		return ResultType::AdvanceNextSubstep;
	}
	return Result;
}
#undef ResultType

#pragma endregion UProjectileMovementComponent Interface