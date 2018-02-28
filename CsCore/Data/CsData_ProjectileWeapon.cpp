// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileWeapon.h"
#include "CsCore.h"
// Data
#include "Data/CsData_Projectile.h"

ACsData_ProjectileWeapon::ACsData_ProjectileWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

bool ACsData_ProjectileWeapon::UseFakeProjectile(const TCsWeaponFireMode &FireMode) { return false; }
ACsData_Projectile* ACsData_ProjectileWeapon::GetData_Projectile(const TCsWeaponFireMode &FireMode, const bool &IsCharged) { return nullptr; }

FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const uint8 &Index /*=0*/){ return FVector::ZeroVector; }
FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const uint8 &Index /*=0*/){ return FVector::ZeroVector; }

#pragma endregion Stats

// FX
#pragma region

FCsFxElement* ACsData_ProjectileWeapon::GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const int32 &Index /*=0*/){ return nullptr; }

#pragma endregion FX