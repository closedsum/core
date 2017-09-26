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

	ControlIndex = INDEX_NONE;

	LockTransform = false;
	LockLocation = false;
	LockRotation = false;
	LockScale = false;

	RecordTransform = !LockTransform;
	RecordLocation = !LockLocation;
	RecordRotation = !LockRotation;
	RecordScale = !LockScale;
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

#if WITH_EDITOR

void ACsAnim_Control::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}

	ControlName = GetActorLabel();

	if (ControlName.HasChanged())
	{
		OnControlNameChanged();
		OnControlNameChanged_Event.ExecuteIfBound(ControlIndex);
		ControlName.Clear();
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

	ForceUpdateTransform = false;
}

void ACsAnim_Control::OnControlNameChanged()
{
	Anchor->SetActorLabel(TEXT("anchor_") + GetActorLabel());
}

void ACsAnim_Control::SetControlName(const FString &InName)
{
	SetActorLabel(InName);
	OnControlNameChanged();
}

#endif // #if WITH_EDITOR

#if WITH_EDITOR

void ACsAnim_Control::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeProperty(e);
		return;
	}

	// ResetToAnchor
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsAnim_Control, ResetToAnchor))
	{
		if (ResetToAnchor)
		{
			GetRootComponent()->SetRelativeTransform(FTransform::Identity);
			ResetToAnchor = false;
		}
	}
	Super::PostEditChangeProperty(e);
}

void ACsAnim_Control::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeChainProperty(e);
		return;
	}

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR