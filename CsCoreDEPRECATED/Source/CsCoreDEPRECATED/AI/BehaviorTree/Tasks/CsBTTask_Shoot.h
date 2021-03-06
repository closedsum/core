// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "CsBTTask_Shoot.generated.h"

struct CSCOREDEPRECATED_API FCsBTTask_ShootMemory
{
	bool Completed;
	bool DelayCompleted;
	float ElapsedTime;
	int32 Shots;
	int32 StartCount;

	void Reset()
	{
		Completed = false;
		DelayCompleted = false;
		ElapsedTime = 0.0f;
		Shots = 0;
		StartCount = 0;
	}
};

UCLASS(config = Game)
class CSCOREDEPRECATED_API UCsBTTask_Shoot : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	/** If True, continue shooting until Duration or Shots is completed. If bForever is set, StopShoot must be called manually.
		If False, stop shooting if the Task is aborted. 
	*/
	UPROPERTY(EditAnywhere, Category = Node)
	bool bStopOnAbort;

	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bDuration;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0", editcondition = "bDuration"))
	float Duration;
	
	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bShots;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bShots"))
	FInt32Interval Shots;

	UPROPERTY(EditAnywhere, Category = Node)
	bool bForever;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_ShootMemory); }

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};
