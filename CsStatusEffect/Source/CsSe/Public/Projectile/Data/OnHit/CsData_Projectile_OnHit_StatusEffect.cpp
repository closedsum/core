// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/OnHit/CsData_Projectile_OnHit_StatusEffect.h"
#include "CsSe.h"

const FName NCsProjectile::NData::NOnHit::NStatusEffect::IStatusEffect::Name = FName("NCsProjectile::NData::NOnHit::NStatusEffect::IStatusEffect");

const FName ICsData_Projectile_OnHit_StatusEffect::Name = FName("ICsData_Projectile_OnHit_StatusEffect");

UCsData_Projectile_OnHit_StatusEffect::UCsData_Projectile_OnHit_StatusEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}