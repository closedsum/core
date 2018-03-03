// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsGunWeapon.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "Pawn/CsPawn.h"
#include "Animation/CsAnimInstance_Character.h"

// Data
#include "Data/CsData_Character.h"
#include "Data/CsData_WeaponMaterialSkin.h"

ACsGunWeapon::ACsGunWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Data
#pragma region

void ACsGunWeapon::ApplyData_Weapon(const TCsWeaponSlot &Slot, ACsData_Weapon* InData, class ACsData_WeaponMaterialSkin* InSkin, const bool &Equipped)
{
	Reset();

	WeaponSlot = Slot;
	WeaponIndex = (uint8)Slot;

	MyData_Weapon = InData;

	ACsData_ProjectileWeapon* Data_Weapon = Cast<ACsData_ProjectileWeapon>(InData);
	GripType = Data_Weapon->GetGripType();

	MyData_WeaponMaterialSkin = InSkin;
	IsEquipped = Equipped;

	CurrentState = IdleState;
	LastState = CurrentState;

	// UseMeshLow
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		//UseMesh3PLow = false;// Pawn->UseMesh3PLow && InData->HasMesh3PLow;
	}

	SetMesh();
	AttachMeshToPawn();
	SetMultiValueMembers();

	OnApplyData_Weapon_Event.Broadcast(WeaponIndex);
#if WITH_EDITOR
	OnApplyData_Weapon_ScriptEvent.Broadcast(WeaponIndex);
#endif // #if WITH_EDITOR
}

ACsData_WeaponMaterialSkin* ACsGunWeapon::GetMyData_WeaponMaterialSkin()
{
	return MyData_WeaponMaterialSkin.IsValid() ? MyData_WeaponMaterialSkin.Get() : nullptr;
}

ACsData_Character* ACsGunWeapon::GetMyData_Character()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		// Character
		if (UCsAnimInstance_Character* AnimInstance = Cast<UCsAnimInstance_Character>(GetMyOwner()))
			return AnimInstance->GetData();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (MyOwnerType == PawnWeaponOwner)
			return GetMyPawn()->GetMyData_Character();
	}
	return nullptr;
}

#pragma endregion Data

// Owner
#pragma region

void ACsGunWeapon::AttachMeshToPawn() {}

#pragma endregion Owner

// State
#pragma region

void ACsGunWeapon::OnPawnDeActivate()
{
	Hide();
	Disable();

	IsReloading = false;
	ReloadStartTime = GetWorld()->TimeSeconds + ReloadTime.Get(CS_WEAPON_DATA_VALUE) + 1.0f;
}

#pragma endregion State

// Mesh
#pragma region

void ACsGunWeapon::SetMesh() {}

#pragma endregion Mesh

// Animation
#pragma region

TCsCharacterAnim ACsGunWeapon::GetCharacterAnimType(const TCsWeaponAnim &AnimType) { return TCsCharacterAnim(0); }

#pragma endregion Animation