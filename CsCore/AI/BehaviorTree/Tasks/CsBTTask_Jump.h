// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "CsBTTask_Jump.generated.h"

UCLASS(config = Game)
class CSCORE_API UCsBTTask_Jump : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	//UPROPERTY(EditAnywhere, Category = Node)
	//bool bForever;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
