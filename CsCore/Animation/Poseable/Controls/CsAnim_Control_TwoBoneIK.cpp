// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/Controls/CsAnim_Control_TwoBoneIK.h"
#include "CsCore.h"
#include "CsCommon.h"

#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper_EndEffector.h"
#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper_JointTarget.h"

ACsAnim_Control_TwoBoneIK::ACsAnim_Control_TwoBoneIK(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	SetMobility(EComponentMobility::Movable);
}

void ACsAnim_Control_TwoBoneIK::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
	
	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale();
}