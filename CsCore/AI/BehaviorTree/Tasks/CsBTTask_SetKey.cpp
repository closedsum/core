// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_SetKey.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

#include "Common/CsCommon.h"
// AI
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"
// Data
#include "Data/CsData_Character.h"

UCsBTTask_SetKey::UCsBTTask_SetKey(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Set Key");
	bNotifyTick = true;
}

EBTNodeResult::Type UCsBTTask_SetKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return EBTNodeResult::Failed;

	ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());

	if (!Pawn)
		return EBTNodeResult::Failed;

	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	// Bool
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
		MyBlackboard->SetValueAsBool(BlackboardKey.SelectedKeyName, Operation == ECsBTTask_BasicSetOperation::Set);
	// Enum
	/*
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Enum::StaticClass())
	{
	}
	*/
	// Int
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
		MyBlackboard->SetValueAsInt(BlackboardKey.SelectedKeyName, Value_Int);
	// Float
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
		MyBlackboard->SetValueAsFloat(BlackboardKey.SelectedKeyName, Value_Float);
	// Name
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Name::StaticClass())
		MyBlackboard->SetValueAsName(BlackboardKey.SelectedKeyName, Value_Name);
	// String
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_String::StaticClass())
		MyBlackboard->SetValueAsString(BlackboardKey.SelectedKeyName, Value_String);
	// Vector
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		MyBlackboard->SetValueAsVector(BlackboardKey.SelectedKeyName, Value_Vector);
	// Rotator
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
		MyBlackboard->SetValueAsRotator(BlackboardKey.SelectedKeyName, Value_Rotator);
	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (Operation == ECsBTTask_BasicSetOperation::Clear)
			MyBlackboard->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	}
	// Class
	/*
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
	{
	}
	*/
	return EBTNodeResult::Succeeded;
}

void UCsBTTask_SetKey::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc));
}

FString UCsBTTask_SetKey::GetStaticDescription() const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc);
}