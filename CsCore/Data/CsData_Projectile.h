// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes.h"
#include "CsData_Projectile.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Projectile : public ACsData
{
	GENERATED_UCLASS_BODY()

	TCsProjectileType ProjectileType_Internal;
	TCsProjectileType ProjectileType_Internal_MAX;

	virtual TCsProjectileType GetBaseProjectileType();
};