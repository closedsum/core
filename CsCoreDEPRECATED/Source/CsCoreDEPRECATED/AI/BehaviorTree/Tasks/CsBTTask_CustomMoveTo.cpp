// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_CustomMoveTo.h"
#include "AI/BehaviorTree/CsCVars_AI_BT.h"

// Types
#include "Types/CsTypes.h"

#include "GameFramework/Actor.h"
#include "AISystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "VisualLogger/VisualLogger.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tasks/AITask_MoveTo.h"

#include "AI/Pawn/CsAIPawn.h"

UCsBTTask_CustomMoveTo::UCsBTTask_CustomMoveTo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Move To";
	bUseGameplayTasks = GET_AI_CONFIG_VAR(bEnableBTAITasks);
	bNotifyTick = !bUseGameplayTasks;
	bNotifyTaskFinished = true;

	AcceptableRadius = GET_AI_CONFIG_VAR(AcceptanceRadius);
	bStopOnOverlap = GET_AI_CONFIG_VAR(bFinishMoveOnGoalOverlap); 
	bAllowStrafe = GET_AI_CONFIG_VAR(bAllowStrafing);
	bAllowPartialPath = GET_AI_CONFIG_VAR(bAcceptPartialPaths);
	bTrackMovingGoal = true;
	bProjectGoalLocation = true;
	bUsePathfinding = true;

	ObservedBlackboardValueTolerance = AcceptableRadius * 0.95f;

	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomMoveTo, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_CustomMoveTo, BlackboardKey));
}

EBTNodeResult::Type UCsBTTask_CustomMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	FCsBTTask_CustomMoveToMemory* MyMemory	= reinterpret_cast<FCsBTTask_CustomMoveToMemory*>(NodeMemory);
	MyMemory->PreviousGoalLocation			= FAISystem::InvalidLocation;
	MyMemory->MoveRequestID					= FAIRequestID::InvalidRequest;

	AAIController* MyController = OwnerComp.GetAIOwner();
	MyMemory->bWaitingForPath	= bUseGameplayTasks ? false : MyController->ShouldPostponePathUpdates();
	if (!MyMemory->bWaitingForPath)
	{
		NodeResult = PerformMoveTask(OwnerComp, NodeMemory);
	}
	else
	{
		UE_VLOG(MyController, LogBehaviorTree, Log, TEXT("Pathfinding requests are freezed, waiting..."));
	}

	if (NodeResult == EBTNodeResult::InProgress && bObserveBlackboardValue)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (ensure(BlackboardComp))
		{
			if (MyMemory->BBObserverDelegateHandle.IsValid())
			{
				UE_VLOG(MyController, LogBehaviorTree, Warning, TEXT("UBTTask_MoveTo::ExecuteTask \'%s\' Old BBObserverDelegateHandle is still valid! Removing old Observer."), *GetNodeName());
				BlackboardComp->UnregisterObserver(BlackboardKey.GetSelectedKeyID(), MyMemory->BBObserverDelegateHandle);
			}
			MyMemory->BBObserverDelegateHandle = BlackboardComp->RegisterObserver(BlackboardKey.GetSelectedKeyID(), this, FOnBlackboardChangeNotification::CreateUObject(this, &UCsBTTask_CustomMoveTo::OnBlackboardValueChange));
		}
	}	
	
	return NodeResult;
}

