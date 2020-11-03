// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/Data/Damage/CsData_TraceDamage.h"
#include "CsCore.h"

const FName NCsTrace::NData::NDamage::IDamage::Name = FName("NCsTrace::NData::NDamage::IDamage");

const FName ICsData_TraceDamage::Name = FName("ICsData_TraceDamage");

UCsData_TraceDamage::UCsData_TraceDamage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}