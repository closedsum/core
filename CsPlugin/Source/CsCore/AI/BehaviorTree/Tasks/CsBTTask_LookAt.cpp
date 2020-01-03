// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_LookAt.h"
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

// Enums
#pragma region

	// BTTask_LookAtType
namespace NCsBTTask_LookAtType
{
	namespace Ref
	{
		CSCORE_API const Type UntilAligned = EMCsBTTask_LookAtType::Get().Add(Type::UntilAligned, TEXT("UntilAligned"), TEXT("Until Aligned"));
		CSCORE_API const Type Timed = EMCsBTTask_LookAtType::Get().Add(Type::Timed, TEXT("Timed"));
		CSCORE_API const Type Forever = EMCsBTTask_LookAtType::Get().Add(Type::Forever, TEXT("Forever"));
		CSCORE_API const Type ECsBTTask_LookAtType_MAX = EMCsBTTask_LookAtType::Get().Add(Type::ECsBTTask_LookAtType_MAX, TEXT("ECsBTTask_LookAtType_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsBTTask_LookAtType_MAX;
}

#pragma endregion Enums

UCsBTTask_LookAt::UCsBTTask_LookAt(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Look At");
	bNotifyTick = true;
	
	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAt, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAt, BlackboardKey));

	bResetOnAbort = false;
	Type = ECsBTTask_LookAtType::UntilAligned;
	Rate = 360.0f;
	bTime = false;
	Time = 0.0f;
	Bone = NAME_None;
	AngleDeltaForSuccess = 1.0f;
}

EBTNodeResult::Type UCsBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAt::ExecuteTask (%s.%s): This Task only works with Pawns derived from ACsAIPawn."), *(BasePawn->GetName()), *(BTree->GetName()));
		return EBTNodeResult::Failed;
	}

	FCsBTTask_LookAtMemory* MyMemory = (FCsBTTask_LookAtMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	SetTimeByType();

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
			Pawn->LookAtActor(ActorValue, Bone, Rate, Time);

			Pawn->OnBTTask_LookAtActor_Start_Event.Broadcast(PlayerState->UniqueMappingId, ActorValue);
#if WITH_EDITOR
			Pawn->OnBTTask_LookAtActor_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId, ActorValue);
#endif // #if WITH_EDITOR
			Result = EBTNodeResult::InProgress;
		}
	}
	// Vector
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		const FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		
		Pawn->LookAtLocation(KeyValue, Rate, Time);

		Pawn->OnBTTask_LookAtLocation_Start_Event.Broadcast(PlayerState->UniqueMappingId, KeyValue);
#if WITH_EDITOR
		Pawn->OnBTTask_LookAtLocation_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId, KeyValue);
#endif // #if WITH_EDITOR
		Result = EBTNodeResult::InProgress;
	}

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAt::ExecuteTask (%s.%s): InProgress."), *(Pawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
	return Result;
}

void UCsBTTask_LookAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		// UntilAligned
		if (Type == ECsBTTask_LookAtType::UntilAligned)
		{
			ACsAIPawn* Pawn							 = Cast<ACsAIPawn>(AIController->GetPawn());
			const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
			
			const float Tolerance = FMath::Max(KINDA_SMALL_NUMBER, AngleDeltaForSuccess);

			float AbsDeltaPitch = Tolerance;
			float AbsDeltaYaw   = Tolerance;

			// Object
			if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
			{
				UObject* KeyValue	= MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
				AActor* ActorValue	= Cast<AActor>(KeyValue);

				const FRotator FinalRotation = Pawn->GetFinalLookAtRotation(ActorValue, Bone);
				AbsDeltaPitch				 = UCsLibrary_Common::GetAbsAngleDelta(Pawn->CurrentAimPitch, FinalRotation.Pitch);
				AbsDeltaYaw					 = UCsLibrary_Common::GetAbsAngleDelta(Pawn->CurrentAimYaw, FinalRotation.Yaw);
			}
			// Vector
			else 
			if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
			{
				const FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());

				const FRotator FinalRotation = Pawn->GetFinalLookAtRotation(KeyValue);
				AbsDeltaPitch				 = UCsLibrary_Common::GetAbsAngleDelta(Pawn->CurrentAimPitch, FinalRotation.Pitch);
				AbsDeltaYaw					 = UCsLibrary_Common::GetAbsAngleDelta(Pawn->CurrentAimYaw, FinalRotation.Yaw);
			}

			if (AbsDeltaPitch < Tolerance &&
				AbsDeltaYaw < Tolerance)
			{
#if !UE_BUILD_SHIPPING
				if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

					UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAt::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
				}
