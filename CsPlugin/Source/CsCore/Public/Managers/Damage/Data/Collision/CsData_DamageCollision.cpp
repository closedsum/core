// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
#include "CsCore.h"

const FName NCsDamage::NData::NCollision::ICollision::Name = FName("NCsDamage::NData::NCollision::ICollision");

UCsData_DamageCollision::UCsData_DamageCollision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageCollision::Name = FName("ICsData_DamageCollision");