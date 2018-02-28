// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Weapon.h"
#include "Types/CsTypes_Weapon.h"
#include "CsData_ProjectileWeapon.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_ProjectileWeapon : public ACsData_Weapon
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region

	virtual bool UseFakeProjectile(const TCsWeaponFireMode &FireMode);
	virtual class ACsData_Projectile* GetData_Projectile(const TCsWeaponFireMode &FireMode, const bool &IsCharged = false);

	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const uint8 &Index = 0);
	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const uint8 &Index = 0);

#pragma endregion Stats

// FX
#pragma region

	virtual FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const int32 &Index = 0);

#pragma endregion FX
};