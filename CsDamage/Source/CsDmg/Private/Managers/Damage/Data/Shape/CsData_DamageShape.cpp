// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"

const FName NCsDamage::NData::NShape::IShape::Name = FName("NCsDamage::NData::NShape::IShape");

UCsData_DamageShape::UCsData_DamageShape(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageShape::Name = FName("ICsData_DamageShape");