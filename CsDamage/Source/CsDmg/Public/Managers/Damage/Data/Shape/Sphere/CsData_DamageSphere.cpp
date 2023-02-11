// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphere.h"
#include "CsDmg.h"

const FName NCsDamage::NData::NShape::NSphere::ISphere::Name = FName("NCsDamage::NData::NShape::NSphere::ISphere");

UCsData_DamageSphere::UCsData_DamageSphere(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageSphere::Name = FName("ICsData_DamageSphere");