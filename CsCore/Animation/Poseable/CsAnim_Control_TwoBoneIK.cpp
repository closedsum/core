// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsAnim_Control_TwoBoneIK.h"
#include "CsCore.h"
#include "CsCommon.h"

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