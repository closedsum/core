// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_Shoot.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/Tasks/CsCVars_AI_BT_Task.h"

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
#include "Weapon/CsWeapon_DEPRECATED.h"

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

	if (!bDuration && !bShots && !bForever)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Either Duration, Shots, or Forever must be SET. All can NOT be NOT SET."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bDuration && bForever)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Either Duration or Forever must be SET. Both can NOT be NOT SET."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bDuration && Duration <= 0.0f)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): if Duration is SET, Duration must be > 0.0f."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bShots && bForever)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): Either Shots or Forever must be SET. Both can NOT be NOT SET."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	if (bShots && Shots.Min <= 0)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): if Shots is SET, Shots.Min must be > 0."), *(Pawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_ShootMemory* MyMemory = (FCsBTTask_ShootMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	MyMemory->Shots = FMath::RandRange(Shots.Min, Shots.Max);

	ACsWeapon_DEPRECATED* Weapon = Pawn->GetCurrentWeapon();

	MyMemory->StartCount = Weapon->FireCount;

	// If NO Delay, Start Shooting
	if (Delay <= 0.0f)
	{
		if (bStopOnAbort || bForever)
		{
			Pawn->StartShoot();
		}
		// If do NOT Stop Shooting on Abort, then run a coroutine on the Pawn
		else
		{
			if (bShots)
				Pawn->StartShootForCount(MyMemory->Shots);
			else
			if (bDuration)
				Pawn->StartShootForDuration(Duration);
		}
	}

	ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

	Pawn->OnBTTask_Shoot_Start_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
	Pawn->OnBTTask_Shoot_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::ExecuteTask (%s.%s): InProgress."), *(BasePawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
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
				// Start Shooting
				if (MyMemory->ElapsedTime >= Delay)
				{
					MyMemory->DelayCompleted = true;
					MyMemory->ElapsedTime	 = DeltaSeconds;

					if (bStopOnAbort || bForever)
					{
						Pawn->StartShoot();
					}
					// If do NOT Stop Shooting on Abort, then run a coroutine on the Pawn
					else
					{
						if (bShots)
							Pawn->StartShootForCount(MyMemory->Shots);
						else
						if (bDuration)
							Pawn->StartShootForDuration(Duration);
					}
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
		ACsWeapon_DEPRECATED* Weapon = Pawn->GetCurrentWeapon();

		if (!MyMemory->Completed)
		{
			if ((bDuration && MyMemory->ElapsedTime >= Duration) ||
				(bShots && (Weapon->FireCount - MyMemory->StartCount >= MyMemory->Shots)))
			{
				if (bStopOnAbort)
					Pawn->StopShoot();

				MyMemory->Completed = true;

				ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

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
			{
#if !UE_BUILD_SHIPPING
				if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

					UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
				}
#endif // #if !UE_BUILD_SHIPPING
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
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

			ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

			Pawn->OnBTTask_Shoot_Aborted_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_Shoot_Aborted_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_Shoot::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
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
	FString Description = NCsCached::Str::Empty;

	if (Delay > 0.0f)
		Description += TEXT("Delay: ") + FString::SanitizeFloat(Delay) + TEXT(" ");

	if (bForever)
	{
		Description += TEXT("Forever");
	}
	else
	if (bDuration)
	{
		Description += TEXT("Duration: ") + FString::SanitizeFloat(Duration);
	}
	else
	if (bShots)
	{
		if (Shots.Min == Shots.Max)
			Description += FString::Printf(TEXT("Shots: %d"), Shots.Min);
		else
			Description += FString::Printf(TEXT("Shots: betwween %d-%d"),Shots.Min, Shots.Max);
	}

	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}

#if WITH_EDITOR

void UCsBTTask_Shoot::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Duration
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Shoot, Duration))
	{
		if (bDuration)
		{
			bShots = false;
			bForever = false;
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	// Shots
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Shoot, Shots))
	{
		if (bShots)
		{
			bDuration = false;
			bForever = false;
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
		Super::PostEditChangeProperty(e);
		return;
	}
	// Shots.Max
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FInt32Interval, Min))
	{
		if (Shots.Max <= 0)
		{
			Shots.Max = 1;
			Shots.Min = FMath::Max(1, Shots.Min);
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	// bForever
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_Shoot, bForever))
	{
		if (bForever)
		{
			bShots = false;
			bDuration = false;
		}
		Super::PostEditChangeProperty(e);
		return;
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR
