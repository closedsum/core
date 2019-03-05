// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CsBTTask_CustomRotateToFaceBBEntry.generated.h"

struct FCsBTTask_CustomRotateToFaceBBEntryMemory
{
	AActor* FocusActorSet;
	FVector FocusLocationSet;
	bool bActorSet;

	void Reset()
	{
		FocusActorSet = nullptr;
		FocusLocationSet = FAISystem::InvalidLocation;
		bActorSet = false;
	}
};

class AAIController;

UCLASS(config = Game)
class CSCORE_API UCsBTTask_CustomRotateToFaceBBEntry : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:
	/** Success condition when the Actor's facing direction is within delta */
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float AngleDeltaForSuccess;
	/** Rate at which to rotate the Actor per second */
	UPROPERTY(config, Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float RotationRate;

private:
	/** Cached AngleDeltaForSuccess tangent value */
	float AngleDeltaForSuccessDot;

public:

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;
	
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_CustomRotateToFaceBBEntryMemory); }

protected:

	float CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB) const;
	float GetAngleDeltaForSuccessDot() const { return AngleDeltaForSuccessDot; }
	void CleanUp(AAIController& AIController, uint8* NodeMemory);
};
