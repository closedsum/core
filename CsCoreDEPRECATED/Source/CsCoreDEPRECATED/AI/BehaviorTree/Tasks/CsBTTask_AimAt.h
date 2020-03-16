// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CsBTTask_AimAt.generated.h"

// Structs
#pragma region

struct CSCOREDEPRECATED_API FCsBTTask_AimAtMemory
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsBTTask_AimAt_ResetOnAbort
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float BlendOutTime;

	FCsBTTask_AimAt_ResetOnAbort()
	{
		BlendOutTime = 0.2f;
	}
	~FCsBTTask_AimAt_ResetOnAbort() {}
};

#pragma endregion Structs

class AAIController;

UCLASS(config = Game)
class CSCOREDEPRECATED_API UCsBTTask_AimAt : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bResetOnAbort;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bResetOnAbort"))
	FCsBTTask_AimAt_ResetOnAbort ResetOnAbort;

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
