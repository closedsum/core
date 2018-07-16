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

	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	// Bool
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
	{
		bool Value = MyBlackboard->GetValue<UBlackboardKeyType_Bool>(BlackboardKey.GetSelectedKeyID());

		if ((BasicOperation == EBasicKeyOperation::Set && Value) ||
			(BasicOperation == EBasicKeyOperation::NotSet && !Value))
			return EBTNodeResult::Succeeded;
		return EBTNodeResult::InProgress;
	}
	// Enum
	/*
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Enum::StaticClass())
	{
	}
	*/
	// Int
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
	{
		int32 Value = MyBlackboard->GetValue<UBlackboardKeyType_Int>(BlackboardKey.GetSelectedKeyID());
		return Value == Value_Int ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
	}
	// Float
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
	{
		float Value = MyBlackboard->GetValue<UBlackboardKeyType_Float>(BlackboardKey.GetSelectedKeyID());
		return Value == Value_Float ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
	}
	// Name
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Name::StaticClass())
	{
		FName Value = MyBlackboard->GetValue<UBlackboardKeyType_Name>(BlackboardKey.GetSelectedKeyID());
		return Value == Value_Name ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
	}
	// String
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_String::StaticClass())
	{
		FString Value = MyBlackboard->GetValue<UBlackboardKeyType_String>(BlackboardKey.GetSelectedKeyID());
		return Value == Value_String ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
	}
	// Vector
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		FVector Value = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		return Value == Value_Vector ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
	}
	// Rotator
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
	{
		FRotator Value = MyBlackboard->GetValue<UBlackboardKeyType_Rotator>(BlackboardKey.GetSelectedKeyID());
		return Value == Value_Rotator ? EBTNodeResult::Succeeded : EBTNodeResult::InProgress;
	}
	// Object
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* Value = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());

		if ((BasicOperation == EBasicKeyOperation::Set && Value) ||
			(BasicOperation == EBasicKeyOperation::NotSet && !Value))
			return EBTNodeResult::Succeeded;
		return EBTNodeResult::InProgress;
	}
	// Class
	/*
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
	{
	}
	*/
	return EBTNodeResult::Failed;
}

void UCsBTTask_SetKey::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

		// Bool
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
		{
			bool Value = MyBlackboard->GetValue<UBlackboardKeyType_Bool>(BlackboardKey.GetSelectedKeyID());

			if ((BasicOperation == EBasicKeyOperation::Set && Value) ||
				(BasicOperation == EBasicKeyOperation::NotSet && !Value))
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Enum
		/*
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Enum::StaticClass())
		{
		}
		*/
		// Int
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
		{
			int32 Value = MyBlackboard->GetValue<UBlackboardKeyType_Int>(BlackboardKey.GetSelectedKeyID());
			
			if (Value == Value_Int)
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Float
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
		{
			float Value = MyBlackboard->GetValue<UBlackboardKeyType_Float>(BlackboardKey.GetSelectedKeyID());
			
			if (Value == Value_Float)
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Name
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Name::StaticClass())
		{
			FName Value = MyBlackboard->GetValue<UBlackboardKeyType_Name>(BlackboardKey.GetSelectedKeyID());

			if (Value == Value_Name)
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// String
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_String::StaticClass())
		{
			FString Value = MyBlackboard->GetValue<UBlackboardKeyType_String>(BlackboardKey.GetSelectedKeyID());

			if (Value == Value_String)
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Vector
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			FVector Value = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());

			if (Value == Value_Vector)
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Rotator
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
		{
			FRotator Value = MyBlackboard->GetValue<UBlackboardKeyType_Rotator>(BlackboardKey.GetSelectedKeyID());
			
			if (Value == Value_Rotator)
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Object
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			UObject* Value = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());

			if ((BasicOperation == EBasicKeyOperation::Set && Value) ||
				(BasicOperation == EBasicKeyOperation::NotSet && !Value))
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		// Class
		/*
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
		{
		}
		*/
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
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