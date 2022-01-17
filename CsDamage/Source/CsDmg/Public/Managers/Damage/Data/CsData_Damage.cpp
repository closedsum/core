// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#include "CsDmg.h"

const FName NCsDamage::NData::IData::Name = FName("NCsDamage::NData::IData");

UCsData_Damage::UCsData_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_Damage::Name = FName("ICsData_Damage");