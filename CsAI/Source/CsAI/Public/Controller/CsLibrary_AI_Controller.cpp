// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Controller/CsLibrary_AI_Controller.h"

// Library
#include "Blackboard/CsLibrary_Blackboard.h"
#include "Library/CsLibrary_Valid.h"
// AI
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

namespace NCsAI
{
	namespace NController
	{
		UBlackboardComponent* FLibrary::GetBlackboardChecked(const FString& Context, const AAIController* Controller)
		{
			CS_IS_PENDING_KILL_CHECKED(Controller);

			UBrainComponent* BrainComponent = Controller->GetBrainComponent();

			CS_IS_PENDING_KILL_CHECKED(BrainComponent);

			UBlackboardComponent* Blackboard = BrainComponent->GetBlackboardComponent();

			CS_IS_PENDING_KILL_CHECKED(Blackboard);
			return Blackboard;
		}

		UBlackboardComponent* FLibrary::GetSafeBlackboard(const FString& Context, const AAIController* Controller, void(*Log)(const FString&) /*=&NCsAI::FLog::Warning*/)
		{
			CS_IS_PENDING_KILL_RET_NULL(Controller);

			UBrainComponent* BrainComponent = Controller->GetBrainComponent();

			CS_IS_PENDING_KILL_RET_NULL(BrainComponent);

			UBlackboardComponent* Blackboard = BrainComponent->GetBlackboardComponent();

			CS_IS_PENDING_KILL_RET_NULL(Blackboard);
			return Blackboard;
		}
	}
}