// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_AimAt.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"

// Behavior Tree
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
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

	bResetOnAbort = true;
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
	ACsAIPlayerState* PlayerState			 = Pawn->GetPlayerState<ACsAIPlayerState>();

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue  = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* ActorValue = Cast<AActor>(KeyValue);

		if (ActorValue)
		{
			Pawn->AimAtActor(ActorValue, Bone);

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
		
		Pawn->AimAtLocation(KeyValue);

		Pawn->OnBTTask_AimAtLocation_Start_Event.Broadcast(PlayerState->UniqueMappingId, KeyValue);
#if WITH_EDITOR
		Pawn->OnBTTask_AimAtLocation_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId, KeyValue);
#endif // #if WITH_EDITOR
		Result = EBTNodeResult::InProgress;
	}

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_AimAt::ExecuteTask (%s.%s): InProgress."), *(Pawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
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
		UCsData_Character* Data = Pawn->GetMyData_Character();

		if (MyMemory->ElapsedTime >= Data->GetAimTime())
		{
#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_AimAt::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCsBTTask_AimAt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			Pawn->StopAimAt();

			if (bResetOnAbort)
				Pawn->ResetAimAt(ResetOnAbort.BlendOutTime);

			ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

			Pawn->OnBTTask_AimAt_Aborted_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_AimAt_Aborted_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_AimAt::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
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
