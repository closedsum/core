// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/CsData_StatusEffect_Visual.h"
#include "CsSe.h"

const FName NCsStatusEffect::NData::NVisual::IVisual::Name = FName("NCsStatusEffect::NData::NVisual::IVisual");

UCsData_StatusEffect_Visual::UCsData_StatusEffect_Visual(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_StatusEffect_Visual::Name = FName("ICsData_StatusEffect_Visual");