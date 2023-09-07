// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Shape/Cone/CsData_DamageCone.h"
#include "CsDmg.h"

const FName NCsDamage::NData::NShape::NCone::ICone::Name = FName("NCsDamage::NData::NShape::NCone::ICone");

UCsData_DamageCone::UCsData_DamageCone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageCone::Name = FName("ICsData_DamageCone");