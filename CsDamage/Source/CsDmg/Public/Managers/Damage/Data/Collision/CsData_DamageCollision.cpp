// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
#include "CsDmg.h"

const FName NCsDamage::NData::NCollision::ICollision::Name = FName("NCsDamage::NData::NCollision::ICollision");

UCsData_DamageCollision::UCsData_DamageCollision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageCollision::Name = FName("ICsData_DamageCollision");