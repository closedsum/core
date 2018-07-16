// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "CsBTTask_SetKey.generated.h"

class AAIController;

UCLASS(config = Game)
class CSCORE_API UCsBTTask_SetKey : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<EBasicKeyOperation::Type> BasicOperation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	int32 Value_Int;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float Value_Float;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FName Value_Name;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FString Value_String;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FVector Value_Vector;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FRotator Value_Rotator;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;
};
