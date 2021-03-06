// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "CsBTTask_StopShoot.generated.h"

UCLASS(config = Game)
class CSCOREDEPRECATED_API UCsBTTask_StopShoot : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
