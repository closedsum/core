// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Collision/CsData_Projectile_Collision.h"
#include "CsPrj.h"

const FName NCsProjectile::NData::NCollision::ICollision::Name = FName("NCsProjectile::NData::NCollision::ICollision");

const FName ICsData_Projectile_Collision::Name = FName("ICsData_Projectile_Collision");

UCsData_Projectile_Collision::UCsData_Projectile_Collision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}