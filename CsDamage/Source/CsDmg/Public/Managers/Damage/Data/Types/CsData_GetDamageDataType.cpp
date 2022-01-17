// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"
#include "CsDmg.h"

const FName NCsData::IGetDamageDataType::Name = FName("NCsData::IGetDamageDataType");

UCsData_GetDamageDataType::UCsData_GetDamageDataType(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const FName ICsData_GetDamageDataType::Name = FName("ICsData_GetDamageDataType");