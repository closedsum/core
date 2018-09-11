// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "Types/CsTypes_Character.h"
#include "CsBTTask_PlayMontage.generated.h"

// Structs
#pragma region

struct FCsBTTask_PlayMontage
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsBTTask_PlayMontage_StopOnAbort
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float BlendOutTime;
	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bStopSyncCurrentViewFromBone;

	FCsBTTask_PlayMontage_StopOnAbort()
	{
		BlendOutTime = 0.0f;
		bStopSyncCurrentViewFromBone = false;
	}
	~FCsBTTask_PlayMontage_StopOnAbort(){}
};

#pragma endregion Structs

UCLASS(config = Game)
class CSCORE_API UCsBTTask_PlayMontage : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bStopOnAbort;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bStopOnAbort"))
	FCsBTTask_PlayMontage_StopOnAbort StopOnAbort;


#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bAnim;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bAnim"))
	class UAnimMontage* Anim;
#endif WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = Node)
	FECsCharacterAnim AnimType;

	UPROPERTY(EditAnywhere, Category = Node)
	bool bWaitUntilFinished;
	UPROPERTY(EditAnywhere, Category = Node)
	bool bLooping;
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float PlayRate;

	float InversePlayRate;

	/** Use the Bone rotation to determine the CurrentView */
	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bSyncCurrentViewFromBone;
	/** Bone used to determine the CurrentView */
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bSyncCurrentViewFromBone"))
	FName BoneForCurrentView;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_PlayMontage); }
};
