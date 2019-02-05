// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_LookAtAndRotateToFace.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// Behavior Tree
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"

UCsBTTask_LookAtAndRotateToFace::UCsBTTask_LookAtAndRotateToFace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AngleDeltaForSuccessDot(10.f)
{
	NodeName = TEXT("Look at and Rotate to Face");
	bNotifyTick = true;
	
	Bone = NAME_None;
	RotationRate = 360.0f;

	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAtAndRotateToFace, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_LookAtAndRotateToFace, BlackboardKey));
}

void UCsBTTask_LookAtAndRotateToFace::PostInitProperties()
{
	Super::PostInitProperties();

	AngleDeltaForSuccessDot = FMath::Cos(FMath::DegreesToRadians(AngleDeltaForSuccess));
}

void UCsBTTask_LookAtAndRotateToFace::PostLoad()
{
	Super::PostLoad();

	AngleDeltaForSuccessDot = FMath::Cos(FMath::DegreesToRadians(AngleDeltaForSuccess));
}

EBTNodeResult::Type UCsBTTask_LookAtAndRotateToFace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == NULL || AIController->GetPawn() == NULL)
	{
		return EBTNodeResult::Failed;
	}

	FCsBTTask_LookAtAndRotateToFaceMemory* MyMemory = (FCsBTTask_LookAtAndRotateToFaceMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	ACsAIPawn* Pawn							 = Cast<ACsAIPawn>(AIController->GetPawn());
	const FVector PawnLocation				 = Pawn->GetActorLocation();
	const FVector PawnForward				 = Pawn->GetActorForwardVector();
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	float AngleDifference = 0.0f;

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue  = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* ActorValue = Cast<AActor>(KeyValue);

		if (ActorValue != NULL)
		{
			AngleDifference = CalculateAngleDifferenceDot(Pawn->GetActorForwardVector(), (ActorValue->GetActorLocation() - PawnLocation).GetSafeNormal2D());
			
			if (AngleDifference >= AngleDeltaForSuccessDot)
			{
				Result = EBTNodeResult::Succeeded;
			}
			else
			{
				const FVector CurrentFocalPoint = PawnLocation + 10000.0f * PawnForward;

				AIController->SetFocalPoint(CurrentFocalPoint, EAIFocusPriority::Gameplay);
				MyMemory->FocusActorSet	   = ActorValue;
				MyMemory->FocusLocationSet = ActorValue->GetActorLocation();
				MyMemory->bActorSet		   = true;

				Pawn->LookAtActor(ActorValue, Bone, 0.5f * RotationRate, -1.0f /*Forever*/);

				Result = EBTNodeResult::InProgress;
			}
		}
	}
	// Vector
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		const FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		
		if (FAISystem::IsValidLocation(KeyValue))
		{
			AngleDifference = CalculateAngleDifferenceDot(PawnForward, (KeyValue - PawnLocation).GetSafeNormal2D());

			if (AngleDifference >= AngleDeltaForSuccessDot)
			{
				Result = EBTNodeResult::Succeeded;
			}
			else
			{
				const FVector CurrentFocalPoint = PawnLocation + 10000.0f * PawnForward;

				AIController->SetFocalPoint(CurrentFocalPoint, EAIFocusPriority::Gameplay);
				MyMemory->FocusLocationSet = KeyValue;

				Pawn->LookAtLocation(KeyValue, 0.5f * RotationRate, -1.0f /*Forever*/);

				Result = EBTNodeResult::InProgress;
			}
		}
	}

	if (Result == EBTNodeResult::InProgress)
	{
		ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

		Pawn->OnBTTask_LookAtAndRotateToFace_Start_Event.Broadcast(PlayerState->UniqueMappingId, AngleDifference, RotationRate);
#if WITH_EDITOR
		Pawn->OnBTTask_LookAtAndRotateToFace_Start_ScriptEvent.Broadcast(PlayerState->UniqueMappingId, AngleDifference, RotationRate);
#endif // #if WITH_EDITOR
	}

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UBehaviorTree* BTree		 = OwnerComp.GetCurrentTree();
		const FString ResultAsString = Result == EBTNodeResult::Succeeded ? TEXT("Succeeded") : TEXT("InProgress");

		UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAtAndRotateToFace::ExecuteTask (%s.%s): %s."), *(Pawn->GetName()), *(BTree->GetName()), *ResultAsString);
	}
#endif // #if !UE_BUILD_SHIPPING
	return Result;
}

