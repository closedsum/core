// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_CustomWait.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "CsCore.h"
// AI
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"
// Weapon
#include "Weapon/CsWeapon.h"
 
// Cache
#pragma region

namespace ECsBTTaskCustomWaitCache
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
}

EBTNodeResult::Type UCsBTTask_CustomWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return EBTNodeResult::Failed;

	ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

	if (!Pawn)
		return EBTNodeResult::Failed;

	if (!bTime && Keys.Num() == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_Shoot (%s): Either Time must be SET or there must be AT LEAST 1 Key Added to Keys."), *(Pawn->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_CustomWaitMemory* MyMemory = (FCsBTTask_CustomWaitMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	for (FCsBTTask_KeyValue& Key : Keys)
	{
		Key.Init(ECsBTTaskCustomWaitCache::Str::ExecuteTask);

		if (!Key.IsValid())
			return EBTNodeResult::Failed;
	}
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

		bool Pass = bTime && MyMemory->ElapsedTime >= Time;

		const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

		for (FCsBTTask_KeyValue& Key : Keys)
		{
			if (Operation == ECsBTTask_LogicalOperator::And)
				Pass &= Key.Evaluate(MyBlackboard);
			else
			if (Operation == ECsBTTask_LogicalOperator::Or)
				Pass |= Key.Evaluate(MyBlackboard);
		}

		if (Pass)
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
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

	// WARNING: Results might be off by 1 frame. If so, update FCsBTTask_KeyValue::GetStaticDescription to NOT include the Results
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	const FString OperationAsString			 = TEXT(" ") + ECsBTTask_LogicalOperator::ToSymbol(Operation) + TEXT(" ");

	const int32 Count = Keys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (I == 0 && bTime)
			Description += OperationAsString;

		Description += Keys[I].GetStaticDescription(MyBlackboard);

		if (I > 0 && I < Count - 1)
			Description += OperationAsString;
	}
	Values.Add(Description);
}
