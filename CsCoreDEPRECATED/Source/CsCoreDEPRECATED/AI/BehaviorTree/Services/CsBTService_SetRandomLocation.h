// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/BTService.h"
#include "CsBTService_SetRandomLocation.generated.h"

UCLASS()
class CSCOREDEPRECATED_API UCsBTService_SetRandomLocation : public UBTService
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius;

	UPROPERTY(Category = Node, EditAnywhere)
	TSubclassOf<UNavigationQueryFilter> FilterClass;

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardKey;
};