EBTNodeResult::Type UCsBTTask_CustomMoveTo::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	FCsBTTask_CustomMoveToMemory* MyMemory	 = reinterpret_cast<FCsBTTask_CustomMoveToMemory*>(NodeMemory);
	AAIController* MyController				 = OwnerComp.GetAIOwner();

	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
	if (MyController && MyBlackboard)
	{
		FAIMoveRequest MoveReq;
		MoveReq.SetNavigationFilter(*FilterClass ? FilterClass : MyController->GetDefaultNavigationFilterClass());
		MoveReq.SetAllowPartialPath(bAllowPartialPath);
		MoveReq.SetAcceptanceRadius(AcceptableRadius);
		MoveReq.SetCanStrafe(bAllowStrafe);
		MoveReq.SetReachTestIncludesAgentRadius(bStopOnOverlap);
		MoveReq.SetProjectGoalLocation(bProjectGoalLocation);
		MoveReq.SetUsePathfinding(bUsePathfinding);
		// Object
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			UObject* KeyValue   = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
			AActor* TargetActor = Cast<AActor>(KeyValue);
			if (TargetActor)
			{
				if (bTrackMovingGoal)
				{
					MoveReq.SetGoalActor(TargetActor);
				}
				else
				{
					MoveReq.SetGoalLocation(TargetActor->GetActorLocation());
				}
			}
			else
			{
				UE_VLOG(MyController, LogBehaviorTree, Warning, TEXT("UBTTask_MoveTo::ExecuteTask tried to go to actor while BB %s entry was empty"), *BlackboardKey.SelectedKeyName.ToString());
			}
		}
		// Vector
		else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			const FVector TargetLocation = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
			MoveReq.SetGoalLocation(TargetLocation);

			MyMemory->PreviousGoalLocation = TargetLocation;
		}

		if (MoveReq.IsValid())
		{
			if (GET_AI_CONFIG_VAR(bEnableBTAITasks))
			{
				UAITask_MoveTo* MoveTask	  = MyMemory->Task.Get();
				const bool bReuseExistingTask = (MoveTask != nullptr);

				MoveTask = PrepareMoveTask(OwnerComp, MoveTask, MoveReq);
				if (MoveTask)
				{
					MyMemory->bObserverCanFinishTask = false;

					if (bReuseExistingTask)
					{
						if (MoveTask->IsActive())
						{
							UE_VLOG(MyController, LogBehaviorTree, Verbose, TEXT("\'%s\' reusing AITask %s"), *GetNodeName(), *MoveTask->GetName());
							MoveTask->ConditionalPerformMove();
						}
						else
						{
							UE_VLOG(MyController, LogBehaviorTree, Verbose, TEXT("\'%s\' reusing AITask %s, but task is not active - handing over move performing to task mechanics"), *GetNodeName(), *MoveTask->GetName());
						}
					}
					else
					{
						MyMemory->Task = MoveTask;
						UE_VLOG(MyController, LogBehaviorTree, Verbose, TEXT("\'%s\' task implementing move with task %s"), *GetNodeName(), *MoveTask->GetName());
						MoveTask->ReadyForActivation();
					}

					MyMemory->bObserverCanFinishTask = true;
					NodeResult = (MoveTask->GetState() != EGameplayTaskState::Finished) ? EBTNodeResult::InProgress :
						MoveTask->WasMoveSuccessful() ? EBTNodeResult::Succeeded :
						EBTNodeResult::Failed;
				}
			}
			else
			{
				FPathFollowingRequestResult RequestResult = MyController->MoveTo(MoveReq);
				if (RequestResult.Code == EPathFollowingRequestResult::RequestSuccessful)
				{
					MyMemory->MoveRequestID = RequestResult.MoveId;
					WaitForMessage(OwnerComp, UBrainComponent::AIMessage_MoveFinished, RequestResult.MoveId);
					WaitForMessage(OwnerComp, UBrainComponent::AIMessage_RepathFailed);

					NodeResult = EBTNodeResult::InProgress;
				}
				else if (RequestResult.Code == EPathFollowingRequestResult::AlreadyAtGoal)
				{
					NodeResult = EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return NodeResult;
}

UAITask_MoveTo* UCsBTTask_CustomMoveTo::PrepareMoveTask(UBehaviorTreeComponent& OwnerComp, UAITask_MoveTo* ExistingTask, FAIMoveRequest& MoveRequest)
{
	UAITask_MoveTo* MoveTask = ExistingTask ? ExistingTask : NewBTAITask<UAITask_MoveTo>(OwnerComp);
	if (MoveTask)
	{
		MoveTask->SetUp(MoveTask->GetAIController(), MoveRequest);
	}

	return MoveTask;
}

EBlackboardNotificationResult UCsBTTask_CustomMoveTo::OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	UBehaviorTreeComponent* BehaviorComp = Cast<UBehaviorTreeComponent>(Blackboard.GetBrainComponent());
	if (BehaviorComp == nullptr)
	{
		return EBlackboardNotificationResult::RemoveObserver;
	}

	uint8* RawMemory					   = BehaviorComp->GetNodeMemory(this, BehaviorComp->FindInstanceContainingNode(this));
	FCsBTTask_CustomMoveToMemory* MyMemory = reinterpret_cast<FCsBTTask_CustomMoveToMemory*>(RawMemory);

	const EBTTaskStatus::Type TaskStatus = BehaviorComp->GetTaskStatus(this);
	if (TaskStatus != EBTTaskStatus::Active)
	{
		UE_VLOG(BehaviorComp, LogBehaviorTree, Error, TEXT("BT MoveTo \'%s\' task observing BB entry while no longer being active!"), *GetNodeName());

		// resetting BBObserverDelegateHandle without unregistering observer since 
		// returning EBlackboardNotificationResult::RemoveObserver here will take care of that for us
		MyMemory->BBObserverDelegateHandle.Reset(); //-V595

		return EBlackboardNotificationResult::RemoveObserver;
	}
	
	// this means the move has already started. MyMemory->bWaitingForPath == true would mean we're waiting for right moment to start it anyway,
	// so we don't need to do anything due to BB value change 
	if (MyMemory != nullptr && MyMemory->bWaitingForPath == false && BehaviorComp->GetAIOwner() != nullptr)
	{
		check(BehaviorComp->GetAIOwner()->GetPathFollowingComponent());

		bool bUpdateMove = true;
		// check if new goal is almost identical to previous one
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			const FVector TargetLocation = Blackboard.GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());

			bUpdateMove = (FVector::DistSquared(TargetLocation, MyMemory->PreviousGoalLocation) > FMath::Square(ObservedBlackboardValueTolerance));
		}

		if (bUpdateMove)
		{
			// don't abort move if using AI tasks - it will mess things up
			if (MyMemory->MoveRequestID.IsValid())
			{
				UE_VLOG(BehaviorComp, LogBehaviorTree, Log, TEXT("Blackboard value for goal has changed, aborting current move request"));
				StopWaitingForMessages(*BehaviorComp);
				BehaviorComp->GetAIOwner()->GetPathFollowingComponent()->AbortMove(*this, FPathFollowingResultFlags::NewRequest, MyMemory->MoveRequestID, EPathFollowingVelocityMode::Keep);
			}

			if (!bUseGameplayTasks && BehaviorComp->GetAIOwner()->ShouldPostponePathUpdates())
			{
				// NodeTick will take care of requesting move
				MyMemory->bWaitingForPath = true;
			}
			else
			{
				const EBTNodeResult::Type NodeResult = PerformMoveTask(*BehaviorComp, RawMemory);
				if (NodeResult != EBTNodeResult::InProgress)
				{
					FinishLatentTask(*BehaviorComp, NodeResult);
				}
			}
		}
	}

	return EBlackboardNotificationResult::ContinueObserving;
}

