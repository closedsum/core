// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "CsCore.h"

ACsData_Projectile::ACsData_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TCsProjectileType ACsData_Projectile::GetBaseProjectileType() { return ProjectileType_Internal; }