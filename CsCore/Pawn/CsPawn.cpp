// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Pawn/CsPawn.h"
#include "CsCore.h"
#include "CsCVars.h"

// Managers
#include "Managers/Inventory/CsManager_Inventory.h"

ACsPawn::ACsPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACsPawn::OnTickActor_HandleCVars(const float &DeltaSeconds) {};

// View
#pragma region

void ACsPawn::RecordView() {}

#pragma endregion View

// Body / Root
#pragma region

void ACsPawn::RecordRoot()
{
	CurrentRootRotation = GetActorRotation();
	CurrentRootLocation = GetActorLocation();
	CurrentRootDir		= CurrentRootRotation.Vector();
	CurrentRootDirXY	= FRotator(0.0f, CurrentRootRotation.Yaw, 0.0f).Vector();

	FRotator Rotation = CurrentRootRotation;

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	CurrentRootRight = Matrix.GetScaledAxis(EAxis::Y);

	Rotation = FRotator(0.0f, CurrentRootRotation.Yaw, 0.0f);

	Matrix = FRotationMatrix(Rotation);
	CurrentRootRightXY = Matrix.GetScaledAxis(EAxis::Y);
}

#pragma endregion Body / Root

// Movement
#pragma region

void ACsPawn::RecordVelocityAndSpeed()
{
	// Velocity from CharacterMovement
	CurrentVelocity			= GetVelocity();
	CurrentVelocityDir		= CurrentVelocity.GetSafeNormal();
	CurrentVelocityXY.X		= CurrentVelocity.X;
	CurrentVelocityXY.Y		= CurrentVelocity.Y;
	CurrentVelocityDirXY	= CurrentVelocityXY.GetSafeNormal();
	CurrentVelocityZ.Z		= CurrentVelocity.Z;
	CurrentVelocityDirZ		= CurrentVelocityZ.GetSafeNormal();
	CurrentSpeed			= CurrentVelocity.Size();
	CurrentSpeedXY			= CurrentVelocityXY.Size();
	CurrentSpeedZ			= CurrentVelocityZ.Size();

	FRotator Rotation = CurrentVelocityDir.Rotation();

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	CurrentVelocityRight = Matrix.GetScaledAxis(EAxis::Y);
	
	Rotation = CurrentVelocityDirXY.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentVelocityRightXY = Matrix.GetScaledAxis(EAxis::Y);

	// Velocity from Capsule
	CurrentCapsuleVelocity		= GetCapsuleComponent()->GetComponentVelocity();
	CurrentCapsuleVelocityDir	= CurrentCapsuleVelocity.GetSafeNormal();
	CurrentCapsuleVelocityXY.X	= CurrentCapsuleVelocity.X;
	CurrentCapsuleVelocityXY.Y	= CurrentCapsuleVelocity.Y;
	CurrentCapsuleVelocityDirXY = CurrentCapsuleVelocityXY.GetSafeNormal();
	CurrentCapsuleVelocityZ.Z	= CurrentCapsuleVelocity.Z;
	CurrentCapsuleVelocityDirZ	= CurrentCapsuleVelocityZ.GetSafeNormal();
	CurrentCapsuleSpeed			= CurrentCapsuleVelocity.Size();
	CurrentCapsuleSpeedXY		= CurrentCapsuleVelocityXY.Size();
	CurrentCapsuleSpeedZ		= CurrentCapsuleVelocityZ.Size();

	Rotation = CurrentCapsuleVelocityDir.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentCapsuleVelocityRight = Matrix.GetScaledAxis(EAxis::Y);

	Rotation = CurrentCapsuleVelocityDirXY.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentCapsuleVelocityRightXY = Matrix.GetScaledAxis(EAxis::Y);
}

#pragma endregion Movement

// Managers
#pragma region

ACsManager_Inventory* ACsPawn::GetMyManager_Inventory() { return nullptr; }

#pragma endregion Managers