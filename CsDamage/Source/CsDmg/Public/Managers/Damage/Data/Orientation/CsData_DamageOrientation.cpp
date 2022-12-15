// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Orientation/CsData_DamageOrientation.h"
#include "CsDmg.h"

const FName NCsDamage::NData::NOrientation::IOrientation::Name = FName("NCsDamage::NData::NOrientation::IOrientation");

UCsData_DamageOrientation::UCsData_DamageOrientation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageOrientation::Name = FName("ICsData_DamageOrientation");