// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
// Types
#include "AI/BehaviorTree/CsTypes_BehaviorTree.h"
#include "CsBTDecorator_CheckAbsDeltaYaw.generated.h"

/**
 * Check Abs Delta Yaw decorator node.
 * A decorator node that checks if AI's root (or current view) Yaw is with Abs Delta of a Rotator Key.
 */
UCLASS()
class CSCOREDEPRECATED_API UCsBTDecorator_CheckAbsDeltaYaw : public UBTDecorator_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", UIMin = "0.0"))
	bool bCurrentView;

	UPROPERTY(EditAnywhere, Category = Condition)
	TEnumAsByte<EArithmeticKeyOperation::Type> Operation;

	UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delta;

	UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float EqualTolerance;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	virtual FString GetStaticDescription() const override;
};
