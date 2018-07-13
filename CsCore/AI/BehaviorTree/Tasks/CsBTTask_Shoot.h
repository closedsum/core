// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "CsBTTask_Shoot.generated.h"

struct FCsBTTask_ShootMemory
{
	float ElapsedTime;
	int32 Shots;
	int32 StartCount;

	void Reset()
	{
		ElapsedTime = 0.0f;
		Shots = 0;
		StartCount = 0;
	}
};

UCLASS(config = Game)
class CSCORE_API UCsBTTask_Shoot : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(config, Category = Node, EditAnywhere, meta = (InlineEditConditionToggle))
	bool bDuration;
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (editcondition = "bDuration"))
	float Duration;
	
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (InlineEditConditionToggle))
	bool bShots;
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (editcondition = "bShots"))
	FInt32Interval Shots;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_ShootMemory); }
};