EBTNodeResult::Type UCsBTTask_CustomMoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FCsBTTask_CustomMoveToMemory* MyMemory = reinterpret_cast<FCsBTTask_CustomMoveToMemory*>(NodeMemory);
	if (!MyMemory->bWaitingForPath)
	{
		if (MyMemory->MoveRequestID.IsValid())
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (MyController && MyController->GetPathFollowingComponent())
			{
				MyController->GetPathFollowingComponent()->AbortMove(*this, FPathFollowingResultFlags::OwnerFinished, MyMemory->MoveRequestID);
			}
		}
		else
		{
			MyMemory->bObserverCanFinishTask = false;
			UAITask_MoveTo* MoveTask		 = MyMemory->Task.Get();
			if (MoveTask)
			{
				MoveTask->ExternalCancel();
			}
			else
			{
				UE_VLOG(&OwnerComp, LogBehaviorTree, Error, TEXT("Can't abort path following! bWaitingForPath:false, MoveRequestID:invalid, MoveTask:none!"));
			}
		}
	}

	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UCsBTTask_CustomMoveTo::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	FCsBTTask_CustomMoveToMemory* MyMemory = reinterpret_cast<FCsBTTask_CustomMoveToMemory*>(NodeMemory);
	MyMemory->Task.Reset();

	if (bObserveBlackboardValue)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (ensure(BlackboardComp) && MyMemory->BBObserverDelegateHandle.IsValid())
		{
			BlackboardComp->UnregisterObserver(BlackboardKey.GetSelectedKeyID(), MyMemory->BBObserverDelegateHandle);
		}

		MyMemory->BBObserverDelegateHandle.Reset();
	}

	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

