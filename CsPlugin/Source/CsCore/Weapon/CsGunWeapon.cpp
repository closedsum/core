// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsGunWeapon.h"
#include "CsCore.h"
#include "Library/CsLibrary_Common.h"

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

void ACsGunWeapon::ApplyData_Weapon(const FECsWeaponSlot &Slot, UCsData_Weapon* InData, UCsData_WeaponMaterialSkin* InSkin, const bool &Equipped)
{
	Reset();

	WeaponSlot = Slot;
	WeaponIndex = Slot.Value;

	MyData_Weapon = InData;

	UCsData_ProjectileWeapon* Data_Weapon = Cast<UCsData_ProjectileWeapon>(InData);
	GripType = Data_Weapon->GetGripType();

	MyData_WeaponMaterialSkin = InSkin;
	IsEquipped = Equipped;

	CurrentState = IdleState;
	LastState = CurrentState;

	// UseMeshLow
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

	OnApplyData_Weapon_Event.Broadcast(WeaponSlot);
#if WITH_EDITOR
	OnApplyData_Weapon_ScriptEvent.Broadcast(WeaponSlot);
#endif // #if WITH_EDITOR
}

UCsData_WeaponMaterialSkin* ACsGunWeapon::GetMyData_WeaponMaterialSkin()
{
	return MyData_WeaponMaterialSkin.IsValid() ? MyData_WeaponMaterialSkin.Get() : nullptr;
}

UCsData_Character* ACsGunWeapon::GetMyData_Character()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

	bReloadingHandle = false;
	ReloadStartTime = GetWorld()->GetTimeSeconds() + ReloadTime.Get(CS_WEAPON_DATA_VALUE) + 1.0f;
}

#pragma endregion State

// Mesh
#pragma region

void ACsGunWeapon::SetMesh() {}

#pragma endregion Mesh

// Animation
#pragma region

const FECsCharacterAnim& ACsGunWeapon::GetCharacterAnimType(const FECsWeaponAnim &AnimType) { return EMCsCharacterAnim::Get().GetMAX(); }

#pragma endregion Animation