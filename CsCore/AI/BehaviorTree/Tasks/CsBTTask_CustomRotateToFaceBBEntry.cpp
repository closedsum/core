// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_CustomRotateToFaceBBEntry.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Common/CsCommon.h"

#include "AI/Pawn/CsAIPawn.h"

UCsBTTask_CustomRotateToFaceBBEntry::UCsBTTask_CustomRotateToFaceBBEntry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AngleDeltaForSuccessDot(10.f)
{
	NodeName = TEXT("Rotate to face BB entry");
	bNotifyTick = true;
	
	RotationRate = 360.0f;

	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomRotateToFaceBBEntry, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomRotateToFaceBBEntry, BlackboardKey));
	BlackboardKey.AddRotatorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomRotateToFaceBBEntry, BlackboardKey));
}

void UCsBTTask_CustomRotateToFaceBBEntry::PostInitProperties()
{
	Super::PostInitProperties();

	AngleDeltaForSuccessDot = FMath::Cos(FMath::DegreesToRadians(AngleDeltaForSuccess));
}

void UCsBTTask_CustomRotateToFaceBBEntry::PostLoad()
{
	Super::PostLoad();

	AngleDeltaForSuccessDot = FMath::Cos(FMath::DegreesToRadians(AngleDeltaForSuccess));
}

EBTNodeResult::Type UCsBTTask_CustomRotateToFaceBBEntry::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == NULL || AIController->GetPawn() == NULL)
	{
		return EBTNodeResult::Failed;
	}

	FCsBTTask_CustomRotateToFaceBBEntryMemory* MyMemory = (FCsBTTask_CustomRotateToFaceBBEntryMemory*)NodeMemory;
	check(MyMemory);
	MyMemory->Reset();

	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	APawn* Pawn								 = AIController->GetPawn();
	const FVector PawnLocation				 = Pawn->GetActorLocation();
	const FVector PawnForward				 = Pawn->GetActorForwardVector();
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue  = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* ActorValue = Cast<AActor>(KeyValue);

		if (ActorValue != NULL)
		{
			const float AngleDifference = CalculateAngleDifferenceDot(Pawn->GetActorForwardVector(), (ActorValue->GetActorLocation() - PawnLocation).GetSafeNormal2D());
			
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
			const float AngleDifference = CalculateAngleDifferenceDot(PawnForward, (KeyValue - PawnLocation).GetSafeNormal2D());

			if (AngleDifference >= AngleDeltaForSuccessDot)
			{
				Result = EBTNodeResult::Succeeded;
			}
			else
			{
				const FVector CurrentFocalPoint = PawnLocation + 10000.0f * PawnForward;

				AIController->SetFocalPoint(CurrentFocalPoint, EAIFocusPriority::Gameplay);
				MyMemory->FocusLocationSet = KeyValue;
				Result = EBTNodeResult::InProgress;
			}
		}
	}
	// Rotator
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
	{
		const FRotator KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Rotator>(BlackboardKey.GetSelectedKeyID());

		if (FAISystem::IsValidRotation(KeyValue))
		{
			const FVector DirectionVector = KeyValue.Vector();
			const float AngleDifference	  = CalculateAngleDifferenceDot(PawnForward, DirectionVector);

			if (AngleDifference >= AngleDeltaForSuccessDot)
			{
				Result = EBTNodeResult::Succeeded;
			}
			else
			{
				const FVector CurrentFocalPoint     = PawnLocation + 10000.0f * PawnForward;
				const FVector DestinationFocalPoint = PawnLocation + 10000.0f * DirectionVector;
				// set focal somewhere far in the indicated direction
				AIController->SetFocalPoint(CurrentFocalPoint, EAIFocusPriority::Gameplay);
				MyMemory->FocusLocationSet = DestinationFocalPoint;
				Result = EBTNodeResult::InProgress;
			}
		}
	}

	return Result;
}

void UCsBTTask_CustomRotateToFaceBBEntry::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == NULL || AIController->GetPawn() == NULL)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		APawn* Pawn = AIController->GetPawn();

		FCsBTTask_CustomRotateToFaceBBEntryMemory* MyMemory = (FCsBTTask_CustomRotateToFaceBBEntryMemory*)NodeMemory;
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
			CleanUp(*AIController, NodeMemory);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
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

			if (CsCVarDrawAIBTRotateToFaceBBEntry->GetInt() == CS_CVAR_DRAW)
			{
				UWorld* World = Pawn->GetWorld();

				// Line to Goal
				const float Thickness = 2.0f;

				DrawDebugLine(World, Origin, Destination, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);

				// Goal
				const float Radius   = 32.0f;
				const float Segments = 16.0f;

				DrawDebugSphere(World, Destination, Radius, Segments, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);

				// Arrow from Pawn in the direction it will eventually face
				const float Length				   = 128.0f;
				FVector End						   = Origin + Length * DestinationDirection;

				DrawDebugDirectionalArrow(World, Origin, End, 10.0f, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);

				// Arrow from Pawn int the direction it is currently facing
				End = Origin + Length * PawnDirection;

				DrawDebugDirectionalArrow(World, Origin, End, 10.0f, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
			}
		}
	}
}

EBTNodeResult::Type UCsBTTask_CustomRotateToFaceBBEntry::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController != NULL)
	{
		CleanUp(*AIController, NodeMemory);
	}

	return EBTNodeResult::Aborted;
}

void UCsBTTask_CustomRotateToFaceBBEntry::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc));

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController != NULL && AIController->GetPawn() != NULL)
	{
		const FVector PawnDirection = AIController->GetPawn()->GetActorForwardVector();
		const FVector FocalPoint = AIController->GetFocalPointForPriority(EAIFocusPriority::Gameplay);

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

FString UCsBTTask_CustomRotateToFaceBBEntry::GetStaticDescription() const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc);
}

float UCsBTTask_CustomRotateToFaceBBEntry::CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB) const
{
	return VectorA.CosineAngle2D(VectorB);
}

void UCsBTTask_CustomRotateToFaceBBEntry::CleanUp(AAIController& AIController, uint8* NodeMemory)
{
	FCsBTTask_CustomRotateToFaceBBEntryMemory* MyMemory = (FCsBTTask_CustomRotateToFaceBBEntryMemory*)NodeMemory;
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
