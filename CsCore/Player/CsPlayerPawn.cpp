// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerPawn.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

ACsPlayerPawn::ACsPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	bAllowTickBeforeBeginPlay = true;
	/*
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetMesh()->SetHiddenInGame(true);
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	GetMesh()->ClothTickFunction.bCanEverTick = true;
	GetMesh()->bGenerateOverlapEvents = false;
	GetMesh()->Deactivate();

	GetMesh()->ClothTickFunction.bStartWithTickEnabled = false;
	GetCharacterMovement()->PrimaryComponentTick.bStartWithTickEnabled = false;
	GetCharacterMovement()->bAutoActivate = false;
	*/
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	/*
	bAlwaysRelevant		   = true;
	NetDormancy			   = ENetDormancy::DORM_Never;
	NetCullDistanceSquared = FMath::Square(100000);
	*/

	EyeHeight = 192.0f;
}

void ACsPlayerPawn::OnTickActor_CheckCVars(){};

// Camera
#pragma region

void ACsPlayerPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	// TODO: This should allow another client to look at another clients view point

	AController* ViewingController = Controller;

	if (!ViewingController)
		return;
	ViewingController->CalcCamera(DeltaTime, OutResult);
}

FRotator ACsPlayerPawn::GetViewRotation() const
{
	return Super::GetViewRotation();
}

FVector ACsPlayerPawn::GetPawnViewLocation() const
{
	if (UCsCommon::IsVive())
		return Super::GetPawnViewLocation() + FVector(0.0f, 0.0f, -2.0f * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
	return GetFeetLocation() + FVector(0.0f, 0.0f, EyeHeight);
}

FVector ACsPlayerPawn::GetFeetLocation() const
{
	return GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

#pragma endregion Camera