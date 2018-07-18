// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_Shoot.h"
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

UCsBTTask_Shoot::UCsBTTask_Shoot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Shoot");
	bNotifyTick = true;
}

EBTNodeResult::Type UCsBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return EBTNodeResult::Failed;

	ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

	if (!Pawn)
		return EBTNodeResult::Failed;

	if (!bDuration && !bShots)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_Shoot (%s): Either Duration or Shots must be SET. Both can NOT be NOT SET."), *(Pawn->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bDuration && Duration <= 0.0f)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_Shoot (%s): if Duration is SET, Duration must be > 0.0f."), *(Pawn->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bShots && Shots.Min <= 0)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_Shoot (%s): if Shots is SET, Shots.Min must be > 0."), *(Pawn->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_ShootMemory* MyMemory = (FCsBTTask_ShootMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	MyMemory->Shots = FMath::RandRange(Shots.Min, Shots.Max);

	ACsWeapon* Weapon = Pawn->GetCurrentWeapon();

	MyMemory->StartCount = Weapon->FireCount;

	Pawn->StartShoot();

	ACsAIPlayerState* PlayerState = Cast<ACsAIPlayerState>(Pawn->PlayerState);

	Pawn->OnBTTask_Shoot_Start_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
	Pawn->OnBTTask_Shoot_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR
	return EBTNodeResult::InProgress;
}

void UCsBTTask_Shoot::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		FCsBTTask_ShootMemory* MyMemory = (FCsBTTask_ShootMemory*)NodeMemory;
		check(MyMemory);

		MyMemory->ElapsedTime += DeltaSeconds;

		// Check Delay
		if (Delay > 0.0f)
		{
			if (!MyMemory->DelayCompleted)
			{
				if (MyMemory->ElapsedTime >= Delay)
				{
					MyMemory->DelayCompleted = true;
					MyMemory->ElapsedTime	 = DeltaSeconds;
				}
				else
				{
					return;
				}
			}
		}

		ACsAIPawn* Pawn	  = Cast<ACsAIPawn>(AIController->GetPawn());
		ACsWeapon* Weapon = Pawn->GetCurrentWeapon();

		if ((bDuration && MyMemory->ElapsedTime >= Duration) ||
			(bShots && (Weapon->FireCount - MyMemory->StartCount > MyMemory->Shots)))
		{
			Pawn->StopShoot();

			ACsAIPlayerState* PlayerState = Cast<ACsAIPlayerState>(Pawn->PlayerState);

			Pawn->OnBTTask_Shoot_Stop_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_Shoot_Stop_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

EBTNodeResult::Type UCsBTTask_Shoot::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			Pawn->StopShoot();

			ACsAIPlayerState* PlayerState = Cast<ACsAIPlayerState>(Pawn->PlayerState);

			Pawn->OnBTTask_Shoot_Aborted_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_Shoot_Aborted_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR
		}
	}
	return EBTNodeResult::Aborted;
}

void UCsBTTask_Shoot::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FCsBTTask_ShootMemory* MyMemory = (FCsBTTask_ShootMemory*)NodeMemory;
	check(MyMemory);
	Values.Add(FString::Printf(TEXT("%s: ElapsedTime: %f Count: %d"), *Super::GetStaticDescription(), MyMemory->ElapsedTime, MyMemory->StartCount));
}
