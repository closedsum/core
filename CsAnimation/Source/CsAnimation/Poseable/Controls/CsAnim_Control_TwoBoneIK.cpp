// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Poseable/Controls/CsAnim_Control_TwoBoneIK.h"
#include "CsAnimation.h"

// Control Helpers
#include "Poseable/Controls/Helpers/CsAnim_ControlHelper_EndEffector.h"
#include "Poseable/Controls/Helpers/CsAnim_ControlHelper_JointTarget.h"

ACsAnim_Control_TwoBoneIK::ACsAnim_Control_TwoBoneIK(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	SetMobility(EComponentMobility::Movable);
}

#if WITH_EDITOR

void ACsAnim_Control_TwoBoneIK::OnTick_Editor(const float &DeltaSeconds)
{
	Super::OnTick_Editor(DeltaSeconds);
}

void ACsAnim_Control_TwoBoneIK::OnControlNameChanged()
{
	Super::OnControlNameChanged();

	EndEffector->SetActorLabel(GetActorLabel() + TEXT("_EndEffector"));
	JointTarget->SetActorLabel(GetActorLabel() + TEXT("_JointTarget"));
}

#endif // #if WITH_EDITOR