// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_PlayMontage.h"
#include "CsCore.h"
#include "CsCVars.h"

// Behavior Tree
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
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
	bSyncCurrentViewFromBone = false;
	BoneForCurrentView = NAME_None;
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
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::ExecuteTask (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

#if WITH_EDITORONLY_DATA
	if (bAnim && !Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::ExecuteTask (%s.%s): No Anim Set."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITORONLY_DATA
	if (!bAnim)
#endif // #if WITH_EDITORONLY_DATA
	{
		UCsData_Character* Data  = Pawn->GetMyData_Character();
		UAnimMontage* AnimToPlay = Data->GetAnimMontage(AnimType, 0, false);

		if (!AnimToPlay)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::ExecuteTask (%s.%s): Data: %s has NO Anim set for AnimType: %s"), *(BasePawn->GetName()), *(BTree->GetName()), *(Data->ShortCode.ToString()), *(AnimType.Name));
			return EBTNodeResult::Failed;
		}
	}

	if (bSyncCurrentViewFromBone)
		Pawn->SyncCurrentViewFromBone(BoneForCurrentView);

#if WITH_EDITORONLY_DATA
	if (bAnim)
	{
		UAnimInstance* AnimInstance = Pawn->GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(Anim, PlayRate);
	}
	else
#endif // #if WITH_EDITORONLY_DATA
	{
		UCsData_Character* Data = Pawn->GetMyData_Character();
		Data->PlayAnimation(Pawn->GetMesh(), AnimType, 0, PlayRate, bLooping, false);
	}

	if (!bWaitUntilFinished)
	{
#if !UE_BUILD_SHIPPING
		if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::ExecuteTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
		}
#endif // #if !UE_BUILD_SHIPPING
		return EBTNodeResult::Succeeded;
	}

	FCsBTTask_PlayMontage* MyMemory = (FCsBTTask_PlayMontage*)NodeMemory;
	check(MyMemory);

	MyMemory->Reset();

	InversePlayRate = 1.0f / PlayRate;

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::ExecuteTask (%s.%s): InProgress."), *(Pawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
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
			UCsData_Character* Data = Pawn->GetMyData_Character();
			CurrentAnim				= Data->GetAnimMontage(AnimType, 0, false);
		}

		const float Time = InversePlayRate * CurrentAnim->GetSectionLength(0);

		if (MyMemory->ElapsedTime > Time)
		{
			if (bSyncCurrentViewFromBone)
				Pawn->StopSyncCurrentViewFromBone();

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
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
					AnimInstance->Montage_Stop(StopOnAbort.BlendOutTime, Anim);
				}
				else
#endif // #if WITH_EDITORONLY_DATA
				{
					UCsData_Character* Data = Pawn->GetMyData_Character();
					Data->StopAnimation(Pawn->GetMesh(), AnimType, 0, StopOnAbort.BlendOutTime, false);
				}

				if (bSyncCurrentViewFromBone &&
					StopOnAbort.bStopSyncCurrentViewFromBone)
				{
					Pawn->StopSyncCurrentViewFromBone();
				}
			}
#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_PlayMontage::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
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
	FString Description = NCsCached::Str::Empty;

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