// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "CsDmg.h"

const FName NCsDamage::NData::NShape::IShape::Name = FName("NCsDamage::NData::NShape::IShape");

UCsData_DamageShape::UCsData_DamageShape(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageShape::Name = FName("ICsData_DamageShape");