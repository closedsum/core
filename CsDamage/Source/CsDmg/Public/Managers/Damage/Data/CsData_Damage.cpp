// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/CsData_Damage.h"
#include "CsDmg.h"

const FName NCsDamage::NData::IData::Name = FName("NCsDamage::NData::IData");

UCsData_Damage::UCsData_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_Damage::Name = FName("ICsData_Damage");