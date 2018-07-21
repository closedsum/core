// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_PlayMontage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"

#include "CsCore.h"
// AI
#include "AI/Pawn/CsAIPawn.h"
// Data
#include "Data/CsData_Character.h"
// Animation
#include "Animation/CsAnimInstance.h"

UCsBTTask_PlayMontage::UCsBTTask_PlayMontage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Play Montage");
	bNotifyTick = true;

	bStopOnAbort = true;
#if WITH_EDITORONLY_DATA
	bAnim = false;
	Anim = nullptr;
#endif // #if WITH_EDITORONLY_DATA
	bWaitUntilFinished = false;
	bLooping = false;
	PlayRate = 1.0f;
}

EBTNodeResult::Type UCsBTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

#if WITH_EDITORONLY_DATA
	if (bAnim && !Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage (%s.%s): No Anim Set."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITORONLY_DATA
	if (!bAnim)
#endif // #if WITH_EDITORONLY_DATA
	{
		ACsData_Character* Data  = Pawn->GetMyData_Character();
		UAnimMontage* AnimToPlay = Data->GetAnimMontage(AnimType, 0, false);

		if (!AnimToPlay)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage (%s.%s): Data: %s has NO Anim set for AnimType: %s"), *(BasePawn->GetName()), *(BTree->GetName()), *(Data->ShortCode.ToString()), *(AnimType.Name));
			return EBTNodeResult::Failed;
		}
	}

#if WITH_EDITORONLY_DATA
	if (bAnim)
	{
		UAnimInstance* AnimInstance = Pawn->GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(Anim, PlayRate);
	}
	else
#endif // #if WITH_EDITORONLY_DATA
	{
		ACsData_Character* Data = Pawn->GetMyData_Character();
		Data->PlayAnimation(Pawn->GetMesh(), AnimType, 0, PlayRate, bLooping, false);
	}

	if (!bWaitUntilFinished)
		return EBTNodeResult::Succeeded;

	FCsBTTask_PlayMontage* MyMemory = (FCsBTTask_PlayMontage*)NodeMemory;
	check(MyMemory);

	MyMemory->Reset();

	InversePlayRate = 1.0f / PlayRate;

	return EBTNodeResult::InProgress;
}

void UCsBTTask_PlayMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		if (bLooping)
			return;

		FCsBTTask_PlayMontage* MyMemory = (FCsBTTask_PlayMontage*)NodeMemory;
		check(MyMemory);

		MyMemory->ElapsedTime += DeltaSeconds;

		ACsAIPawn* Pawn			  = Cast<ACsAIPawn>(AIController->GetPawn());
		UAnimMontage* CurrentAnim = nullptr;

#if WITH_EDITORONLY_DATA
		if (bAnim)
		{
			CurrentAnim = Anim;
		}
		else
#endif // #if WITH_EDITORONLY_DATA
		{
			ACsData_Character* Data = Pawn->GetMyData_Character();
			CurrentAnim				= Data->GetAnimMontage(AnimType, 0, false);
		}

		const float Time = InversePlayRate * CurrentAnim->GetSectionLength(0);

		if (MyMemory->ElapsedTime > Time)
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


EBTNodeResult::Type UCsBTTask_PlayMontage::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			if (bStopOnAbort)
			{
#if WITH_EDITORONLY_DATA
				if (bAnim)
				{
					UAnimInstance* AnimInstance = Pawn->GetMesh()->GetAnimInstance();
					AnimInstance->Montage_Stop(0.0f, Anim);
				}
				else
#endif // #if WITH_EDITORONLY_DATA
				{
					ACsData_Character* Data = Pawn->GetMyData_Character();
					Data->StopAnimation(Pawn->GetMesh(), AnimType, 0, 0.0f, false);
				}
			}
		}
	}
	return EBTNodeResult::Aborted;
}

void UCsBTTask_PlayMontage::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FCsBTTask_PlayMontage* MyMemory = (FCsBTTask_PlayMontage*)NodeMemory;
	check(MyMemory);
	Values.Add(FString::Printf(TEXT("%s: ElapsedTime: %f Count: %d"), *Super::GetStaticDescription(), MyMemory->ElapsedTime));
}

FString UCsBTTask_PlayMontage::GetStaticDescription() const
{
	FString Description = ECsCached::Str::Empty;

#if WITH_EDITORONLY_DATA
	if (bAnim)
	{
		if (Anim)
			Description += Anim->GetName();
	}
	else
#endif // #if WITH_EDITORONLY_DATA
	{
		Description += AnimType.Name;
	}

	Description += FString::Printf(TEXT(" with PlayRate: %f."), PlayRate);

	if (bWaitUntilFinished)
		Description += TEXT(" Wait until Finsihed.");
	if (bLooping)
		Description += TEXT(" Looping.");
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}