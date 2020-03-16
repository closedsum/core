// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CsBTTask_LookAtAndRotateToFace.generated.h"

struct CSCOREDEPRECATED_API FCsBTTask_LookAtAndRotateToFaceMemory
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
class CSCOREDEPRECATED_API UCsBTTask_LookAtAndRotateToFace : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node)
	bool bResetOnAbort;

	UPROPERTY(EditAnywhere, Category = Node)
	FName Bone;
	/** Success condition when the Actor's facing direction is within delta */
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AngleDeltaForSuccess;
	/** Rate at which to rotate the Actor per second */
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
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
	
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_LookAtAndRotateToFaceMemory); }

protected:

	float CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB) const;
	float GetAngleDeltaForSuccessDot() const { return AngleDeltaForSuccessDot; }
	void CleanUp(AAIController& AIController, uint8* NodeMemory);
};
