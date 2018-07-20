// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "Types/CsTypes_Character.h"
#include "CsBTTask_PlayMontage.generated.h"

struct FCsBTTask_PlayMontage
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

UCLASS(config = Game)
class CSCORE_API UCsBTTask_PlayMontage : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node)
	bool bStopOnAbort;

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bAnim;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bAnim"))
	class UAnimMontage* Anim;

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	FECsCharacterAnim AnimType;

	UPROPERTY(EditAnywhere, Category = Node)
	bool bWaitUntilFinished;
	UPROPERTY(EditAnywhere, Category = Node)
	bool bLooping;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float PlayRate;

	float InversePlayRate;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_PlayMontage); }
};
