// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CsBTTask_AimAt.generated.h"

struct FCsBTTask_AimAtMemory
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

class AAIController;

UCLASS(config = Game)
class CSCORE_API UCsBTTask_AimAt : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node)
	bool bResetOnAbort;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ResetTime;

	UPROPERTY(EditAnywhere, Category = Node)
	FName Bone;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;
	
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_AimAtMemory); }
};
