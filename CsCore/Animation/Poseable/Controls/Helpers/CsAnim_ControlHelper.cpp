// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper.h"
#include "CsCore.h"
#include "CsCommon.h"

ACsAnim_ControlHelper::ACsAnim_ControlHelper(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	SetMobility(EComponentMobility::Movable);

	ControlIndex = INDEX_NONE;
}

void ACsAnim_ControlHelper::Tick(float DeltaSeconds)
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

bool ACsAnim_ControlHelper::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsAnim_ControlHelper::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}

	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale3D();
}


bool ACsAnim_ControlHelper::HasTransformChanged()
{
	return Location.HasChanged() || Rotation.HasChanged() || Scale.HasChanged();
}

void ACsAnim_ControlHelper::ResolveTransform()
{
	Location.Clear();
	Rotation.Clear();
	Scale.Clear();
}

void ACsAnim_ControlHelper::UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve)
{
	SetActorRelativeTransform(Transform);

	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale3D();

	if (Resolve)
		ResolveTransform();
}