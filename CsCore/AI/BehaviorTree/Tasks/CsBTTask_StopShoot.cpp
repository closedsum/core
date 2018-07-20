// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_StopShoot.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"

#include "CsCore.h"
// AI
#include "AI/Pawn/CsAIPawn.h"

UCsBTTask_StopShoot::UCsBTTask_StopShoot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Stop Shoot");
	bNotifyTick = true;
}

EBTNodeResult::Type UCsBTTask_StopShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_Shoot (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (!Pawn->IsShooting())
		return EBTNodeResult::Succeeded;

	Pawn->StopShoot();
	return EBTNodeResult::InProgress;
}

void UCsBTTask_StopShoot::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

		if (!Pawn->IsShooting())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}