// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Pawn/CsPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Character.h"
#include "Data/CsData_CharacterMeshSkin.h"
#include "Data/CsData_CharacterMaterialSkin.h"
// Managers
#include "Managers/Inventory/CsManager_Inventory.h"

#include "Player/CsPlayerStateBase.h"
#include "Weapon/CsWeapon.h"

ACsPawn::ACsPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WeaponClass = ACsWeapon::StaticClass();
}

void ACsPawn::PostActorCreated()
{
	Super::PostActorCreated();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	for (int32 I = 0; I < MaxWeaponCount; I++)
	{
		Weapons[I] = GetWorld()->SpawnActor<ACsWeapon>(WeaponClass, SpawnInfo);
		Weapons[I]->SetMyPawn(this);
	}
}

void ACsPawn::Destroyed()
{
	Super::Destroyed();

	for (int32 I = 0; I < MaxWeaponCount; I++)
	{
		if (!Weapons[I] && !Weapons[I]->IsPendingKill())
			Weapons[I]->Destroy();
	}
}

void ACsPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!IsPendingKill())
	{
		IsPlacedInWorld = GetWorld()->bStartup;
	}
}

void ACsPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RecordRoot();
	RecordVelocityAndSpeed();
}

void ACsPawn::OnTickActor_HandleCVars(const float &DeltaSeconds) {};

bool ACsPawn::IsOnBoardCompleted_Game()
{
	ACsPlayerStateBase* MyPlayerState = Cast<ACsPlayerStateBase>(PlayerState);

	if (!MyPlayerState)
		return false;
	return MyPlayerState->IsOnBoardCompleted_Game();
}

void ACsPawn::OnTick_HandleSetup() {}

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

// Data
#pragma region

ACsDataMapping* ACsPawn::GetDataMapping()
{
	return UCsCommon::GetDataMapping(GetWorld());
}

ACsData_Character* ACsPawn::GetMyData_Character()
{
	return MyData_Character.IsValid() ? MyData_Character.Get() : nullptr;
}

ACsData_CharacterMeshSkin* ACsPawn::GetMyData_CharacterMeshSkin()
{
	return MyData_CharacterMeshSkin.IsValid() ? MyData_CharacterMeshSkin.Get() : nullptr;
}

ACsData_CharacterMaterialSkin* ACsPawn::GetMyData_CharacterMaterialSkin()
{
	return MyData_CharacterMaterialSkin.IsValid() ? MyData_CharacterMaterialSkin.Get() : nullptr;
}

void ACsPawn::ApplyData_Character(){}

#pragma endregion Data

// Weapons
#pragma region

ACsWeapon* ACsPawn::GetWeapon(const TCsWeaponSlot &Slot)
{
	return Weapons[(uint8)Slot];
}

ACsWeapon* ACsPawn::GetCurrentWeapon()
{
	return GetWeapon(CurrentWeaponSlot);
}

ACsData_Weapon* ACsPawn::GetData_Weapon(const TCsWeaponSlot &Slot)
{
	return Data_Weapons[(uint8)Slot].IsValid() ? Data_Weapons[(uint8)Slot].Get() : nullptr;
}

ACsData_Weapon* ACsPawn::GetCurrentData_Weapon()
{
	return GetData_Weapon(CurrentWeaponSlot);
}

ACsData_WeaponMaterialSkin* ACsPawn::GetData_WeaponMaterialSkin(const TCsWeaponSlot &Slot)
{
	return Data_WeaponMaterialSkins[(uint8)Slot].IsValid() ? Data_WeaponMaterialSkins[(uint8)Slot].Get() : nullptr;
}

ACsData_WeaponMaterialSkin* ACsPawn::GetCurrentData_WeaponMaterialSkin()
{
	return GetData_WeaponMaterialSkin(CurrentWeaponSlot);
}

void ACsPawn::ApplyData_Weapon(){}

#pragma endregion Weapons

// Managers
#pragma region

ACsManager_Inventory* ACsPawn::GetMyManager_Inventory() { return nullptr; }

#pragma endregion Managers