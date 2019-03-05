// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/BehaviorTree/Services/CsBTService_SetRandomLocation.h"
#include "CsCore.h"

#include "AI/CsAIController.h"
#include "AI/Pawn/CsAIPawn.h"

#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationData.h"
#include "AI/NavigationSystemBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

//DEFINE_STAT(STAT_UCsBTService_SetRandomLocation);

UCsBTService_SetRandomLocation::UCsBTService_SetRandomLocation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Set Random Location");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTService_SetRandomLocation, BlackboardKey));
}

void UCsBTService_SetRandomLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//SCOPE_CYCLE_COUNTER(STAT_UCsBTService_SetRandomLocation);

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

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
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsBTService_SetRandomLocation::TickNode: No NavigationData found."));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsBTService_SetRandomLocation::TickNode: No NavigationSystem found."));
	}
}