// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CsBTTask_Jump.generated.h"

UCLASS(config = Game)
class CSCORE_API UCsBTTask_Jump : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node)
	bool bTime;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	UPROPERTY(EditAnywhere, Category = Node)
	bool bHeight;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Height;

	UPROPERTY(EditAnywhere, Category = Node)
	bool bSpeedXYAsPercent;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SpeedXYAsPercent;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};
