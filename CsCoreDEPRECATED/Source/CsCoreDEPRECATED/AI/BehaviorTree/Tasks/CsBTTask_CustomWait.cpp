// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_CustomWait.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/CsCVars_AI_BT.h"

// Behavior Tree
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"
// Weapon
#include "Weapon/CsWeapon.h"
 
// Cache
#pragma region

namespace NCsBTTaskCustomWaitCache
{
	namespace Str
	{
		const FString ExecuteTask = TEXT("UCsBTTask_CustomWait::ExecuteTask");
	}
}

#pragma endregion Cache

UCsBTTask_CustomWait::UCsBTTask_CustomWait(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Custom Wait");
	bNotifyTick = true;

	bTime = false;
	Time = 0.0f;
	bFrames = false;
	Frames = 0;
}

void UCsBTTask_CustomWait::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		for (FCsBTTask_KeyValue_Compare& Key : Keys)
		{
			Key.Key.ResolveSelectedKey(*BBAsset);
		}
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies a blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UCsBTTask_CustomWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (!bTime && !bFrames && Keys.Num() == CS_EMPTY)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Either Time must be SET, Frames must be SET, or there must be AT LEAST 1 Key Added to Keys."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bTime && bFrames)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Both Time and Frames can NOT be SET at the same time."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bTime && Time <= 0.0f)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Time must be > 0.0f."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bFrames && Frames <= 0)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Frames must be > 0."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_CustomWaitMemory* MyMemory = (FCsBTTask_CustomWaitMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	for (FCsBTTask_KeyValue_Compare& Key : Keys)
	{
		Key.Init(NCsBTTaskCustomWaitCache::Str::ExecuteTask);

		if (!Key.IsValid())
			return EBTNodeResult::Failed;
	}

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_CustomWait::ExecuteTask (%s.%s): InProgress."), *(Pawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
	return EBTNodeResult::InProgress;
}

void UCsBTTask_CustomWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		FCsBTTask_CustomWaitMemory* MyMemory = (FCsBTTask_CustomWaitMemory*)NodeMemory;
		check(MyMemory);

		MyMemory->ElapsedTime += DeltaSeconds;
		++(MyMemory->ElapsedFrames);

		bool Pass = (bTime && MyMemory->ElapsedTime >= Time) || (bFrames && MyMemory->ElapsedFrames >= Frames);

		const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

		for (FCsBTTask_KeyValue_Compare& Key : Keys)
		{
			if (Operation == ECsBTTask_LogicalOperator::And)
				Pass &= Key.Evaluate(MyBlackboard);
			else
			if (Operation == ECsBTTask_LogicalOperator::Or)
				Pass |= Key.Evaluate(MyBlackboard);
		}

		if (Pass)
		{
#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				ACsAIPawn* Pawn		 = Cast<ACsAIPawn>(AIController->GetPawn());
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_CustomWait::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

void UCsBTTask_CustomWait::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString Description = Super::GetStaticDescription() + TEXT(": ");

	if (bTime)
	{
		FCsBTTask_CustomWaitMemory* MyMemory = (FCsBTTask_CustomWaitMemory*)NodeMemory;
		check(MyMemory);

		Description += FString::Printf(TEXT("Elapsed: %f"), MyMemory->ElapsedTime);
	}

	// WARNING: Results might be off by 1 frame. If so, update FCsBTTask_KeyValue_Compare::GetStaticDescription to NOT include the Results
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	const FString OperationAsString			 = TEXT(" ") + ECsBTTask_LogicalOperator::ToSymbol(Operation) + TEXT(" ");

	const int32 Count = Keys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (I == 0 && bTime)
			Description += OperationAsString;

		Description += Keys[I].GetRuntimeDescription(MyBlackboard);

		if (I > 0 && I < Count - 1)
			Description += OperationAsString;
	}
	Values.Add(Description);
}

FString UCsBTTask_CustomWait::GetStaticDescription() const
{
	FString Description = NCsCached::Str::Empty;

	if (bTime)
	{
		Description += FString::Printf(TEXT("Time: %f"), Time);
	}

	const FString OperationAsString = TEXT(" ") + ECsBTTask_LogicalOperator::ToSymbol(Operation) + TEXT(" ");

	const int32 Count = Keys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (I == 0 && bTime)
			Description += OperationAsString;

		Description += Keys[I].GetStaticDescription();

		if (I > 0 && I < Count - 1)
			Description += OperationAsString;
	}
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}

#if WITH_EDITOR

void UCsBTTask_CustomWait::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Time
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomWait, Time))
	{
		if (bTime)
		{
			bFrames = false;
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	// Frames
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomWait, Frames))
	{
		if (bFrames)
		{
			bTime = false;
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR