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

void ACsGunWeapon::ApplyData_Weapon(const TCsWeaponSlot &Slot, class ACsData_Weapon* InData, class ACsData_WeaponMaterialSkin* InSkin, const bool &Equipped /*=true*/){}

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