// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "VR/Player/CsPlayerPawn_VR.h"
#include "CsCore.h"
#include "MotionControllerComponent.h"
#include "../InputCore/Classes/InputCoreTypes.h"
#include "MotionController/CsMotionController.h"

ACsPlayerPawn_VR::ACsPlayerPawn_VR(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MotionControllerClass = ACsMotionController::StaticClass();

	MotionControllerComponent_LeftHand = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("MotionControllerComponent_LeftHand"));
	MotionControllerComponent_LeftHand->MotionSource = EMCsControllerHand::Get().ToName(ECsControllerHand::Left);
	MotionControllerComponent_RightHand = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("MotionControllerComponent_RightHand"));
	MotionControllerComponent_RightHand->MotionSource = EMCsControllerHand::Get().ToName(ECsControllerHand::Right);
}

void ACsPlayerPawn_VR::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags					|= RF_Transient;

	// LeftHand
	LeftHand = GetWorld()->SpawnActor<ACsMotionController>(MotionControllerClass, SpawnInfo);
	LeftHand->SetReplicates(false);
	LeftHand->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(LeftHand);
	LeftHand->Init(MotionControllerComponent_LeftHand, ECsControllerHand::Left);
	// RightHand
	RightHand = GetWorld()->SpawnActor<ACsMotionController>(MotionControllerClass, SpawnInfo);
	RightHand->SetReplicates(false);
	RightHand->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(RightHand);
	RightHand->Init(MotionControllerComponent_RightHand, ECsControllerHand::Right);

	LeftHand->OtherHand = RightHand;
	RightHand->OtherHand = LeftHand;
}

void ACsPlayerPawn_VR::Destroyed()
{
	Super::Destroyed();

	if (LeftHand)
	{
		LeftHand->Destroy(true);
		LeftHand = nullptr;
	}

	if (RightHand)
	{
		RightHand->Destroy(true);
		RightHand = nullptr;
	}
}

void ACsPlayerPawn_VR::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LeftHand->OnTick(DeltaSeconds);
	RightHand->OnTick(DeltaSeconds);
}

// Camera
#pragma region

void ACsPlayerPawn_VR::LinkHandsToCamera(USceneComponent* CameraViewComponent)
{
	MotionControllerComponent_LeftHand->AttachToComponent(CameraViewComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	MotionControllerComponent_RightHand->AttachToComponent(CameraViewComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

#pragma endregion Camera

// Hands
#pragma region

void ACsPlayerPawn_VR::ShowHand(const TCsControllerHand &Hand)
{
	if (Hand == ECsControllerHand::Left)
		LeftHand->Show();
	if (Hand == ECsControllerHand::Right)
		RightHand->Show();
}

void ACsPlayerPawn_VR::ShowHands()
{
	ShowHand(ECsControllerHand::Left);
	ShowHand(ECsControllerHand::Right);
}

void ACsPlayerPawn_VR::HideHand(const TCsControllerHand &Hand)
{
	if (Hand == ECsControllerHand::Left)
		LeftHand->Hide();
	if (Hand == ECsControllerHand::Right)
		RightHand->Hide();
}

void ACsPlayerPawn_VR::HideHands()
{
	HideHand(ECsControllerHand::Left);
	HideHand(ECsControllerHand::Right);
}

#pragma endregion Hands