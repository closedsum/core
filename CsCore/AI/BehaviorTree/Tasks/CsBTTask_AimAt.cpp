// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_AimAt.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Common/CsCommon.h"
// AI
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"
// Data
#include "Data/CsData_Character.h"

UCsBTTask_AimAt::UCsBTTask_AimAt(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Aim At");
	bNotifyTick = true;
	
	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_AimAt, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_AimAt, BlackboardKey));
}

EBTNodeResult::Type UCsBTTask_AimAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return EBTNodeResult::Failed;

	ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

	if (!Pawn)
		return EBTNodeResult::Failed;

	FCsBTTask_AimAtMemory* MyMemory = (FCsBTTask_AimAtMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACsAIPlayerState* PlayerState			 = Cast<ACsAIPlayerState>(Pawn->PlayerState);

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue  = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* ActorValue = Cast<AActor>(KeyValue);

		if (ActorValue)
		{
			AIController->SetFocalPoint(ActorValue->GetActorLocation(), EAIFocusPriority::Gameplay);
			Pawn->AimAtActor(ActorValue);

			Pawn->OnBTTask_AimAtActor_Start_Event.Broadcast(PlayerState->UniqueMappingId, ActorValue);
#if WITH_EDITOR
			Pawn->OnBTTask_AimAtActor_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId, ActorValue);
#endif // #if WITH_EDITOR
			Result = EBTNodeResult::InProgress;
		}
	}
	// Vector
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		const FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		
		AIController->SetFocalPoint(KeyValue, EAIFocusPriority::Gameplay);
		Pawn->AimAtLocation(KeyValue);

		Pawn->OnBTTask_AimAtLocation_Start_Event.Broadcast(PlayerState->UniqueMappingId, KeyValue);
#if WITH_EDITOR
		Pawn->OnBTTask_AimAtLocation_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId, KeyValue);
#endif // #if WITH_EDITOR
		Result = EBTNodeResult::InProgress;
	}
	return Result;
}

void UCsBTTask_AimAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		FCsBTTask_AimAtMemory* MyMemory = (FCsBTTask_AimAtMemory*)NodeMemory;
		check(MyMemory);

		MyMemory->ElapsedTime += DeltaSeconds;

		ACsAIPawn* Pawn			= Cast<ACsAIPawn>(AIController->GetPawn());
		ACsData_Character* Data = Pawn->GetMyData_Character();

		if (MyMemory->ElapsedTime >= Data->GetAimTime())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UCsBTTask_AimAt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			Pawn->StopAimAt();

			ACsAIPlayerState* PlayerState = Cast<ACsAIPlayerState>(Pawn->PlayerState);

			Pawn->OnBTTask_AimAt_Aborted_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_AimAt_Aborted_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR
		}
	}
	return EBTNodeResult::Aborted;
}

void UCsBTTask_AimAt::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc));
}

FString UCsBTTask_AimAt::GetStaticDescription() const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc);
}
