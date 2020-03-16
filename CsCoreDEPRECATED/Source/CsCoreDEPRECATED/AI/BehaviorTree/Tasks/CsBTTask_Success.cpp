// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_Success.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/CsCVars_AI_BT.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"

// AI
#include "AI/Pawn/CsAIPawn.h"

UCsBTTask_Success::UCsBTTask_Success(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Success");
	bNotifyTick = true;
}

EBTNodeResult::Type UCsBTTask_Success::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Success::ExecuteTask (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Success::ExecuteTask (%s.%s): Succeeded."), *(BasePawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
	return EBTNodeResult::Succeeded;
}