void UCsBTTask_CustomMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FCsBTTask_CustomMoveToMemory* MyMemory = (FCsBTTask_CustomMoveToMemory*)NodeMemory;
	if (MyMemory->bWaitingForPath && !OwnerComp.IsPaused())
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (MyController && !MyController->ShouldPostponePathUpdates())
		{
			UE_VLOG(MyController, LogBehaviorTree, Log, TEXT("Pathfinding requests are unlocked!"));
			MyMemory->bWaitingForPath = false;

			const EBTNodeResult::Type NodeResult = PerformMoveTask(OwnerComp, NodeMemory);
			if (NodeResult != EBTNodeResult::InProgress)
			{
				FinishLatentTask(OwnerComp, NodeResult);
			}
		}
	}

	if (MyMemory->MoveRequestID != FAIRequestID::InvalidRequest &&
		MyMemory->PreviousGoalLocation != FAISystem::InvalidLocation)
	{
		if (CsCVarDrawAIBTMoveTo->GetInt() == CS_CVAR_DRAW)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			ACsAIPawn* Pawn			  = Cast<ACsAIPawn>(MyController->GetPawn());
			const FVector Origin	  = Pawn->GetActorLocation();
			const FVector Destination = MyMemory->PreviousGoalLocation;

			UWorld* World = Pawn->GetWorld();

			// Line to Goal
			const float Thickness = 2.0f;

			DrawDebugLine(World, Origin, Destination, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);
			// Goal
			const float Radius   = 32.0f;
			const float Segments = 16.0f;

			DrawDebugSphere(World, Destination, Radius, Segments, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);
			// Arrow from Pawn to the direction the Pawn travels

			const FVector Forward = Pawn->GetActorForwardVector();
			const float Length	  = 128.0f;
			const FVector End	  = Origin + Length * Forward;

			DrawDebugDirectionalArrow(World, Origin, End, 10.0f, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);
		}
	}
}

void UCsBTTask_CustomMoveTo::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 SenderID, bool bSuccess)
{
	// AIMessage_RepathFailed means task has failed
	bSuccess &= (Message != UBrainComponent::AIMessage_RepathFailed);
	Super::OnMessage(OwnerComp, NodeMemory, Message, SenderID, bSuccess);
}

void UCsBTTask_CustomMoveTo::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	// AI move task finished
	UAITask_MoveTo* MoveTask = Cast<UAITask_MoveTo>(&Task);
	if (MoveTask && MoveTask->GetAIController() && MoveTask->GetState() != EGameplayTaskState::Paused)
	{
		UBehaviorTreeComponent* BehaviorComp = GetBTComponentForTask(Task);
		if (BehaviorComp)
		{
			uint8* RawMemory = BehaviorComp->GetNodeMemory(this, BehaviorComp->FindInstanceContainingNode(this));
			FCsBTTask_CustomMoveToMemory* MyMemory = reinterpret_cast<FCsBTTask_CustomMoveToMemory*>(RawMemory);

			if (MyMemory->bObserverCanFinishTask && (MoveTask == MyMemory->Task))
			{
				const bool bSuccess = MoveTask->WasMoveSuccessful();
				FinishLatentTask(*BehaviorComp, bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
			}
		}
	}
}

FString UCsBTTask_CustomMoveTo::GetStaticDescription() const
{
	FString KeyDesc("invalid");
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass() ||
		BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	}

	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc);
}

void UCsBTTask_CustomMoveTo::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (BlackboardComp)
	{
		const FString KeyValue = BlackboardComp->DescribeKeyValue(BlackboardKey.GetSelectedKeyID(), EBlackboardDescription::OnlyValue);

		FCsBTTask_CustomMoveToMemory* MyMemory = (FCsBTTask_CustomMoveToMemory*)NodeMemory;
		const bool bIsUsingTask				   = MyMemory->Task.IsValid();
		
		const FString ModeDesc =
			MyMemory->bWaitingForPath ? TEXT("(WAITING)") :
			bIsUsingTask ? TEXT("(task)") :
			TEXT("");

		Values.Add(FString::Printf(TEXT("move target: %s%s"), *KeyValue, *ModeDesc));
	}
}

uint16 UCsBTTask_CustomMoveTo::GetInstanceMemorySize() const
{
	return sizeof(FCsBTTask_CustomMoveToMemory);
}

#if WITH_EDITOR

FName UCsBTTask_CustomMoveTo::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.MoveTo.Icon");
}

#endif	// WITH_EDITOR
