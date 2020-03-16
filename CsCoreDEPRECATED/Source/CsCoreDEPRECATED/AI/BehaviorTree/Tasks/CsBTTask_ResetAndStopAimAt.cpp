// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_ResetAndStopAimAt.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/CsCVars_AI_BT.h"

// Behavior Tree
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_ResetAndStopAimtAt::ExecuteTask (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_ResetAndStopAimAtMemory* MyMemory = (FCsBTTask_ResetAndStopAimAtMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	Pawn->ResetAimAt(BlendOutTime);

	if (BlendOutTime <= 0.0f)
	{
#if !UE_BUILD_SHIPPING
		if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_ResetAndStopAimtAt::ExecuteTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
		}
#endif // #if !UE_BUILD_SHIPPING
		return EBTNodeResult::Succeeded;
	}

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_ResetAndStopAimtAt::ExecuteTask (%s.%s): InProgress."), *(Pawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
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

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_ResetAndStopAimtAt::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
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

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_ResetAndStopAimtAt::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
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