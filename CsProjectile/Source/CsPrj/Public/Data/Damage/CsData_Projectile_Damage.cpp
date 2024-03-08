// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_Projectile_Damage.h"
#include "CsPrj.h"

const FName NCsProjectile::NData::NDamage::IDamage::Name = FName("NCsProjectile::NData::NDamage::IDamage");

const FName ICsData_Projectile_Damage::Name = FName("ICsData_Projectile_Damage");

UCsData_Projectile_Damage::UCsData_Projectile_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}