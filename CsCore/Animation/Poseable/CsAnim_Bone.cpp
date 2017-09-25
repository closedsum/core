// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsAnim_Bone.h"
#include "CsCore.h"
#include "CsCommon.h"

ACsAnim_Bone::ACsAnim_Bone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	SetMobility(EComponentMobility::Movable);

	Bone = NAME_None;
	BoneIndex = INDEX_NONE;

	RecordTransform = true;
	RecordRotation = true;
}

void ACsAnim_Bone::Tick(float DeltaSeconds)
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

bool ACsAnim_Bone::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsAnim_Bone::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
	/*
	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale3D();
	*/
	
	const bool Record = Root->IsSelected() || IsSelected() || ForceUpdateTransform;

	if (!Record)
		return;
	if (!RecordTransform)
		return;

	Location = GetActorLocation();

	if (!ForceUpdateTransform &&
		!RecordLocation &&
		Location.HasChanged())
	{
		SetActorLocation(Location.Last_Value);
		Location.Value = Location.Last_Value;
		Location.Clear();
	}

	Rotation = GetActorRotation();

	if (!ForceUpdateTransform &&
		!RecordRotation &&
		Rotation.HasChanged())
	{
		SetActorRotation(Rotation.Last_Value);
		Rotation.Value = Rotation.Last_Value;
		Rotation.Clear();
	}

	Scale = GetActorScale3D();

	if (!ForceUpdateTransform &&
		!RecordScale &&
		Scale.HasChanged())
	{
		SetActorScale3D(Scale.Last_Value);
		Scale.Value = Scale.Last_Value;
		Scale.Clear();
	}
}

void ACsAnim_Bone::ResetRelativeTransform()
{
	UpdateRelativeTransform(DefaultRelativeTransform, true);
}

bool ACsAnim_Bone::HasTransformChanged()
{
	return Location.HasChanged() || Rotation.HasChanged() || Scale.HasChanged();
}

void ACsAnim_Bone::ResolveTransform()
{
	Location.Clear();
	Rotation.Clear();
	Scale.Clear();
}

void ACsAnim_Bone::UpdateTransform(const FTransform &Transform)
{
	SetActorLocation(Transform.GetTranslation());
	SetActorRotation(Transform.GetRotation());
	SetActorScale3D(Transform.GetScale3D());
	//SetActorTransform()

	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale3D();

	//ForceUpdateTransform = true;
}

void ACsAnim_Bone::UpdateRelativeTransform(const FTransform &Transform, const bool &Resolve)
{
	GetRootComponent()->SetRelativeLocation(Transform.GetTranslation());
	GetRootComponent()->SetRelativeRotation(Transform.GetRotation());
	GetRootComponent()->SetRelativeScale3D(Transform.GetScale3D());

	//SetActorRelativeTransform()

	Location = GetActorLocation();
	Rotation = GetActorRotation();
	Scale = GetActorScale3D();

	ForceUpdateTransform = Resolve;
	//if (Resolve)
	//	ResolveTransform();
}