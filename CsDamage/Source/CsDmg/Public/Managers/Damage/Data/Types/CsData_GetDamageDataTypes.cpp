// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Types/CsData_GetDamageDataTypes.h"
#include "CsDmg.h"

const FName NCsData::IGetDamageDataTypes::Name = FName("NCsData::IGetDamageDataTypes");

UCsData_GetDamageDataTypes::UCsData_GetDamageDataTypes(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_GetDamageDataTypes::Name = FName("ICsData_GetDamageDataTypes");