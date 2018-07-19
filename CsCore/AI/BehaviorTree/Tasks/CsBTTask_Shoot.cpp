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

	bStopOnAbort = true;
	Shots.Min = 0.0f;
	Shots.Max = 0.0f;
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

	if (Delay <= 0.0f)
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

		ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

		// Check Delay
		if (Delay > 0.0f)
		{
			if (!MyMemory->DelayCompleted)
			{
				if (MyMemory->ElapsedTime >= Delay)
				{
					MyMemory->DelayCompleted = true;
					MyMemory->ElapsedTime	 = DeltaSeconds;

					Pawn->StartShoot();
				}
				else
				{
					return;
				}
			}
		}

		if (bForever)
			return;

		// Check finished Shooting (Duration or Shots)
		ACsWeapon* Weapon = Pawn->GetCurrentWeapon();

		if (!MyMemory->Completed)
		{
			if ((bDuration && MyMemory->ElapsedTime >= Duration) ||
				(bShots && (Weapon->FireCount - MyMemory->StartCount > MyMemory->Shots)))
			{
				Pawn->StopShoot();

				MyMemory->Completed = true;

				ACsAIPlayerState* PlayerState = Cast<ACsAIPlayerState>(Pawn->PlayerState);

				Pawn->OnBTTask_Shoot_Stop_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
				Pawn->OnBTTask_Shoot_Stop_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR
			}
		}
		else
		{
			// Check weapon has actually stopped shooting
			if (!Pawn->IsShooting())
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
			if (bStopOnAbort)
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

FString UCsBTTask_Shoot::GetStaticDescription() const
{
	FString Description = ECsCached::Str::Empty;

	if (Delay > 0.0f)
		Description += TEXT("Delay: ") + FString::SanitizeFloat(Delay) + TEXT(" ");

	if (bDuration)
		Description += TEXT("Duration: ") + FString::SanitizeFloat(Duration);
	else
	if (bShots)
		Description += FString::Printf(TEXT("Shots: %d-%d"),Shots.Min, Shots.Max);

	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}

#if WITH_EDITOR

void UCsBTTask_Shoot::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// bDuration
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Shoot, bDuration))
	{
		if (bDuration)
		{
			bShots = false;
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	// bShots
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Shoot, bShots))
	{
		if (bShots)
		{
			bDuration = false;
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	// Shots.Min
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FInt32Interval, Min))
	{
		if (Shots.Min <= 0)
		{
			Shots.Min = 1;
			Shots.Max = FMath::Max(Shots.Min, Shots.Max);
		}
	}
	// Shots.Max
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FInt32Interval, Min))
	{
		if (Shots.Max <= 0)
		{
			Shots.Max = 1;
			Shots.Min = FMath::Max(1, Shots.Min);
		}
	}
	// bForever
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Shoot, bForever))
	{
		if (bForever)
		{
			bShots = false;
			bDuration = false;
		}
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR
