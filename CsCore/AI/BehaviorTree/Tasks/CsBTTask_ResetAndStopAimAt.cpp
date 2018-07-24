// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_ResetAndStopAimAt.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"

#include "CsCore.h"
// AI
#include "AI/Pawn/CsAIPawn.h"

UCsBTTask_ResetAndStopAimtAt::UCsBTTask_ResetAndStopAimtAt(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Reset and Stop Aim At");
	bNotifyTick = true;
}

EBTNodeResult::Type UCsBTTask_ResetAndStopAimtAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return EBTNodeResult::Failed;

	APawn* BasePawn = AIController->GetPawn();

	if (!BasePawn)
		return EBTNodeResult::Failed;

	ACsAIPawn* Pawn		 = Cast<ACsAIPawn>(BasePawn);
	UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

	if (!Pawn)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_ResetAndStopAimtAt (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_ResetAndStopAimAtMemory* MyMemory = (FCsBTTask_ResetAndStopAimAtMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	Pawn->ResetAimAt(BlendOutTime);

	if (BlendOutTime <= 0.0f)
	{
		Pawn->StopAimAt();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::InProgress;
}

void UCsBTTask_ResetAndStopAimtAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		FCsBTTask_ResetAndStopAimAtMemory* MyMemory = (FCsBTTask_ResetAndStopAimAtMemory*)NodeMemory;
		check(MyMemory);

		MyMemory->ElapsedTime += DeltaSeconds;

		if (MyMemory->ElapsedTime >= BlendOutTime)
		{
			ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());
			Pawn->StopAimAt();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCsBTTask_ResetAndStopAimtAt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			Pawn->ResetAimAt(0.0f);
			Pawn->StopAimAt();
		}
	}
	return EBTNodeResult::Aborted;
}

void UCsBTTask_ResetAndStopAimtAt::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FCsBTTask_ResetAndStopAimAtMemory* MyMemory = (FCsBTTask_ResetAndStopAimAtMemory*)NodeMemory;
	check(MyMemory);
	Values.Add(FString::Printf(TEXT("%s: ElapsedTime: %f"), *Super::GetStaticDescription(), MyMemory->ElapsedTime));
}

FString UCsBTTask_ResetAndStopAimtAt::GetStaticDescription() const
{
	FString Description = FString::Printf(TEXT("BlendOutTime: %f"), BlendOutTime);

	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}