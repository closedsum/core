// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_Damage.h"
#include "CsSe.h"

const FName NCsStatusEffect::NData::NDamage::IDamage::Name = FName("NCsStatusEffect::NData::NDamage::IDamage");

UCsData_StatusEffect_Damage::UCsData_StatusEffect_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_StatusEffect_Damage::Name = FName("ICsData_StatusEffect_Damage");