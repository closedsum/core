// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Animation/Mannequin/Silhouette/CsAnimInstance_Mannequin_Silhouette.h"
#include "CsCore.h"

// Mannequin
#include "Animation/Mannequin/Silhouette/CsMannequin_Silhouette.h"

UCsAnimInstance_Mannequin_Silhouette::UCsAnimInstance_Mannequin_Silhouette(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UAnimInstance Interface
#pragma region

// Init
void UCsAnimInstance_Mannequin_Silhouette::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MyOwner = Cast<ACsMannequin_Silhouette>(GetOwningActor());
}

// Tick
void UCsAnimInstance_Mannequin_Silhouette::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!MyOwner)
		return;

	PelvisHeight			= MyOwner->PelvisControl.Height;
	PelvisDepth				= MyOwner->PelvisControl.Depth;
	PelvisWidth				= MyOwner->PelvisControl.Width;
	PelvisHeightOffset		= MyOwner->PelvisControl.HeightOffset;
	LowerTorsoHeight		= MyOwner->LowerTorsoControl.Height;
	LowerTorsoDepth			= MyOwner->LowerTorsoControl.Depth;
	LowerTorsoWidth			= MyOwner->LowerTorsoControl.Width;
	//LowerTorsoHeightOffset  = MyOwner->LowerTorsoControl.HeightOffset;
	UpperTorsoHeight		= MyOwner->UpperTorsoControl.Height;
	UpperTorsoDepth			= MyOwner->UpperTorsoControl.Depth;
	UpperTorsoWidth			= MyOwner->UpperTorsoControl.Width;
	ChestHeight				= MyOwner->ChestControl.Height;
	ChestDepth				= MyOwner->ChestControl.Depth;
	ChestWidth				= MyOwner->ChestControl.Width;
	HeadHeight				= MyOwner->HeadControl.Height;
	HeadDepth				= MyOwner->HeadControl.Depth;
	HeadWidth				= MyOwner->HeadControl.Width;
	HeadScale				= MyOwner->HeadControl.Scale;
	LatSize					= MyOwner->LatSize;
	LatHeightOffset			= MyOwner->LatHeightOffset;
	UpperarmLength			= MyOwner->UpperarmControl.Length;
	UpperarmThickness		= MyOwner->UpperarmControl.Thickness;
	UpperarmThickness_Depth = MyOwner->UpperarmControl.Depth;
	UpperarmThickness_Width = MyOwner->UpperarmControl.Width;
	LowerarmLength			= MyOwner->LowerarmControl.Length;
	LowerarmThickness		= MyOwner->LowerarmControl.Thickness;
	LowerarmThickness_Depth = MyOwner->LowerarmControl.Depth;
	LowerarmThickness_Width = MyOwner->LowerarmControl.Width;
	HandLength				= MyOwner->HandControl.Length;
	HandThickness			= MyOwner->HandControl.Thickness;
	HandWidth				= MyOwner->HandControl.Width;
	HandScale				= MyOwner->HandControl.Scale;
	ThighLength				= MyOwner->ThighControl.Length;
	ThighThickness			= MyOwner->ThighControl.Thickness;
	ThighThickness_Depth	= MyOwner->ThighControl.Depth;
	ThighThickness_Width	= MyOwner->ThighControl.Width;
	CalfLength				= MyOwner->CalfControl.Length;
	CalfThickness			= MyOwner->CalfControl.Thickness;
	CalfThickness_Depth		= MyOwner->CalfControl.Depth;
	CalfThickness_Width		= MyOwner->CalfControl.Width;
	FootHeight				= MyOwner->FootControl.Height;
	FootLength				= MyOwner->FootControl.Length;
	FootWidth				= MyOwner->FootControl.Width;
	FootScale				= MyOwner->FootControl.Scale;
}

#pragma endregion UAnimInstance Interface