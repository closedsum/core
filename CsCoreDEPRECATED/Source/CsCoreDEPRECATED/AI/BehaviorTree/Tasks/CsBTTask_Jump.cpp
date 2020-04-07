// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_Jump.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/Tasks/CsCVars_AI_BT_Task.h"

// Behavior Tree
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"

UCsBTTask_Jump::UCsBTTask_Jump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Jump");
	bNotifyTick = true;

	// accept only actors, vectors, and rotators
	BlackboardKey.AllowNoneAsValue(true);
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_Jump, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_Jump, BlackboardKey));
	BlackboardKey.AddRotatorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_Jump, BlackboardKey));

	bSpeedXYAsPercent = true;
	SpeedXYAsPercent = 1.0f;
}

EBTNodeResult::Type UCsBTTask_Jump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Jump::ExecuteTask (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	FVector Direction = FVector::ZeroVector;
	bool UseDistance = false;
	float Distance = 0.0f;

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue  = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* ActorValue = Cast<AActor>(KeyValue);

		const FVector Destination	= ActorValue->GetActorLocation();
		const FVector DestinationXY = FVector(Destination.X, Destination.Y, 0.0f);
		const FVector& Location		= Pawn->CurrentBodyLocation;
		const FVector LocationXY	= FVector(Location.X, Location.Y, 0.0f);
		const FVector MeToGoal		= DestinationXY - LocationXY;
		Distance					= MeToGoal.Size2D();

		const float Tolerance = Pawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
		Direction			  = Distance <= Tolerance ? FVector::ZeroVector : MeToGoal / Distance;

		UseDistance = Distance > Tolerance;
	}
	// Vector
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		const FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		
		const FVector KeyValueXY = FVector(KeyValue.X, KeyValue.Y, 0.0f);
		const FVector& Location  = Pawn->CurrentBodyLocation;
		const FVector LocationXY = FVector(Location.X, Location.Y, 0.0f);
		const FVector MeToGoal	 = KeyValueXY - LocationXY;
		Distance				 = MeToGoal.Size2D();

		const float Tolerance   = Pawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
		Direction				= Distance <= Tolerance ? FVector::ZeroVector : MeToGoal / Distance;

		UseDistance = Distance > Tolerance;
	}
	// Rotator
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
	{
		const FRotator KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Rotator>(BlackboardKey.GetSelectedKeyID());
		Direction				= KeyValue.Vector();
	}

	if (UseDistance)
	{
		Pawn->SetStartJumpEventInfoConstrainedBySpeedXY(Direction, Distance);
	}
	else
	if (bTime)
	{
		Pawn->SetStartJumpEventInfoByTime(Direction, Time, bSpeedXYAsPercent ? SpeedXYAsPercent : 1.0f);
	}
	else
	if (bHeight)
	{
		Pawn->SetStartJumpEventInfoByHeight(Direction, Height, bSpeedXYAsPercent ? SpeedXYAsPercent : 1.0f);
	}
	else
	{
		Pawn->SetStartJumpEventInfo(Direction, bSpeedXYAsPercent ? SpeedXYAsPercent : 1.0f);
	}

	Pawn->StartJump();

	ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

	Pawn->OnBTTask_Jump_Start_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
	Pawn->OnBTTask_Jump_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): InProgress."), *(BasePawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
	return EBTNodeResult::InProgress;
}

void UCsBTTask_Jump::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

		if (Pawn->bJumpFinished)
		{
			ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

			Pawn->OnBTTask_Jump_Finish_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_Jump_Finish_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Jump::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCsBTTask_Jump::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Jump::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}
	return EBTNodeResult::Aborted;
}

#if WITH_EDITOR

void UCsBTTask_Jump::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// bTime
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Jump, Time))
	{
		if (bTime)
		{
			if (Time <= 0.0f)
				Time = 1.0f;

			bHeight = false;
		}
	}
	// bHeight
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Jump, Height))
	{
		if (bHeight)
		{
			if (Height <= 0.0f)
				Height = 300.0f;

			bTime = false;
		}
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR
