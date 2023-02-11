// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/Cone/CsData_DamageCone.h"
#include "CsDmg.h"

const FName NCsDamage::NData::NShape::NCone::ICone::Name = FName("NCsDamage::NData::NShape::NCone::ICone");

UCsData_DamageCone::UCsData_DamageCone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageCone::Name = FName("ICsData_DamageCone");