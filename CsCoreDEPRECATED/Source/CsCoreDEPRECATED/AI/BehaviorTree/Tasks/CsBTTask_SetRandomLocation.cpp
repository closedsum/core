// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/BehaviorTree/Tasks/CsBTTask_SetRandomLocation.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/CsCVars_AI_BT.h"

// BehaviorTree
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AI/CsAIController.h"
#include "AI/Pawn/CsAIPawn.h"

#include "NavigationSystem/Public/NavigationSystem.h"

UCsBTTask_SetRandomLocation::UCsBTTask_SetRandomLocation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Set Random Location");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTTask_SetRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UCsBTTask_SetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	ACsAIController*  Controller	 = Cast<ACsAIController>(OwnerComp.GetOwner());
	ACsAIPawn* Pawn					 = Cast<ACsAIPawn>(Controller->GetPawn());

	UWorld* World			    = Pawn->GetWorld();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

	if (NavSys)
	{
		ANavigationData* NavData = Cast<ANavigationData>(NavSys->GetMainNavData());

		if (NavData)
		{
			const FVector Origin = Pawn->GetActorLocation();
			FNavLocation OutLocation(Origin);

			const bool bResult = NavSys->GetRandomPointInNavigableRadius(Origin, Radius, OutLocation, NavData, UNavigationQueryFilter::GetQueryFilter(*NavData, Pawn, FilterClass));

			Blackboard->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.SelectedKeyName, bResult ? OutLocation.Location : Origin);

#if !UE_BUILD_SHIPPING
			if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

				UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_SetRandomLocation::ExecuteTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
			}
#endif // #if !UE_BUILD_SHIPPING
			return EBTNodeResult::Succeeded;
		}
		else
		{
			UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_SetRandomLocation::ExecuteTask: No NavigationData found."));
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_SetRandomLocation::ExecuteTask: No NavigationSystem found."));
		return EBTNodeResult::Failed;
	}
}