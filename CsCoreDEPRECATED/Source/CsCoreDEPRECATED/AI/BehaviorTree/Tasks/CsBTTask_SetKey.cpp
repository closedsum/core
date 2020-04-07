// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Tasks/CsBTTask_SetKey.h"
#include "CsCoreDEPRECATED.h"
#include "AI/BehaviorTree/Tasks/CsCVars_AI_BT_Task.h"

// Library
#include "Library/CsLibrary_Common.h"
// Behavior Tree
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
// AI
#include "AIController.h"
#include "AI/Pawn/CsAIPawn.h"
#include "AI/CsAIPlayerState.h"

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

#if !UE_BUILD_SHIPPING
	if (CsCVarLogAIBTTasks->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UBehaviorTree* BTree = OwnerComp.GetCurrentTree();

		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsBTTask_SetKey::ExecuteTask (%s.%s): Succeeded."), *(Pawn->GetName()), *(BTree->GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING
	return EBTNodeResult::Succeeded;
}

void UCsBTTask_SetKey::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	Values.Add(FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc));
}

FString UCsBTTask_SetKey::GetStaticDescription() const
{
	FString Description = BlackboardKey.SelectedKeyName.ToString();
	Description		   += TEXT(" to ");

		// Bool
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
		Description += Operation == ECsBTTask_BasicSetOperation::Set ? TEXT("true") : TEXT("false");
	// Enum
	/*
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Enum::StaticClass())
	{
	}
	*/
	// Int
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
		Description += FString::FromInt(Value_Int);
	// Float
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
		Description += FString::SanitizeFloat(Value_Float);
	// Name
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Name::StaticClass())
		Description += Value_Name.ToString();
	// String
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_String::StaticClass())
		Description += Value_String;
	// Vector
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		Description += Value_Vector.ToString();
	// Rotator
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
		Description += Value_Rotator.ToString();
	// Object
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		Description += TEXT("NULL");
	// Class
	/*
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
	{
	}
	*/
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}