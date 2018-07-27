// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AI/BehaviorTree/Decorators/CsBTDecorator_CheckAbsDeltaYaw.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

// Behavior Tree
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
// AI
#include "AIController.h"
#include "AI/Pawn/CsAIPawn.h"

UCsBTDecorator_CheckAbsDeltaYaw::UCsBTDecorator_CheckAbsDeltaYaw(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Check Abs Delta Yaw";

	// accept only rotators
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTDecorator_CheckAbsDeltaYaw, BlackboardKey));
	BlackboardKey.AddRotatorFilter(this, GET_MEMBER_NAME_CHECKED(UCsBTDecorator_CheckAbsDeltaYaw, BlackboardKey));

	bCurrentView = false;
	EqualTolerance = SMALL_NUMBER;
}

bool UCsBTDecorator_CheckAbsDeltaYaw::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	check(AIController);
	ACsAIPawn* Pawn = Cast<ACsAIPawn>(AIController->GetPawn());
	check(Pawn);

	const FRotator& Rotation = bCurrentView ? Pawn->CurrentViewRotation : Pawn->CurrentRootRotation;

	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	// Float
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
	{
		const float KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Float>(BlackboardKey.GetSelectedKeyID());

		// =
		if (Operation == EArithmeticKeyOperation::Equal)
			return FMath::Abs(UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue) - Delta) <= EqualTolerance;
		// !=
		if (Operation == EArithmeticKeyOperation::NotEqual)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue) != Delta;
		// <
		if (Operation == EArithmeticKeyOperation::Less)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue) < Delta;
		// <=
		if (Operation == EArithmeticKeyOperation::LessOrEqual)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue) <= Delta;
		// >
		if (Operation == EArithmeticKeyOperation::Greater)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue) > Delta;
		// >=
		if (Operation == EArithmeticKeyOperation::GreaterOrEqual)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue) >= Delta;
	}
	// Rotator
	else
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
	{
		const FRotator KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Rotator>(BlackboardKey.GetSelectedKeyID());

		// =
		if (Operation == EArithmeticKeyOperation::Equal)
			return FMath::Abs(UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue.Yaw) - Delta) <= EqualTolerance;
		// !=
		if (Operation == EArithmeticKeyOperation::NotEqual)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue.Yaw) != Delta;
		// <
		if (Operation == EArithmeticKeyOperation::Less)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue.Yaw) < Delta;
		// <=
		if (Operation == EArithmeticKeyOperation::LessOrEqual)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue.Yaw) <= Delta;
		// >
		if (Operation == EArithmeticKeyOperation::Greater)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue.Yaw) > Delta;
		// >=
		if (Operation == EArithmeticKeyOperation::GreaterOrEqual)
			return UCsCommon::GetAbsAngleDelta(Rotation.Yaw, KeyValue.Yaw) >= Delta;
	}
	return false;
}

FString UCsBTDecorator_CheckAbsDeltaYaw::GetStaticDescription() const
{
	FString Description				 = BlackboardKey.SelectedKeyName.ToString();
	const FString& OperationAsString = EArithmeticKeyOperation::ToSymbol(Operation);
	Description						+= TEXT(" ") + OperationAsString + TEXT(" ") + FString::SanitizeFloat(Delta);

	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Description);
}