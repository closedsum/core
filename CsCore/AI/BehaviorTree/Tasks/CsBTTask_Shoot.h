// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CsBTTask_Shoot.generated.h"

struct FCsBTTask_ShootMemory
{
	float ElapsedTime;
	int32 Count;

	void Reset()
	{
		ElapsedTime = 0.0f;
		Count = 0;
	}
};

class AAIController;

UCLASS(config = Game)
class CSCORE_API UCsBTTask_Shoot : public UBTTask_BlackboardBase
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
	virtual FString GetStaticDescription() const override;
	
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_ShootMemory); }
};
