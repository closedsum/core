// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Trigger/CsData_StatusEffect_Trigger.h"
#include "CsSe.h"

const FName NCsStatusEffect::NData::NTrigger::ITrigger::Name = FName("NCsStatusEffect::NData::NTrigger::ITrigger");

UCsData_StatusEffect_Trigger::UCsData_StatusEffect_Trigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_StatusEffect_Trigger::Name = FName("ICsData_StatusEffect_Trigger");