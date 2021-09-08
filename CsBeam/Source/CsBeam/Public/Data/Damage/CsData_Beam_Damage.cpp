// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_Beam_Damage.h"
#include "CsBeam.h"

const FName NCsBeam::NData::NDamage::IDamage::Name = FName("NCsBeam::NData::NDamage::IDamage");

const FName ICsData_Beam_Damage::Name = FName("ICsData_Beam_Damage");

UCsData_Beam_Damage::UCsData_Beam_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}