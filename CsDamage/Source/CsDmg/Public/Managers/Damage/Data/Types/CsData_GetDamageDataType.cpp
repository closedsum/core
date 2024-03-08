// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"
#include "CsDmg.h"

const FName NCsData::IGetDamageDataType::Name = FName("NCsData::IGetDamageDataType");

UCsData_GetDamageDataType::UCsData_GetDamageDataType(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_GetDamageDataType::Name = FName("ICsData_GetDamageDataType");