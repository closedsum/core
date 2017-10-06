// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsAnim_Bone.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Components/CsStaticMeshComponent.h"

ACsAnim_Bone::ACsAnim_Bone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	DefaultRootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("DefaultRootComponent"));
	DefaultRootComponent->SetMobility(EComponentMobility::Movable);
	SetRootComponent(DefaultRootComponent);
	StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);

	HandleSize = 1.0f;
	HandleSize_Internal = HandleSize * FVector::OneVector;

	Bone = NAME_None;
	BoneIndex = INDEX_NONE;
	ArrayIndex = INDEX_NONE;
	Root = nullptr;

	LockTransform = false;
	LockLocation = true;
	LockRotation = false;
	LockScale = true;

	RecordTransform = !LockTransform;
	RecordLocation = !LockLocation;
	RecordRotation = !LockRotation;
	RecordScale = !LockScale;

	DefaultRelativeTransform = FTransform::Identity;
	DefaultComponentTransform = FTransform::Identity;
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
		HandleSize_Internal = HandleSize * FVector::OneVector;

		HasTickedInEditor = true;
	}

	HandleScale = StaticMeshComponent->GetComponentScale();

	if (HandleScale.HasChanged())
	{
		StaticMeshComponent->SetWorldScale3D(HandleSize_Internal);
		HandleScale.Clear();
	}

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

	HandleScale = StaticMeshComponent->GetComponentScale();

	if (HandleScale.HasChanged())
	{
		StaticMeshComponent->SetWorldScale3D(HandleSize_Internal);
		HandleScale.Clear();
	}

	ForceUpdateTransform = false;
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
}

void ACsAnim_Bone::UpdateLocation(const FVector &InLocation, const int32 &Axes /*= CS_AXES_ALL*/)
{
	if (Axes == CS_AXES_ALL)
	{
		SetActorLocation(InLocation);
		Location = GetActorLocation();
	}
	else
	{
		FVector V = GetActorLocation();

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
			V.X = InLocation.X;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
			V.Y = InLocation.Y;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
			V.Z = InLocation.Z;

		SetActorLocation(V);
		Location = GetActorLocation();
	}
}

void ACsAnim_Bone::UpdateRotation(const FRotator &InRotation, const int32 &Axes /*= CS_AXES_ALL*/)
{
	if (Axes == CS_AXES_ALL)
	{
		SetActorRotation(InRotation);
		Rotation = GetActorRotation();
	}
	else
	{
		FRotator R = GetActorRotation();

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL))
			R.Roll = InRotation.Roll;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH))
			R.Pitch = InRotation.Pitch;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW))
			R.Yaw = InRotation.Yaw;

		SetActorRotation(R);
		Rotation = GetActorRotation();
	}
}

void ACsAnim_Bone::UpdateScale(const FVector &InScale, const int32 &Axes /*= CS_AXES_ALL*/)
{
	if (Axes == CS_AXES_ALL)
	{
		SetActorScale3D(InScale);
		Scale = GetActorScale3D();
	}
	else
	{
		FVector V = GetActorScale3D();

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
			V.X = InScale.X;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
			V.Y = InScale.Y;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
			V.Z = InScale.Z;

		SetActorScale3D(V);
		Scale = GetActorScale3D();
	}
}

#if WITH_EDITOR

void ACsAnim_Bone::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeProperty(e);
		return;
	}

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// HandleSize
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsAnim_Bone, HandleSize))
	{
		HandleSize_Internal = FVector(HandleSize);
		HandleScale			= HandleSize_Internal;

		StaticMeshComponent->SetWorldScale3D(HandleSize_Internal);
	}

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR