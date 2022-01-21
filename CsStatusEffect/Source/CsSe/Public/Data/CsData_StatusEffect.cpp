// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_StatusEffect.h"
#include "CsSe.h"

const FName NCsStatusEffect::NData::IData::Name = FName("NCsStatusEffect::NData::IData");

UCsData_StatusEffect::UCsData_StatusEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_StatusEffect::Name = FName("ICsData_StatusEffect");