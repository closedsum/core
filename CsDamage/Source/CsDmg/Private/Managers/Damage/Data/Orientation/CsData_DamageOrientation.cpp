// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Orientation/CsData_DamageOrientation.h"

const FName NCsDamage::NData::NOrientation::IOrientation::Name = FName("NCsDamage::NData::NOrientation::IOrientation");

UCsData_DamageOrientation::UCsData_DamageOrientation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_DamageOrientation::Name = FName("ICsData_DamageOrientation");