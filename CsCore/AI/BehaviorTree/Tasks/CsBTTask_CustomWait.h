// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "Types/CsTypes_BehaviorTree.h"
#include "CsBTTask_CustomWait.generated.h"

struct FCsBTTask_CustomWaitMemory
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

UCLASS(config = Game)
class CSCORE_API UCsBTTask_CustomWait : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node)
	TEnumAsByte<ECsBTTask_LogicalOperator::Type> Operation;

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bTime;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bTime"))
	float Time;
	
	UPROPERTY(EditAnywhere, Category = Node)
	TArray<FCsBTTask_KeyValue_Compare> Keys;

public:

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_CustomWaitMemory); }
};
