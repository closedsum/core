// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "AI/BehaviorTree/CsTypes_BehaviorTree.h"
#include "CsBTTask_CustomWait.generated.h"

struct CSCOREDEPRECATED_API FCsBTTask_CustomWaitMemory
{
	float ElapsedTime;
	int32 ElapsedFrames;

	void Reset()
	{
		ElapsedTime = 0.0f;
		ElapsedFrames = 0;
	}
};

UCLASS(config = Game)
class CSCOREDEPRECATED_API UCsBTTask_CustomWait : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node)
	ECsBTTask_LogicalOperator Operation;

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bTime;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bTime", ClampMin = "0.0", UIMin = "0.0"))
	float Time;
	
	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bFrames;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bFrames", ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, Category = Node)
	TArray<FCsBTTask_KeyValue_Compare> Keys;

public:

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_CustomWaitMemory); }

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};
