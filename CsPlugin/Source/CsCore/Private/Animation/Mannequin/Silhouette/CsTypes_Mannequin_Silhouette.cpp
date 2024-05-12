// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Mannequin/Silhouette/CsTypes_Mannequin_Silhouette.h"

// Animation
#include "Animation/Mannequin/Silhouette/CsMannequin_Silhouette.h"
// Components
#include "Components/StaticMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Mannequin_Silhouette)

namespace NCsAnimation
{
	namespace NMannequin
	{
		namespace NSilhouette
		{
			void FBoneControlInfo::OnModify(FBoneControlInfo& DOb)
			{
				Transform = Control->GetRelativeTransform();

				FVector3d Scale = Transform.GetScale3D();

				static const float MIN = 0.01f;

				if (Scale.X < MIN || Scale.Y < MIN || Scale.Z < MIN)
				{
					Scale = FVector3d(FMath::Max(MIN, Scale.X), FMath::Max(MIN, Scale.Y), FMath::Max(MIN, Scale.Z));

					Control->SetRelativeScale3D(Scale);
					DOb.Control->SetRelativeScale3D(Scale);
				}
			}
		}
	}
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Core::OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Core& DOb, InfoType& Info)
{
#undef InfoType

	const FTransform Transform = Info.Control->GetRelativeTransform();
	Info.Transform			   = Transform;

	FVector3d Scale = Transform.GetScale3D();

	SetFromScale(Scale);
	DOb.SetFromScale(Scale);

	const FVector3d Location = Transform.GetLocation();

	HeightOffset	 = Location.Z;
	DOb.HeightOffset = Location.Z;

	Info.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Core::OnUpdateByMember(InfoType& DObInfo, InfoType& Info)
{
#undef InfoType

	const FVector3d Scale = GetScale();

	Info.Control->SetRelativeScale3D(Scale);
	DObInfo.Control->SetRelativeScale3D(Scale);

	FVector3d Location = FVector3d::ZeroVector;

	Location.Z = HeightOffset;

	Info.Control->SetRelativeLocation(Location);
	DObInfo.Control->SetRelativeLocation(Location);

	Info.Transform = Info.Control->GetRelativeTransform();
	Info.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Limb::OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Limb& DOb, InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right)
{
#undef InfoType

	const FTransform Transform_L = Left.Control->GetRelativeTransform();
	const FTransform Transform_R = Right.Control->GetRelativeTransform();

	Left.Transform  = Transform_L;
	Right.Transform = Transform_R;

	// Left Changed
	if (Left.HasChanged())
	{
		Right.Transform = Transform_L;

		const FVector3d Scale = Transform_L.GetScale3D();

		SetFromScale(Scale);
		DOb.SetFromScale(Scale);

		RightDOb.Control->SetRelativeTransform(Transform_L);
		Right.Control->SetRelativeTransform(Transform_L);
	}
	// Right Changed
	else
	if (Right.HasChanged())
	{
		Left.Transform = Transform_R;

		const FVector3d Scale = Transform_R.GetScale3D();

		SetFromScale(Scale);
		DOb.SetFromScale(Scale);

		LeftDOb.Control->SetRelativeTransform(Transform_R);
		Left.Control->SetRelativeTransform(Transform_R);
	}
	Left.Resolve();
	Right.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Limb::OnUpdateByMember(InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right)
{
#undef InfoType

	const FVector3d Scale = GetScale();

	LeftDOb.Control->SetRelativeScale3D(Scale);
	Left.Control->SetRelativeScale3D(Scale);
	RightDOb.Control->SetRelativeScale3D(Scale);
	Right.Control->SetRelativeScale3D(Scale);

	Left.Transform = Left.Control->GetRelativeTransform();
	Right.Transform = Right.Control->GetRelativeTransform();

	Left.Resolve();
	Right.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Foot::OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Foot& DOb, InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right)
{
#undef InfoType

	const FTransform Transform_L = Left.Control->GetRelativeTransform();
	const FTransform Transform_R = Right.Control->GetRelativeTransform();

	Left.Transform  = Transform_L;
	Right.Transform = Transform_R;

	// Left Changed
	if (Left.HasChanged())
	{
		Right.Transform = Transform_L;

		const FVector3d _Scale = Transform_L.GetScale3D();

		SetFromScale(_Scale);
		DOb.SetFromScale(_Scale);

		RightDOb.Control->SetRelativeTransform(Transform_L);
		Right.Control->SetRelativeTransform(Transform_L);
	}
	// Right Changed
	else
	if (Right.HasChanged())
	{
		Left.Transform = Transform_R;

		const FVector3d _Scale = Transform_R.GetScale3D();

		SetFromScale(_Scale);
		DOb.SetFromScale(_Scale);

		LeftDOb.Control->SetRelativeTransform(Transform_R);
		Left.Control->SetRelativeTransform(Transform_R);
	}
	Left.Resolve();
	Right.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Foot::OnUpdateByMember(InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right)
{
#undef InfoType

	const FVector3d _Scale = GetScale();

	LeftDOb.Control->SetRelativeScale3D(_Scale);
	Left.Control->SetRelativeScale3D(_Scale);
	RightDOb.Control->SetRelativeScale3D(_Scale);
	Right.Control->SetRelativeScale3D(_Scale);

	Left.Transform  = Left.Control->GetRelativeTransform();
	Right.Transform = Right.Control->GetRelativeTransform();

	Left.Resolve();
	Right.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Hand::OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Hand& DOb, InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right)
{
#undef InfoType

	const FTransform Transform_L = Left.Control->GetRelativeTransform();
	const FTransform Transform_R = Right.Control->GetRelativeTransform();

	Left.Transform  = Transform_L;
	Right.Transform = Transform_R;

	// Left Changed
	if (Left.HasChanged())
	{
		Right.Transform = Transform_L;

		const FVector3d _Scale = Transform_L.GetScale3D();

		SetFromScale(_Scale);
		DOb.SetFromScale(_Scale);

		RightDOb.Control->SetRelativeTransform(Transform_L);
		Right.Control->SetRelativeTransform(Transform_L);
	}
	// Right Changed
	else
	if (Right.HasChanged())
	{
		Left.Transform = Transform_R;

		const FVector3d _Scale = Transform_R.GetScale3D();

		SetFromScale(_Scale);
		DOb.SetFromScale(_Scale);

		LeftDOb.Control->SetRelativeTransform(Transform_R);
		Left.Control->SetRelativeTransform(Transform_R);
	}
	Left.Resolve();
	Right.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Hand::OnUpdateByMember(InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right)
{
#undef InfoType

	const FVector3d _Scale = GetScale();

	LeftDOb.Control->SetRelativeScale3D(_Scale);
	Left.Control->SetRelativeScale3D(_Scale);
	RightDOb.Control->SetRelativeScale3D(_Scale);
	Right.Control->SetRelativeScale3D(_Scale);

	Left.Transform  = Left.Control->GetRelativeTransform();
	Right.Transform = Right.Control->GetRelativeTransform();

	Left.Resolve();
	Right.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Head::OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Head& DOb, InfoType& Info)
{
#undef InfoType

	const FTransform Transform = Info.Control->GetRelativeTransform();
	Info.Transform			   = Transform;

	FVector3d _Scale = Transform.GetScale3D();

	SetFromScale(_Scale);
	DOb.SetFromScale(_Scale);

	const FVector3d Location = Transform.GetLocation();

	HeightOffset	 = Location.Z;
	DOb.HeightOffset = Location.Z;

	Info.Resolve();
}

#define InfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
void FCsMannequinSilhouette_BoneControl_Head::OnUpdateByMember(InfoType& DObInfo, InfoType& Info)
{
#undef InfoType

	const FVector3d _Scale = GetScale();

	Info.Control->SetRelativeScale3D(_Scale);
	DObInfo.Control->SetRelativeScale3D(_Scale);

	FVector3d Location = FVector3d::ZeroVector;

	Location.Z = HeightOffset;

	Info.Control->SetRelativeLocation(Location);
	DObInfo.Control->SetRelativeLocation(Location);

	Info.Transform = Info.Control->GetRelativeTransform();
	Info.Resolve();
}
