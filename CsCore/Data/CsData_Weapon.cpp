// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "CsCore.h"
// Data
#include "Data/CsData_Projectile.h"

ACsData_Weapon::ACsData_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void* ACsData_Weapon::GetFireTypeStruct(const uint8 &Index) { return nullptr; }
UScriptStruct* ACsData_Weapon::GetFireTypeScriptStruct() { return nullptr; }
//ACsData_Projectile* ACsData_Weapon::GetData_Projectile(const TCsWeaponFire &FireType, const bool &IsCharged){ return nullptr; }