void UCsBTTask_LookAtAndRotateToFace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == NULL || AIController->GetPawn() == NULL)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

		FCsBTTask_LookAtAndRotateToFaceMemory* MyMemory = (FCsBTTask_LookAtAndRotateToFaceMemory*)NodeMemory;
		check(MyMemory);

		const FVector PawnDirection			= Pawn->GetActorForwardVector();
		const float CurrentYaw				= PawnDirection.Rotation().Yaw;
		const FVector Destination			= MyMemory->bActorSet ? MyMemory->FocusActorSet->GetActorLocation() : MyMemory->FocusLocationSet;
		const FVector Origin				= Pawn->GetActorLocation();
		const FVector DestinationDirection	= (Destination - Origin).GetSafeNormal2D();
		const float DestinationYaw			= DestinationDirection.Rotation().Yaw;
		const float DeltaYaw				= UCsCommon::GetAngleDelta(CurrentYaw, DestinationYaw);
		const float AbsDeltaYaw				= FMath::Abs(DeltaYaw);
		// EXIT, if near AngleDeltaForSuccess
		if (AbsDeltaYaw <= AngleDeltaForSuccess)
		{
			Pawn->ResetLookAt(0.0f /*Immediately*/);

			CleanUp(*AIController, NodeMemory);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

			ACsAIPlayerState* PlayerState = Pawn->GetPlayerState<ACsAIPlayerState>();

			Pawn->OnBTTask_LookAtAndRotateToFace_Finish_Event.Broadcast(PlayerState->UniqueMappingId);
#if WITH_EDITOR
			Pawn->OnBTTask_LookAtAndRotateToFace_Finish_ScriptEvent.Broadcast(PlayerState->UniqueMappingId);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAtAndRotateToFace::TickTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}
		// LERP to goal Angle
		else
		{
			float AngleDelta = DeltaYaw > 0.0f ? DeltaSeconds * RotationRate : -DeltaSeconds * RotationRate;

			if (FMath::Abs(AngleDelta) > AbsDeltaYaw)
				AngleDelta = DeltaYaw;

			const FRotator Rotation			= FRotator(0.0f, CurrentYaw + AngleDelta, 0.0f);
			const FVector UpdatedDirection	= Rotation.Vector();
			const FVector PawnLocation		= Pawn->GetActorLocation();
			const FVector UpdatedFocalPoint = PawnLocation + 10000.0f * UpdatedDirection;

			AIController->SetFocalPoint(UpdatedFocalPoint, EAIFocusPriority::Gameplay);

#if !UE_BUILD_SHIPPING
			if (CsCVarDrawAIBTRotateToFaceBBEntry->GetInt() == CS_CVAR_DRAW)
			{
				UWorld* World = Pawn->GetWorld();

				// Line to Goal
				static const float Thickness = 2.0f;

				DrawDebugLine(World, Origin, Destination, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);

				// Goal
				static const float Radius   = 32.0f;
				static const float Segments = 16.0f;

				DrawDebugSphere(World, Destination, Radius, Segments, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);

				// Arrow from Pawn in the direction it will eventually face
				static const float Length = 128.0f;
				FVector End				  = Origin + Length * DestinationDirection;

				DrawDebugDirectionalArrow(World, Origin, End, 10.0f, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);

				// Arrow from Pawn int the direction it is currently facing
				End = Origin + Length * PawnDirection;

				DrawDebugDirectionalArrow(World, Origin, End, 10.0f, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}
}

EBTNodeResult::Type UCsBTTask_LookAtAndRotateToFace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn()))
		{
			if (bResetOnAbort)
				Pawn->ResetLookAt(0.0f /*Immediately*/);
			else
				Pawn->StopLookAt();
#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCs, Warning, TEXT("UCsBTTask_LookAtAndRotateToFace::AbortTask (%s.%s): Aborted."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}
		CleanUp(*AIController, NodeMemory);
	}

	return EBTNodeResult::Aborted;
}

void UCsBTTask_LookAtAndRotateToFace::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc));

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController != NULL && AIController->GetPawn() != NULL)
	{
		const FVector PawnDirection = AIController->GetPawn()->GetActorForwardVector();
		const FVector FocalPoint	= AIController->GetFocalPointForPriority(EAIFocusPriority::Gameplay);

		if (FocalPoint != FAISystem::InvalidLocation)
		{
			const float CurrentAngleRadians = CalculateAngleDifferenceDot(PawnDirection, (FocalPoint - AIController->GetPawn()->GetActorLocation()).GetSafeNormal2D());
			Values.Add(FString::Printf(TEXT("Current angle: %.2f"), FMath::RadiansToDegrees(FMath::Acos(CurrentAngleRadians))));
		}
		else
		{
			Values.Add(TEXT("FocalPoint is an Invalid Location"));
		}
	}
	else
	{
		Values.Add(TEXT("Controller or Pawn is NULL"));
	}
}

FString UCsBTTask_LookAtAndRotateToFace::GetStaticDescription() const
{
	FString Description = BlackboardKey.SelectedKeyName.ToString();

	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		// Bone
		if (Bone != NAME_None)
			Description += TEXT(" at Bone: ") + Bone.ToString();
	}

	Description += TEXT(" with Rate: ") + FString::SanitizeFloat(RotationRate) + TEXT(" degs/sec with Delta Sucess of: ") + FString::SanitizeFloat(AngleDeltaForSuccess) + TEXT(" degs");
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}

float UCsBTTask_LookAtAndRotateToFace::CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB) const
{
	return VectorA.CosineAngle2D(VectorB);
}

void UCsBTTask_LookAtAndRotateToFace::CleanUp(AAIController& AIController, uint8* NodeMemory)
{
	FCsBTTask_LookAtAndRotateToFaceMemory* MyMemory = (FCsBTTask_LookAtAndRotateToFaceMemory*)NodeMemory;
	check(MyMemory);

	bool bClearFocus = false;
	if (MyMemory->bActorSet)
	{
		bClearFocus = (MyMemory->FocusActorSet == AIController.GetFocusActorForPriority(EAIFocusPriority::Gameplay));
	}
	else
	{
		bClearFocus = (MyMemory->FocusLocationSet == AIController.GetFocalPointForPriority(EAIFocusPriority::Gameplay));
	}

	if (bClearFocus)
	{
		AIController.ClearFocus(EAIFocusPriority::Gameplay);
	}
}