#endif // #if !UE_BUILD_SHIPPING
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
		// Timed
		if (Type == ECsBTTask_LookAtType::Timed)
		{
			FCsBTTask_LookAtMemory* MyMemory = (FCsBTTask_LookAtMemory*)NodeMemory;
			check(MyMemory);

			MyMemory->ElapsedTime += DeltaSeconds;

			if (MyMemory->ElapsedTime >= Time)
			{
#if !UE_BUILD_SHIPPING
				if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
				{
					ACsAIPawn* Pawn		 = Cast<ACsAIPawn>(AIController->GetPawn());
					UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

					UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAt::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
				}
#endif // #if !UE_BUILD_SHIPPING
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}

EBTNodeResult::Type UCsBTTask_LookAt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			if (bResetOnAbort)
				Pawn->ResetLookAt(ResetOnAbort.BlendOutRate);
			else
				Pawn->StopLookAt();

			ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

			Pawn->OnBTTask_LookAt_Aborted_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_LookAt_Aborted_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAt::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}
	return EBTNodeResult::Aborted;
}

void UCsBTTask_LookAt::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString Description = BlackboardKey.SelectedKeyName.ToString();

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		// Bone
		if (Bone != NAME_None)
			Description += TEXT(" at Bone: ") + Bone.ToString();
	}

	// Rate
	if (Rate > 0.0f)
		Description += TEXT(" with Rate: ") + FString::SanitizeFloat(Rate);
	else
		Description += TEXT(" immediately");

	// UntilAligned
	if (Type == ECsBTTask_LookAtType::UntilAligned)
	{
		if (Rate > 0.0f)
			Description += TEXT(" until aligned");
	}
	// Timed
	else
	if (Type == ECsBTTask_LookAtType::Timed)
	{
		FCsBTTask_LookAtMemory* MyMemory = (FCsBTTask_LookAtMemory*)NodeMemory;
		check(MyMemory);

		Description += TEXT(" for Time: ") + FString::SanitizeFloat(Time) + TEXT(" (Elpased: ") + FString::SanitizeFloat(MyMemory->ElapsedTime) + TEXT(")");;
	}
	// Forever
	else
	if (Type == ECsBTTask_LookAtType::Forever)
	{
		Description += TEXT(" forever");
	}
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description));
}

FString UCsBTTask_LookAt::GetStaticDescription() const
{
	FString Description = BlackboardKey.SelectedKeyName.ToString();

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		// Bone
		if (Bone != NAME_None)
			Description += TEXT(" at Bone: ") + Bone.ToString();
	}

	// Rate
	if (Rate > 0.0f)
		Description += TEXT(" with Rate: ") + FString::SanitizeFloat(Rate);
	else
		Description += TEXT(" immediately");

	// UntilAligned
	if (Type == ECsBTTask_LookAtType::UntilAligned)
	{
		if (Rate > 0.0f)
			Description += TEXT(" until aligned with Delta Sucess of: ") + FString::SanitizeFloat(AngleDeltaForSuccess) + TEXT(" degs");
	}
	// Timed
	else
	if (Type == ECsBTTask_LookAtType::Timed)
	{
		Description += TEXT(" for Time: ") + FString::SanitizeFloat(Time);
	}
	// Forever
	else
	if (Type == ECsBTTask_LookAtType::Forever)
	{
		Description += TEXT(" forever");
	}
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}

void UCsBTTask_LookAt::SetTimeByType()
{
	// UntilAligned
	if (Type == ECsBTTask_LookAtType::UntilAligned)
	{
		bTime = false;
		Time = 0.0f;
	}
	// Timed
	if (Type == ECsBTTask_LookAtType::Timed)
	{
		bTime = true;

		if (Time <= 0.0f)
			Time = 1.0f;
	}
	// Forever
	if (Type == ECsBTTask_LookAtType::Forever)
	{
		bTime = false;
		
		if (Time >= 0.0f)
			Time = 1.0f;
	}
}

#if WITH_EDITOR

void UCsBTTask_LookAt::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Type
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAt, Type))
	{
		SetTimeByType();

		Super::PostEditChangeProperty(e);
		return;
	}
	// bTime
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAt, Type))
	{
		if (bTime)
		{
			Type = ECsBTTask_LookAtType::Timed;

			if (Time <= 0.0f)
				Time = 1.0f;
		}
		else
		{
			if (Type == ECsBTTask_LookAtType::Timed)
				Type = ECsBTTask_LookAtType::UntilAligned;

			if (Time > 0.0f)
				Time = 0.0f;
		}

		Super::PostEditChangeProperty(e);
		return;
	}
	// Time
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAt, Time))
	{
		if (Time < 0.0f)
		{
			bTime = false;
			Type = ECsBTTask_LookAtType::Forever;
		}
		else
		if (Time > 0.0f)
		{
			bTime = true;
			Type = ECsBTTask_LookAtType::Timed;
		}
		else
		{
			bTime = false;
			Type = ECsBTTask_LookAtType::UntilAligned;
		}

		Super::PostEditChangeProperty(e);
		return;
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR