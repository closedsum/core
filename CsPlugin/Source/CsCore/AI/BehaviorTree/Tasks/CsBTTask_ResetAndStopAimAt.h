// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "CsBTTask_ResetAndStopAimAt.generated.h"

struct FCsBTTask_ResetAndStopAimAtMemory
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

UCLASS(config = Game)
class CSCORE_API UCsBTTask_ResetAndStopAimtAt : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float BlendOutTime;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_ResetAndStopAimAtMemory); }
};
