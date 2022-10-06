// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Types/CsData_GetDamageDataTypes.h"
#include "CsDmg.h"

const FName NCsData::IGetDamageDataTypes::Name = FName("NCsData::IGetDamageDataTypes");

UCsData_GetDamageDataTypes::UCsData_GetDamageDataTypes(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_GetDamageDataTypes::Name = FName("ICsData_GetDamageDataTypes");