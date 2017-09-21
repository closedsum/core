// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsAnim_Control_JointTarget.h"
#include "CsCore.h"
#include "CsCommon.h"

ACsAnim_Control_JointTarget::ACsAnim_Control_JointTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	SetMobility(EComponentMobility::Movable);
}

void ACsAnim_Control_JointTarget::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
	// Handle Waypoints placed in Editor
	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
		OnTick_Editor(DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR
}

bool ACsAnim_Control_JointTarget::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsAnim_Control_JointTarget::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
	
	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale();
}