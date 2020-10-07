// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileStatusEffect.h"
#include "CsSe.h"

const FName NCsProjectile::NData::NStatusEffect::IStatusEffect::Name = FName("NCsProjectile::NData::NStatusEffect::IStatusEffect");

const FName ICsData_ProjectileStatusEffect::Name = FName("ICsData_ProjectileStatusEffect");

UCsData_ProjectileStatusEffect::UCsData_ProjectileStatusEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}