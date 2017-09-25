// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/Controls/CsAnim_Control.h"
#include "CsCore.h"
#include "CsCommon.h"

ACsAnim_Control::ACsAnim_Control(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	SetMobility(EComponentMobility::Movable);

	RecordTransform = true;
}

void ACsAnim_Control::Tick(float DeltaSeconds)
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

bool ACsAnim_Control::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsAnim_Control::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}

	const bool Record = Root->IsSelected() || IsSelected() || ForceUpdateTransform;

	if (!Record)
		return;
	if (!RecordTransform)
		return;

	Location = GetActorLocation();
	
	if (!RecordLocation &&
		Location.HasChanged())
	{
		SetActorLocation(Location.Last_Value);
		Location.Value = Location.Last_Value;
		Location.Clear();
	}

	Rotation = GetActorRotation();

	if (!RecordRotation &&
		Rotation.HasChanged())
	{
		SetActorRotation(Rotation.Last_Value);
		Rotation.Value = Rotation.Last_Value;
		Rotation.Clear();
	}

	Scale = GetActorScale3D();

	if (!RecordScale &&
		Scale.HasChanged())
	{
		SetActorScale3D(Scale.Last_Value);
		Scale.Value = Scale.Last_Value;
		Scale.Clear();
	}
}